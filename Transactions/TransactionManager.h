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

/**
 * Class responsible for managing all
 * transaction related operations. The class
 * checks for deadlock, manages waiting operations
 * and reads/writes data for all txns
 */
class TransactionManager {
		map<string, list<Command *> *> waitQueue;

		DeadlockManager *dm;
		SiteManager *sm;
		map<string, Transaction *> txnList;

        /**
         * Function responsible for reading the
         * data from sites. If txn cannot acquire
         * lock, then the command is added to wait queue
         * @param cmd current cmd containing txn details, variable name
         */
		void executeRead(Command *cmd);

        /**
         * Function responsible for writing the
         * data to all sites. If txn cannot acquire
         * lock, then the command is added to wait queue
         * @param cmd current cmd containing txn details, variable name and value
         */
		void executeWrite(Command *cmd);

        /**
         * Functions checks if a deadlock is caused
         * by the current set of commands for txns
         * If a deadlock is present, then the youngest
         * txn is aborted.
         */
		void detectResolveDeadlock();

        /**
         * Checks wait queue for each variable,
         * and execute all the commands that can
         * be execute at that point of time.
         */
		void checkWaitQueue();

        /**
         * Function checks if the read/write operations
         * can be performed by the current txn.
         * Checks if any other txn is already waiting for
         * the locks for same variable as current txn
         * @param cmd current command containing details about txn, variable, operation type.
         * @return true if the current command can be executed
         */
		bool canExecuteRW(Command *cmd);

public:
		TransactionManager(SiteManager *siteManager);

        /**
         * starts a new transactions and adds the txn object to txnList
         * @param txnId ID of new transaction
         * @param type  Type of new transaction
         * @param currTime Start time of new transaction
         */
		void beingTxn(string txnId, TxnType type, int currTime);

        /**
         * ends an ongoing transaction. Checks if the txn can
         * be committed or has to be aborted. Performs necessary action.
         * @param txnId ID of the txn ending
         */
		void endTxn(string txnId);

        /**
         * Checks if the current command is a read or write and
         * executes the command by calling read or write function
         * @param cmd current command to be executed
         */
		void executeCmd(Command *cmd);

        /**
         * Performs a check for deadlock and also checks
         * the wait queue to see is any of existing commands
         * can be executed.
         */
		void beforeCommandChecks();

        /**
         * Checks if any txn had accesses the site. If any txn
         * has read/write from site, then the txn is aborted
         * @param site the site that failed
         */
		void checkTxnForSiteFail(int site);

        /**
         * Function to get txn object
         * @param txnId ID of the txn
         * @return object of txn
         */
		Transaction *getTxn(string txnId);
};


#endif //REPCREC_TRANSACTIONMANAGER_H
