//
// Created by Vinayak Agarwal on 12/4/21.
//

#ifndef REPCREC_LOCK_H
#define REPCREC_LOCK_H

#include <set>
#include "LockType.h"
#include "../DataTypes/Variable.h"

/**
 * Class representing individual locks
 */
class Lock {
		LockType type;
		string var;
		set<string> transactions;

public:
		Lock(LockType type, string var, const string &txnId);

		/**
		 * Adds transaction to list of transactions holding lock
		 * @param txnId The transaction
		 * @return whether operation was successful
		 */
		bool addTransaction(const string &txnId);

		/**
		 * Removes transaction from the list of transactions holding lock
		 * @param txnId The transaction
		 * @return whether operation was successful
		 */
		bool removeTransaction(const string &txnId);

		/**
		 * Return type of lock held
		 * @return the type
		 */
		LockType getLockType();

		/**
		 * Returns the owner of the lock
		 * @return the owner
		 */
		string getSoleLockOwner();

		/**
		 * Returns number of transactions holding the lock
		 * @return the count
		 */
		int getLockOwnersSize();

		/**
		 * Convert shared lock to exclusive lock
		 * @return whether operation was successful
		 */
		bool promoteLock();

		/**
		 * Return the list of transactions holding the lock
		 * @return the result of operation
		 */
		set<string> getTransactions();
};


#endif //REPCREC_LOCK_H
