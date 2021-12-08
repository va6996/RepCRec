//
// Created by Anurag Gupta on 12/4/21.
//

#ifndef REPCREC_TRANSACTION_H
#define REPCREC_TRANSACTION_H

#include <map>
#include <set>
#include <list>
#include "../Locking/Lock.h"
#include "TxnType.h"

/**
 * Class responsible for storing details about the transaction
 * Stores the start time, type of txn, id of txn and
 * the sites accessed for read/write operations.
 */
class Transaction {
		int startTime;
		string id;
		TxnType type;

public:
		map<string, set<int>> variableWriteSite;
		map<string, int> variableWriteTime;
		map<string, set<int>> variableReadSite;
		map<string, int> variableReadTime;
		bool isEnded;
		string endMsg;

		Transaction(string Id, int currTime, TxnType newType);

        /**
         * Function to get the start time of txn
         * @return start time of txn
         */
		int getStartTime() const;

        /**
         * Function to get type of txn
         * @return type of txn
         */
		TxnType getTxnType();

        /**
         * Function to get the ID of txn
         * @return ID of txn
         */
		string getId();

        /**
         * Function to store the list of sited accessed to write the value of variable
         * @param variable variable written to
         * @param sites list of sites accessed
         */
		void addWriteSites(const string& variable, vector<int> sites);

        /**
         * Function to store the time of the write operation for a given variable
         * @param variable variable written to
         * @param currTime time of the operation
         */
		void addWriteTimes(const string& variable, int currTime);

        /**
         * Function to store the list of sites accessed to read the value of variable
         * @param variable variable read
         * @param sites list of sites accessed
         */
		void addReadSites(const string& variable, vector<int> sites);

        /**
         * Function to store the time of read operation for a given variable
         * @param variable variable read
         * @param currTime time of the operation
         */
		void addReadTimes(const string& variable, int currTime);

        /**
         * checks if txn has written to the site
         * @param site Site to be check
         * @return true if txn has written to the site
         */
		bool writeSiteContains(int site);

        /**
         * checks if txn had read from the site
         * @param site Site to be check
         * @return true if txn has read from site
         */
		bool readSiteContains(int site);
};


#endif //REPCREC_TRANSACTION_H
