//
// Created by Vinayak Agarwal on 12/4/21.
//

#ifndef REPCREC_LOCKMANAGER_H
#define REPCREC_LOCKMANAGER_H


#include "Lock.h"
#include "Command.h"

class LockManager {
		vector<Lock*> locks;

		bool getReadLock(Command cmd);
		bool getWriteLock(Command cmd);
		bool releaseLock(Lock lock);
};


#endif //REPCREC_LOCKMANAGER_H
