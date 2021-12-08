//
// Created by Anurag Gupta on 12/4/21.
//

#ifndef REPCREC_DRIVER_H
#define REPCREC_DRIVER_H


#include "../Transactions/TransactionManager.h"
#include "../Sites/SiteManager.h"
#include "../Clock/GlobalClock.h"
#include <cstring>

/**
 * Class responsible to read a line from input file and
 * co-ordinate with transaction manager, site manager
 * and handle time increments
 */
class Driver {
		TransactionManager *tm;
		SiteManager *sm;

        /**
         * Returns tokens for a given line
         * @param str contains the current line
         * @return array of tokens which can be begin,beginRO,end,dump,R,W or txn or variable number
         */
		vector<string> getArgs(string str);

public:
		Driver();

        /**
         * Responsible for calling Txn Manager or Site Manager for a given command.
         * Also, checks for deadlock and Waiting Txns
         * @param line current file line
         */
		void processLine(const string &line);
};


#endif //REPCREC_DRIVER_H
