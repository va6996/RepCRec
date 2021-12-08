//
// Created by Vinayak Agarwal on 12/4/21.
//

#include "Lock.h"

#include <utility>
#include <cassert>

Lock::Lock(LockType type, string var, const string &txnId) : type(type), var(std::move(var)) {
	transactions.insert(txnId);
}

bool Lock::addTransaction(const string &txnId) {
	transactions.insert(txnId);
	return true;
}

bool Lock::removeTransaction(const string &txnId) {
	if (transactions.find(txnId) == transactions.end())
		return false;

	transactions.erase(txnId);
	return true;
}

LockType Lock::getLockType() {
	return type;
}

string Lock::getSoleLockOwner() {
	assert(transactions.size() == 1);
	return *transactions.begin();
}

int Lock::getLockOwnersSize() {
	return (int) transactions.size();
}

bool Lock::promoteLock() {
	type = Exclusive;
	return true;
}

set<string> Lock::getTransactions() {
	return transactions;
}
