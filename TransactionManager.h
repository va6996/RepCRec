//
// Created by Vinayak Agarwal on 12/4/21.
//

#ifndef REPCREC_TRANSACTIONMANAGER_H
#define REPCREC_TRANSACTIONMANAGER_H

#include <deque>
#include "Command.h"
#include "DeadlockManager.h"
#include "Transaction.h"
#include "SiteManager.h"
#include <iostream>
#include "GlobalClock.h"

using namespace std;

class TransactionManager {
		map<string, list<Command *> *> waitQueue;

		DeadlockManager *dm;
		SiteManager *sm;
		map<string, Transaction *> txnList;

		void executeRead(Command *cmd);
		void executeWrite(Command *cmd);
		void detectResolveDeadlock();
		void checkWaitQueue();
        bool canExecuteRW(Command *cmd);
public:
		TransactionManager(SiteManager *siteManager);

		void beingTxn(string txnId, TxnType type, int currTime);
		void endTxn(string txnId);
		void executeCmd(Command *cmd);
		void beforeCommandChecks();
        Transaction *getTxn(string txnId);
};


#endif //REPCREC_TRANSACTIONMANAGER_H
