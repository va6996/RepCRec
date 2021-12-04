//
// Created by Vinayak Agarwal on 12/4/21.
//

#include "DeadlockManager.h"

void DeadlockManager::addEdge(string t1, string t2){
	if(adjacencyList.count(t1)){
		adjacencyList[t1].insert(t2);
	} else{
		set<string> edgeL;
		edgeL.insert(t2);
		adjacencyList.insert(make_pair(t1, edgeL));
	}
	nodeList.insert(t1);
	nodeList.insert(t2);
}

void DeadlockManager::removeTransaction(string txn){
	if(adjacencyList.count(txn)){
		adjacencyList.erase(txn);
	}

	vector<string> keysToRemove;
	for (map<string, set<string>>::iterator it = adjacencyList.begin(); it != adjacencyList.end(); it++){
		set<string>::iterator currKeyEdges = it->second.find(txn);
		if(currKeyEdges != it->second.end()){
			it->second.erase(currKeyEdges);
			if(it->second.size()==0){
				keysToRemove.push_back(it->first);
			}
		}
	}
	for(int i=0;i<keysToRemove.size();i++){
		adjacencyList.erase(keysToRemove[i]);
	}
	nodeList.erase(txn);
}

bool DeadlockManager::isCycleRec(string txn, map<string, bool> &visited, map<string, bool> &recStack){
	if(!visited[txn]){
		visited[txn] = true;
		recStack[txn] = true;

		if(adjacencyList.count(txn)) {
			for(set<string>::iterator it = adjacencyList[txn].begin(); it != adjacencyList[txn].end(); it++){
				if(!visited[*it] && isCycleRec(*it, visited, recStack))
					return true;
				else if(recStack[*it])
					return true;
			}
		}
	}
	recStack[txn] = false;
	return false;
}

bool DeadlockManager::detectDeadlock() {
	map<string, bool> visited;
	map<string, bool> recurStack;
	for (set<string>::iterator it = nodeList.begin(); it != nodeList.end(); it++){
		visited.insert(make_pair(*it, false));
		recurStack.insert(make_pair(*it, false));
	}

	for (map<string, set<string>>::iterator it = adjacencyList.begin(); it != adjacencyList.end(); it++) {
		if (isCycleRec(it->first, visited, recurStack))
			return true;
	}
	return false;
}

string DeadlockManager::minTransRec(string txn, map<string, bool> &visited, map<string, bool> &recStack, map<string, Transaction *> &txnDetails) {
	if(!visited[txn]){
		visited[txn] = true;
		recStack[txn] = true;

		if(adjacencyList.count(txn)) {
			for(set<string>::iterator it = adjacencyList[txn].begin(); it != adjacencyList[txn].end(); it++){
				if(!visited[*it]){
					string cycleTxn = minTransRec(*it, visited, recStack, txnDetails);
					if(cycleTxn!=""){
						if(txnDetails[txn]->getStartTime() > txnDetails[cycleTxn]->getStartTime() )
							return txn;
						else return cycleTxn;
					}
				}
				else if(recStack[*it])
					return *it;
			}
		}
	}
	recStack[txn] = false;
	return "";
}

string DeadlockManager::resolveDeadlock(map<string, Transaction *> &txn){
	map<string, bool> visited;
	map<string, bool> recurStack;
	for (set<string>::iterator it = nodeList.begin(); it != nodeList.end(); it++){
		visited.insert(make_pair(*it, false));
		recurStack.insert(make_pair(*it, false));
	}

	for (map<string, set<string>>::iterator it = adjacencyList.begin(); it != adjacencyList.end(); it++) {
		string txnName = minTransRec(it->first, visited, recurStack, txn);
		if (txnName != "")
			return txnName;
	}
}