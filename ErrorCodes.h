//
// Created by Vinayak Agarwal on 12/4/21.
//

#ifndef REPCREC_ERRORCODES_H
#define REPCREC_ERRORCODES_H


enum ErrorCodes {
	SiteDown, VariableNotExists, StaleVariable, ReadLockFailed, WriteLockFailed, TxnAbortedDeadlock
};


#endif //REPCREC_ERRORCODES_H
