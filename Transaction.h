//
// Created by Vinayak Agarwal on 12/4/21.
//

#ifndef REPCREC_TRANSACTION_H
#define REPCREC_TRANSACTION_H


#include "Lock.h"
#include "TxnType.h"

class Transaction {
		string id;
		int startTime;
		vector<Lock*> locks;
		TxnType type;
};


#endif //REPCREC_TRANSACTION_H
