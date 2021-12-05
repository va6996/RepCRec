//
// Created by Vinayak Agarwal on 12/4/21.
//

#ifndef REPCREC_LOCKCODES_H
#define REPCREC_LOCKCODES_H


enum LockCodes {
	SharedLockFailed, ExclusiveLockFailed,
	SharedLockAcquired, ExclusiveLockAcquired,
	SharedLockReleased, ExclusiveLockReleased,
	FatalError, StaleData
};


#endif //REPCREC_LOCKCODES_H
