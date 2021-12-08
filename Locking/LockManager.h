//
// Created by Vinayak Agarwal on 12/4/21.
//

#ifndef REPCREC_LOCKMANAGER_H
#define REPCREC_LOCKMANAGER_H

#include <map>
#include "Lock.h"
#include "../Transactions/Commands/Command.h"
#include "LockCodes.h"

class LockManager {
		map<string, Lock*> locks;

public:
		LockCodes getReadLock(Command* cmd);
		set<string> testReadLock(Command* cmd);

		LockCodes getWriteLock(Command* cmd);
		set<string> testWriteLock(Command* cmd);

		LockCodes releaseLock(Command* cmd);

		set<string> getConflictingTransactions(Command* cmd);

		bool hasWriteLock(Command *cmd);

		void releaseAllLocks(Transaction* txn);
};


#endif //REPCREC_LOCKMANAGER_H
