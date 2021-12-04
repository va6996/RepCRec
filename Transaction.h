//
// Created by Vinayak Agarwal on 12/4/21.
//

#ifndef REPCREC_TRANSACTION_H
#define REPCREC_TRANSACTION_H

#include <map>
#include <set>
#include <list>
#include "Lock.h"
#include "TxnType.h"

class Transaction {
		int startTime;
		vector<Lock*> locks;
		TxnType type;

public:
		map<string, set<int>> variableSite;
		bool isEnded;

		Transaction(string Id, int currTime, TxnType newType);
		int getStartTime();
		TxnType getTxnType();
		string getId();
		void addSites(string variable, vector<int> sites);
};


#endif //REPCREC_TRANSACTION_H
