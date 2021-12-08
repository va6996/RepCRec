//
// Created by Anurag Gupta on 12/4/21.
//

#ifndef REPCREC_DEADLOCKMANAGER_H
#define REPCREC_DEADLOCKMANAGER_H


#include <map>
#include <set>
#include "../Transactions/Transaction.h"
#include "iostream"
using namespace std;

class DeadlockManager {
		map<string, set<string>> adjacencyList;
		set<string> nodeList;

public:
		void addEdge(string t1, string t2);
		void removeTransaction(string txn);
		bool isCycleRec(string txn, map<string, bool> &visited, map<string, bool> &recStack);
		bool detectDeadlock();
        vector<string> minTransRec(string txn, map<string, bool> &visited, map<string, bool> &recStack, map<string, Transaction *> &txnDetails, vector<string> currP);
		string resolveDeadlock(map<string, Transaction*> &txn);
};

#endif //REPCREC_DEADLOCKMANAGER_H
