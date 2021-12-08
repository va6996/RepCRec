//
// Created by Vinayak Agarwal on 12/4/21.
//

#ifndef REPCREC_COMMAND_H
#define REPCREC_COMMAND_H


#include "CmdType.h"
#include "../Transaction.h"

class Command {
public:
		Command() {
			var = "";
			value = "";
			txnId = "";
			txn = NULL;
		}

		CmdType type;
		int startTime;
		string var;
		string value;
		string txnId;
		Transaction *txn;
};


#endif //REPCREC_COMMAND_H
