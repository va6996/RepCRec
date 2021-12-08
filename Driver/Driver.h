//
// Created by Anurag Gupta on 12/4/21.
//

#ifndef REPCREC_DRIVER_H
#define REPCREC_DRIVER_H


#include "../Transactions/TransactionManager.h"
#include "../Sites/SiteManager.h"
#include "../Clock/GlobalClock.h"
#include <cstring>


class Driver {
		TransactionManager *tm;
		SiteManager *sm;

		vector<string> getArgs(string str);

public:
		Driver();

		void processLine(const string &line);
};


#endif //REPCREC_DRIVER_H
