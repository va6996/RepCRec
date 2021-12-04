//
// Created by Vinayak Agarwal on 12/4/21.
//

#ifndef REPCREC_SITE_H
#define REPCREC_SITE_H


#include "Variable.h"
#include "LockManager.h"

class Site {
		int nodeId;
		vector<Variable*> data;
		LockManager* lockManager;
		int lastDownTime;
		int lastUptime;

		bool isSiteUp();
		void fail();
		void recover();
};


#endif //REPCREC_SITE_H
