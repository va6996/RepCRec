//
// Created by Anurag Gupta on 12/4/21.
//

#include <iostream>
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

void Transaction::addWriteSites(string variable, vector<int> sites){
    if(!variableWriteSite.count(variable)){
        set<int> site;
        variableWriteSite.insert(make_pair(variable, site));
    }

    for(int i=0;i<sites.size();i++){
        variableWriteSite[variable].insert((sites[i]));
    }
}

void Transaction::addWriteTimes(string variable, int currTime) {
    if(!variableWriteTime.count(variable)){
        variableWriteTime.insert(make_pair(variable, currTime));
    }
}

void Transaction::addReadSites(string variable, vector<int> sites){
    if(!variableReadSite.count(variable)){
        set<int> site;
        variableReadSite.insert(make_pair(variable, site));
    }

    for(int i=0;i<sites.size();i++){
        variableReadSite[variable].insert((sites[i]));
    }
}

void Transaction::addReadTimes(string variable, int currTime) {
    if(!variableReadTime.count(variable)){
        variableReadTime.insert(make_pair(variable, currTime));
    }
}

bool Transaction::writeSiteContains(int site) {
    for (map<string, set<int>>::iterator it = variableWriteSite.begin(); it != variableWriteSite.end(); it++) {
        if(it->second.count(site)!=0){
            return true;
        }
    }
    return false;
}

bool Transaction::readSiteContains(int site) {
    for (map<string, set<int>>::iterator it = variableReadSite.begin(); it != variableReadSite.end(); it++) {
        if(it->second.count(site)!=0){
            return true;
        }
    }
    return false;
}