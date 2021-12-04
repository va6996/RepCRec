//
// Created by Vinayak Agarwal on 12/4/21.
//

#ifndef REPCREC_DEADLOCKMANAGER_H
#define REPCREC_DEADLOCKMANAGER_H


#include <map>
#include <set>
#include "Transaction.h"

class DeadlockManager {
		map<string, set<string>> adjacencyList;
		set<string> nodeList;

public:
		void addEdge(string t1, string t2);
		void removeTransaction(string txn);
		bool isCycleRec(string txn, map<string, bool> &visited, map<string, bool> &recStack);
		bool detectDeadlock();
		string minTransRec(string txn, map<string, bool> &visited, map<string, bool> &recStack, map<string, Transaction *> &txnDetails);
		string resolveDeadlock(map<string, Transaction*> &txn);
};

#endif //REPCREC_DEADLOCKMANAGER_H
