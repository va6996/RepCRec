//
// Created by Vinayak Agarwal on 12/4/21.
//

#ifndef REPCREC_LOCK_H
#define REPCREC_LOCK_H


#include "LockType.h"
#include "Variable.h"

class Lock {
		LockType type;
		Variable var;
		string owner;
};


#endif //REPCREC_LOCK_H
