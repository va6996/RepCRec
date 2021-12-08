//
// Created by Anurag Gupta on 12/4/21.
//

#ifndef REPCREC_DRIVER_H
#define REPCREC_DRIVER_H


#include "TransactionManager.h"
#include "SiteManager.h"
#include "GlobalClock.h"
#include <string.h>


class Driver {
		TransactionManager *tm;
		SiteManager *sm;
//		GlobalClock *gc;
		vector<string> getArgs(string str);

public:
		Driver();

		void processLine(const string& line);
		void printDump();
		void queryState();
		void printValue(Variable var);
};


#endif //REPCREC_DRIVER_H
