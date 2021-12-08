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

class Transaction {
		int startTime;
		vector<Lock *> locks;
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

		int getStartTime() const;

		TxnType getTxnType();

		string getId();

		void addWriteSites(const string& variable, vector<int> sites);

		void addWriteTimes(const string& variable, int currTime);

		void addReadSites(const string& variable, vector<int> sites);

		void addReadTimes(const string& variable, int currTime);

		bool writeSiteContains(int site);

		bool readSiteContains(int site);
};


#endif //REPCREC_TRANSACTION_H
