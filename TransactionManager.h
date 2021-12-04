//
// Created by Vinayak Agarwal on 12/4/21.
//

#ifndef REPCREC_TRANSACTIONMANAGER_H
#define REPCREC_TRANSACTIONMANAGER_H

#include <deque>
#include "Command.h"
#include "DeadlockManager.h"

class TransactionManager {
		deque<Command> waitQueue;
		DeadlockManager dm;

		void commitTxn(Transaction txn);
		void abortTxn(Transaction txn);
		bool executeCmd(Command cmd);
		void updateGraph(string src, string dst);
		void detectResolveDeadlock(DeadlockManager dm);
};


#endif //REPCREC_TRANSACTIONMANAGER_H
