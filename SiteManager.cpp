//
// Created by Vinayak Agarwal on 12/4/21.
//

#include <sstream>
#include <iostream>
#include "SiteManager.h"

using namespace std;

void SiteManager::fail(int nodeId) {
	Site * site = sites[nodeId];

	if (site == nullptr) {
		ostringstream stringStream;
		stringStream << "Cannot fail site " << nodeId << " since it does not exist!";
		string exceptionString = stringStream.str();
		throw invalid_argument(exceptionString);
	}

	site->fail();
}

void SiteManager::recover(int nodeId) {
	Site * site = sites[nodeId];

	if (site == nullptr) {
		ostringstream stringStream;
		stringStream << "Cannot recover site " << nodeId << " since it does not exist!";
		string exceptionString = stringStream.str();
		throw invalid_argument(exceptionString);
	}

	site->recover();
}

string SiteManager::read(Command *cmd) {
	set<int> siteList = reverseCfg[cmd->var];

	for (int site: siteList) {
		if (sites[site]->isSiteUp()) {
			if (cmd->txn->getTxnType() == RO) {
				sites[site]->read(cmd, cmd->txn->getStartTime());
			} else {
				// Same lock is acquired for multiple access to same variables in a transaction
				LockCodes result = sites[site]->acquireLock(cmd);
				if (result == SharedLockAcquired || result == ExclusiveLockAcquired) {
					return sites[site]->read(cmd);
				}
			}
		}
	}
	return {};
}

LockCodes SiteManager::getWriteLock(Command *cmd) {
	set<int> siteList = reverseCfg[cmd->var];

	set<int> lockedSites;
	for (int site: siteList) {
		if (sites[site]->isSiteUp()) {
			// Same lock is acquired for multiple access to same variables in a transaction
			LockCodes result = sites[site]->acquireLock(cmd);
			if (result != ExclusiveLockAcquired) {
				// Release all locks cuz locking failed
				for (int lockSite : lockedSites) {
					sites[lockSite]->releaseLock(cmd);
				}
				return ExclusiveLockFailed;
			} else {
				lockedSites.insert(site);
			}
		}
	}
	return ExclusiveLockAcquired;
}

set<string> SiteManager::getConflictingLocks(Command *cmd) {
	set<int> siteList = reverseCfg[cmd->var];

	set<string> conflictingTransactions;
	for (int site: siteList) {
		if (sites[site]->isSiteUp()) {
			// Same lock is acquired for multiple access to same variables in a transaction
			set<string> result = sites[site]->getConflictingTransactions(cmd);
			conflictingTransactions.insert(result.begin(), result.end());
		}
	}
	return conflictingTransactions;
}

vector<int> SiteManager::stage(Command *cmd) {
	set<int> siteList = reverseCfg[cmd->var];
	vector<int> stagedSites;
	for (int site: siteList) {
		if (sites[site]->isSiteUp() && sites[site]->hasWriteLock(cmd)) {
			sites[site]->stage(cmd);
			stagedSites.push_back(site);
		}
	}
	return stagedSites;
}

void SiteManager::abort(Transaction *txn) {
	for (auto & site : sites) {
		site.second->abort(txn);
	}
}

void SiteManager::commit(Transaction *txn, const set<int>& commitSites, const string& var) {
	for (int site: commitSites) {
		sites[site]->commit(var);
	}
}

bool SiteManager::wasSiteDownAfter(set<int> siteList, int time) {
	for (auto & site : sites) {
		if (siteList.find(site.first) != siteList.end() && site.second->getLastDownTime() >= time) return true;
	}

	return false;
}

void SiteManager::dump() {
	ostringstream ss;

	for (auto & site : sites) {
		map<string, string> siteData = site.second->getKeyValues();

		ss << "site " << site.first << ":- ";

		vector<string> stringData(siteData.size());
		for (auto & itt : siteData) {
			stringData.push_back(itt.first + ": " + itt.second);
		}

		copy(stringData.begin(), stringData.end(), ostream_iterator<string>(ss, ", "));
		ss << endl;
	}

	cout << ss.str();
}

SiteManager::SiteManager(const map<int, set<string>> &cfg) : cfg(cfg) {

	for (const auto &it : cfg) {
		for (const string &var: it.second) {
			if (reverseCfg[var].empty()) {
				reverseCfg[var] = {};
			}
			reverseCfg[var].insert(it.first);
		}
	}

	for (const auto &it: reverseCfg) {
		if (it.second.size() == 1) {
			if (soleOwner[*it.second.begin()].empty()) {
				soleOwner[*it.second.begin()] = {};
			}
			soleOwner[*it.second.begin()].insert(it.first);
		}
	}

	for (const auto & it : cfg) {
		sites[it.first] = new Site(it.first, it.second, soleOwner[it.first]);
	}
}
