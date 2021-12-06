//
// Created by Vinayak Agarwal on 12/4/21.
//

#include <iostream>
#include "LockManager.h"

LockCodes LockManager::getReadLock(Command* cmd) {
	Lock *lock = locks[cmd->var];

	if (lock == nullptr) {
		lock = new Lock(Shared, cmd->var, cmd->txn->getId());
		locks[cmd->var] = lock;
		return SharedLockAcquired;
	}

    if(lock->getLockOwnersSize()==0){
        lock->addTransaction(cmd->txnId);
        locks[cmd->var] = lock;
        return SharedLockAcquired;
    }

	if (lock->getLockType() == Exclusive) {
		// Return highest type of lock type only
		return lock->getSoleLockOwner() == cmd->txn->getId() ? ExclusiveLockAcquired : SharedLockFailed;
	}

	lock->addTransaction(cmd->txn->getId());
	return SharedLockAcquired;
}

set<string> LockManager::testReadLock(Command* cmd) {
	Lock *lock = locks[cmd->var];

	set<string> conflictingTransactions;
	// Will read locks ever conflict?
    if (lock != nullptr && lock->getLockType() == Exclusive && lock->getSoleLockOwner() != cmd->txn->getId())
        conflictingTransactions.insert(lock->getSoleLockOwner());

	return conflictingTransactions;
}

LockCodes LockManager::getWriteLock(Command *cmd) {
	Lock *lock = locks[cmd->var];

	if (lock == nullptr) {
		lock = new Lock(Exclusive, cmd->var, cmd->txn->getId());
		locks[cmd->var] = lock;
		return ExclusiveLockAcquired;
	}

    if(lock->getLockOwnersSize()==0){
        lock->addTransaction(cmd->txnId);
        locks[cmd->var] = lock;
        return ExclusiveLockAcquired;
    }

	if (lock->getLockType() == Exclusive) {
		// Return highest type of lock type only
		return lock->getSoleLockOwner() == cmd->txn->getId() ? ExclusiveLockAcquired : ExclusiveLockFailed;
	}

	if (lock->getLockOwnersSize() > 1) {
		return ExclusiveLockFailed;
	}

	if (lock->getSoleLockOwner() == cmd->txn->getId()) {
		lock->promoteLock();
		return ExclusiveLockAcquired;
	}

	return ExclusiveLockFailed;
}

set<string> LockManager::testWriteLock(Command* cmd) {
	Lock *lock = locks[cmd->var];

	set<string> conflictingTransactions;
	if (lock == nullptr)
		return conflictingTransactions;
	if (lock != nullptr && lock->getLockType() == Exclusive && lock->getSoleLockOwner() != cmd->txn->getId()) {
		// Return highest type of lock type only
		conflictingTransactions.insert(lock->getSoleLockOwner());
	}

	if (lock->getLockOwnersSize() > 1) {
		return lock->getTransactions();
	}

    if (lock != nullptr && lock->getLockType() == Shared && lock->getLockOwnersSize()>0)
        if(lock->getSoleLockOwner() != cmd->txn->getId())
            conflictingTransactions.insert(lock->getSoleLockOwner());

    return conflictingTransactions;
}

LockCodes LockManager::releaseLock(Command *cmd) {
	Lock *lock = locks[cmd->var];

	if (lock == nullptr) {
		return FatalError;
	}

	bool result = lock->removeTransaction(cmd->txn->getId());

	if (!result) {
		return FatalError;
	}

	if (lock->getLockOwnersSize() == 0) {
		LockType type = lock->getLockType();
		free(lock);
		locks.erase(cmd->var);
		return type == Exclusive ? ExclusiveLockReleased : SharedLockReleased;
	}

	return SharedLockReleased;
}

bool LockManager::hasWriteLock(Command *cmd) {
	Lock *lock = locks[cmd->var];
	if (lock == nullptr) return false;
	if (lock->getLockType() != Exclusive) return false;
	if (lock->getSoleLockOwner() != cmd->txn->getId()) return false;
	return true;
}

void LockManager::releaseAllLocks(Transaction* txn) {
	for (auto & lock : locks) {
        if(lock.second)
		    lock.second->removeTransaction(txn->getId());
	}
}

set<string> LockManager::getConflictingTransactions(Command *cmd) {
    if (cmd->type == Read) {
        return testReadLock(cmd);
    } else {
        return testWriteLock(cmd);
    }
}
