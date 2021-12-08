//
// Created by Vinayak Agarwal on 12/4/21.
//

#ifndef REPCREC_SITEMANAGER_H
#define REPCREC_SITEMANAGER_H

#include <map>
#include "Site.h"
#include <iterator>

class SiteManager {
		map<int, Site*> sites;
		map<int, set<string>> cfg;
		map<int, set<string>> soleOwner;
		map<string, set<int>> reverseCfg;
public:
		SiteManager(const map<int, set<string>> &cfg);

		pair<string, int> read(Command *cmd);
		LockCodes getWriteLock(Command *cmd);
		set<string> getConflictingLocks(Command *cmd);
		vector<int> stage(Command *cmd);
		void abort(Transaction *txn);
		void commit(Transaction *txn, const set<int>& commitSites, const string& var);
		bool wasSiteDownAfter(set<int> sites, int time);
		void dump();

		void fail(int nodeId);
		void recover(int nodeId);};


#endif //REPCREC_SITEMANAGER_H
