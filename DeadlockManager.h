//
// Created by Vinayak Agarwal on 12/4/21.
//

#ifndef REPCREC_DEADLOCKMANAGER_H
#define REPCREC_DEADLOCKMANAGER_H


#include "Graph.h"

class DeadlockManager {
		Graph graph;

		bool detectDeadlock();
		void resolveDeadlock();
};

#endif //REPCREC_DEADLOCKMANAGER_H
