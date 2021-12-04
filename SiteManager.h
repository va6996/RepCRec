//
// Created by Vinayak Agarwal on 12/4/21.
//

#ifndef REPCREC_SITEMANAGER_H
#define REPCREC_SITEMANAGER_H


#include "Site.h"

class SiteManager {
		vector<Site*> data;

		void fail(int nodeId);
		void recover(int nodeId);
};


#endif //REPCREC_SITEMANAGER_H
