//
// Created by Anurag Gupta on 12/4/21.
//

#include <iostream>
#include <utility>
#include "Transaction.h"

Transaction::Transaction(string Id, int currTime, TxnType newType) {
	id = std::move(Id);
	startTime = currTime;
	type = newType;
	isEnded = false;
}

int Transaction::getStartTime() const {
	return startTime;
}

TxnType Transaction::getTxnType() {
	return type;
}

string Transaction::getId() {
	return id;
}

void Transaction::addWriteSites(const string& variable, vector<int> sites) {
	if (!variableWriteSite.count(variable)) {
		set<int> site;
		variableWriteSite.insert(make_pair(variable, site));
	}

	for (int i = 0; i < sites.size(); i++) {
		variableWriteSite[variable].insert((sites[i]));
	}
}

void Transaction::addWriteTimes(const string& variable, int currTime) {
	if (!variableWriteTime.count(variable)) {
		variableWriteTime.insert(make_pair(variable, currTime));
	}
}

void Transaction::addReadSites(const string& variable, vector<int> sites) {
	if (!variableReadSite.count(variable)) {
		set<int> site;
		variableReadSite.insert(make_pair(variable, site));
	}

	for (int i = 0; i < sites.size(); i++) {
		variableReadSite[variable].insert((sites[i]));
	}
}

void Transaction::addReadTimes(const string& variable, int currTime) {
	if (!variableReadTime.count(variable)) {
		variableReadTime.insert(make_pair(variable, currTime));
	}
}

bool Transaction::writeSiteContains(int site) {
	for (auto & it : variableWriteSite) {
		if (it.second.count(site) != 0) {
			return true;
		}
	}
	return false;
}

bool Transaction::readSiteContains(int site) {
	for (auto & it : variableReadSite) {
		if (it.second.count(site) != 0) {
			return true;
		}
	}
	return false;
}