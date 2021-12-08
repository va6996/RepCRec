//
// Created by Vinayak Agarwal on 12/4/21.
//

#ifndef REPCREC_LOCKMANAGER_H
#define REPCREC_LOCKMANAGER_H

#include <map>
#include "Lock.h"
#include "../Transactions/Commands/Command.h"
#include "LockCodes.h"
/**
 * Class representing a lock manager located on each site.
 */
class LockManager {
		map<string, Lock *> locks;

public:
		/**
		 * Determines the type of lock required by the command.
		 * @param cmd The command
		 * @return LockCode indicating success/failure along with LockType
		 */
		LockCodes getReadLock(Command *cmd);

		/**
		 * Determines whether a command can lock required variables and return conflicting locks otherwise.
		 * @param cmd The command
		 * @return set of conflicting transactions, if any
		 */
		set<string> testReadLock(Command *cmd);

		/**
		 * Determines the type of lock required by the command.
		 * @param cmd The command
		 * @return LockCode indicating success/failure along with LockType
		 */
		LockCodes getWriteLock(Command *cmd);

		/**
		 * Determines whether a command can lock required variables and return conflicting locks otherwise.
		 * @param cmd The command
		 * @return set of conflicting transactions, if any
		 */
		set<string> testWriteLock(Command *cmd);

		/**
		 * Releases the lock held by the given transaction of the command
		 * @param cmd The command
		 * @return LockCOde indicating whether lock was released
		 */
		LockCodes releaseLock(Command *cmd);

		/**
		 * This is called when a read/write fails. Gives the list of transactions that have conflicting locks
		 * @param cmd The command
		 * @return The set of conflicting transactions
		 */
		set<string> getConflictingTransactions(Command *cmd);

		/**
		 * Tests whether given command holds a write lock.
		 * @param cmd The command
		 * @return bool representing the result
		 */
		bool hasWriteLock(Command *cmd);

		/**
		 * Releases all the locks held by the given transaction
		 * @param txn The transaction
		 */
		void releaseAllLocks(Transaction *txn);
};


#endif //REPCREC_LOCKMANAGER_H
