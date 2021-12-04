//
// Created by Vinayak Agarwal on 12/4/21.
//

#ifndef REPCREC_LOCKMANAGER_H
#define REPCREC_LOCKMANAGER_H

#include <map>
#include "Lock.h"
#include "Command.h"
#include "LockCodes.h"

class LockManager {
		map<string, Lock*> locks;

		LockCodes getReadLock(Command* cmd);
		LockCodes getWriteLock(Command* cmd);
		LockCodes releaseLock(Command* cmd);
};


#endif //REPCREC_LOCKMANAGER_H
