//
// Created by Vinayak Agarwal on 12/4/21.
//

#include "Driver.h"

Driver::Driver() {
	sm = new SiteManager();
	tm = new TransactionManager(sm);
}

