//
// Created by Vinayak Agarwal on 12/4/21.
//

#include "LockManager.h"

LockCodes LockManager::getReadLock(Command* cmd) {
	Lock *lock = locks[cmd->var];

	if (lock == nullptr) {
		lock = new Lock(Shared, cmd->var, cmd->txn.id);
		locks[cmd->var] = lock;
		return SharedLockAcquired;
	}

	if (lock->getLockType() == Exclusive) {
		// Return highest type of lock type only
		return lock->getSoleLockOwner() == cmd->txn.id ? ExclusiveLockAcquired : SharedLockFailed;
	}

	lock->addTransaction(cmd->txn.id);
	return SharedLockAcquired;
}

LockCodes LockManager::getWriteLock(Command *cmd) {
	Lock *lock = locks[cmd->var];

	if (lock == nullptr) {
		lock = new Lock(Exclusive, cmd->var, cmd->txn.id);
		locks[cmd->var] = lock;
		return ExclusiveLockAcquired;
	}

	if (lock->getLockType() == Exclusive) {
		// Return highest type of lock type only
		return lock->getSoleLockOwner() == cmd->txn.id ? ExclusiveLockAcquired : ExclusiveLockFailed;
	}

	if (lock->getLockOwnersSize() > 1) {
		return ExclusiveLockFailed;
	}

	if (lock->getSoleLockOwner() == cmd->txn.id) {
		lock->promoteLock();
		return ExclusiveLockAcquired;
	}

	return ExclusiveLockFailed;
}

LockCodes LockManager::releaseLock(Command *cmd) {
	Lock *lock = locks[cmd->var];

	if (lock == nullptr) {
		return FatalError;
	}

	bool result = lock->removeTransaction(cmd->txn.id);

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
