//
// Created by Vinayak Agarwal on 12/4/21.
//

#ifndef REPCREC_DRIVER_H
#define REPCREC_DRIVER_H


#include "TransactionManager.h"
#include "SiteManager.h"

class Driver {
		TransactionManager tm;
		SiteManager sm;

		void readLine(istream file);
		void printDump();
		void queryState();
		void printValue(Variable var);
};


#endif //REPCREC_DRIVER_H
