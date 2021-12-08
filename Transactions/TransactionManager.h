//
// Created by Anurag Gupta on 12/4/21.
//

#ifndef REPCREC_TRANSACTIONMANAGER_H
#define REPCREC_TRANSACTIONMANAGER_H

#include <deque>
#include "Commands/Command.h"
#include "../Deadlocks/DeadlockManager.h"
#include "Transaction.h"
#include "../Sites/SiteManager.h"
#include <iostream>
#include "../Clock/GlobalClock.h"

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

		void checkTxnForSiteFail(int site);

		Transaction *getTxn(string txnId);
};


#endif //REPCREC_TRANSACTIONMANAGER_H