//
// Created by Vinayak Agarwal on 12/4/21.
//

#include "Site.h"
#include "GlobalClock.h"

void Site::fail() {
	status = Down;
	// Lock status is lost when a site fails
	free(lockManager);
	lastDownTime = GlobalClock::getTime();
}

void Site::recover() {
	status = Up;
	lockManager = new LockManager();
	lastUpTime = GlobalClock::getTime();
}

bool Site::isSiteUp() {
	return status == Up;
}

Site::Site(int nodeId, const set<string>& vars) : nodeId(nodeId){
	lastUpTime = GlobalClock::getTime();
	lastDownTime = -1;
	status = Up;
	lockManager = new LockManager();
	// Add init for all variables
	for (const string& var : vars) {
		data[var] = new Variable(var, to_string(nodeId*10));
	}
}

LockCodes Site::acquireLock(Command* cmd) {
	if (cmd->type == Read) {
		return lockManager->getReadLock(cmd);
	}

	return lockManager->getWriteLock(cmd);
}

LockCodes Site::releaseLock(Command *cmd) {
	return lockManager->releaseLock(cmd);
}

string Site::read(Command *cmd) {
	// Validate if lock exists?
	return data[cmd->var]->getLatestValue();
}

string Site::read(Command *cmd, int time) {
	return data[cmd->var]->getLatestValue(time);
}

bool Site::hasWriteLock(Command *cmd) {
	return lockManager->hasWriteLock(cmd);
}

void Site::stage(Command *cmd) {
	data[cmd->var]->stageValue(cmd->value);
}

void Site::commit(const string& var) {
	data[var]->commitStagedValue();
}

void Site::abort(Transaction *txn) {
	lockManager->releaseAllLocks(txn);
}

int Site::getLastDownTime() {
	return lastDownTime;
}

set<string> Site::getConflictingTransactions(Command *cmd) {
	return lockManager->getConflictingTransactions(cmd);
}

map<string, string> Site::getKeyValues() {
	map<string, string> kvPairs;

	for (auto & it : data) {
		kvPairs[it.first] = it.second->getLatestValue();
	}

	return kvPairs;
}
