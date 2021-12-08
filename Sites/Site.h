//
// Created by Vinayak Agarwal on 12/4/21.
//

#ifndef REPCREC_SITE_H
#define REPCREC_SITE_H


#include "../DataTypes/Variable.h"
#include "../Locking/LockManager.h"
#include "SiteStatus.h"

/**
 * Class representing individual sites
 */
class Site {
		int nodeId;
		SiteStatus status;
		map<string, Variable *> data;
		set<string> singleOwner;
		LockManager *lockManager;
		int lastDownTime;

public:
		Site(int nodeId, const set<string> &vars, const set<string> &singleOwnerVars);

		/**
		 * Fails the given site. Makes lock manager lose all its data.
		 */
		void fail();

		/**
		 * Recovers the given site. Re-initializes lock manager.
		 */
		void recover();

		/**
		 * Determines the type of lock required by the command.
		 * @param cmd The command
		 * @return LockCode indicating success/failure along with LockType
		 */
		LockCodes acquireLock(Command *cmd);

		/**
		 * Releases the lock held by the given transaction of the command
		 * @param cmd The command
		 * @return LockCOde indicating whether lock was released
		 */
		LockCodes releaseLock(Command *cmd);

		/**
		 * Tests whether given command holds a write lock.
		 * @param cmd The command
		 * @return bool representing the result
		 */
		bool hasWriteLock(Command *cmd);

		/**
		 * Tests if a given site is up
		 * @return  bool representing the result
		 */
		bool isSiteUp();

		/**
		 * Reads data for the given command
		 * @param cmd The command
		 * @return Pair containing the result and the site# from which the data was retrieved
		 */
		pair<int, string> read(Command *cmd);

		/**
		 * Reads data for the given command before the given time
		 * @param cmd The command
		 * @param time The time before which the data should be read
		 * @return Pair containing the result and the site# from which the data was retrieved
		 */
		pair<int, string> read(Command *cmd, int time);

		/**
		 * Write data in a temporary storage
		 * @param cmd The command
		 */
		void stage(Command *cmd);

		/**
		 * Make the write permanent by moving staged data to permanent store
		 * @param var The variable to commit
		 */
		void commit(const string &var);

		/**
		 * Release all the locks associated with the transaction
		 * @param txn The transaction
		 */
		void abort(Transaction *txn);

		/**
		 * Get the time when the given site was last down
		 * @return The result
		 */
		int getLastDownTime() const;

		/**
		 * This is called when a read/write fails. Gives the list of transactions that have conflicting locks
		 * @param cmd The command
		 * @return The set of conflicting transactions
		 */
		set<string> getConflictingTransactions(Command *cmd);

		/**
		 * Gives the data held on each site
		 * @return A map containing the result
		 */
		map<string, string> getKeyValues();
};


#endif //REPCREC_SITE_H
