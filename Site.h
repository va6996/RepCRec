//
// Created by Vinayak Agarwal on 12/4/21.
//

#ifndef REPCREC_SITE_H
#define REPCREC_SITE_H


#include "Variable.h"
#include "LockManager.h"
#include "SiteStatus.h"

class Site {
		int nodeId;
		SiteStatus status;
		map<string, Variable*> data;
		set<string> singleOwner;
		LockManager* lockManager;
		int lastDownTime;
		int lastUpTime;

public:
		Site(int nodeId, const set<string>& vars, const set<string> &singleOwnerVars);

		void fail();

		void recover();

		LockCodes acquireLock(Command* cmd);
		LockCodes releaseLock(Command* cmd);
		bool hasWriteLock(Command *cmd);

		bool isSiteUp();
		string read(Command *cmd);
		string read(Command *cmd, int time);
		void stage(Command *cmd);
		void commit(const string& var);
		void abort(Transaction *txn);
		int getLastDownTime();
		set<string> getConflictingTransactions(Command* cmd);
		map<string, string> getKeyValues();
};


#endif //REPCREC_SITE_H
