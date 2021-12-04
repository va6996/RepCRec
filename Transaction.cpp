//
// Created by Vinayak Agarwal on 12/4/21.
//

#include "Transaction.h"

Transaction::Transaction(string Id, int currTime, TxnType newType) {
	id = Id;
	startTime = currTime;
	type = newType;
	isEnded = false;
}

int Transaction::getStartTime() {
	return startTime;
}

TxnType Transaction::getTxnType() {
	return type;
}

string Transaction::getId() {
	return id;
}

void Transaction::addSites(string variable, vector<int> sites){
	if(!variableSite.count(variable)){
		set<int> site;
		variableSite.insert(make_pair(variable, site));
	}

	for(int i=0;i<sites.size();i++){
		variableSite[variable].insert((sites[i]));
	}
}