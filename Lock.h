//
// Created by Vinayak Agarwal on 12/4/21.
//

#ifndef REPCREC_LOCK_H
#define REPCREC_LOCK_H

#include <set>
#include "LockType.h"
#include "Variable.h"

class Lock {
		LockType type;
		string var;
		set<string> transactions;

public:
		Lock(LockType type, string var, const string& txnId);
		bool addTransaction(const string& txnId);
		bool removeTransaction(const string& txnId);
		LockType getLockType();
		string getSoleLockOwner();
		int getLockOwnersSize();
		bool promoteLock();
		set<string> getTransactions();
};


#endif //REPCREC_LOCK_H
