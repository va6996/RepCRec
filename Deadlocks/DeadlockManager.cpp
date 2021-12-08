//
// Created by Anurag Gupta on 12/4/21.
//

#include "DeadlockManager.h"

void DeadlockManager::addEdge(const string& t1, const string& t2) {
	if (t1 != t2) {
//        cout<<t1<<" "<<t2<<"******\n";
		if (adjacencyList.count(t1)) {
			adjacencyList[t1].insert(t2);
		} else {
			set<string> edgeL;
			edgeL.insert(t2);
			adjacencyList.insert(make_pair(t1, edgeL));
		}
		nodeList.insert(t1);
		nodeList.insert(t2);
	}
}

void DeadlockManager::removeTransaction(const string& txn) {
	if (adjacencyList.count(txn)) {
		adjacencyList.erase(txn);
	}

	vector<string> keysToRemove;
	for (map<string, set<string>>::iterator it = adjacencyList.begin(); it != adjacencyList.end(); it++) {
		auto currKeyEdges = it->second.find(txn);
		if (currKeyEdges != it->second.end()) {
			it->second.erase(currKeyEdges);
			if (it->second.size() == 0) {
				keysToRemove.push_back(it->first);
			}
		}
	}
	for (int i = 0; i < keysToRemove.size(); i++) {
		adjacencyList.erase(keysToRemove[i]);
	}
	nodeList.erase(txn);
}

bool DeadlockManager::isCycleRec(const string& txn, map<string, bool> &visited, map<string, bool> &recStack) {
	if (!visited[txn]) {
		visited[txn] = true;
		recStack[txn] = true;

		if (adjacencyList.count(txn)) {
			for (const auto & it : adjacencyList[txn]) {
				if (!visited[it] && isCycleRec(it, visited, recStack))
					return true;
				else if (recStack[it])
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
	for (const auto & it : nodeList) {
		visited.insert(make_pair(it, false));
		recurStack.insert(make_pair(it, false));
	}

	for (auto & it : adjacencyList) {
		if (isCycleRec(it.first, visited, recurStack))
			return true;
	}
	return false;
}

vector<string> DeadlockManager::minTransRec(const string& txn, map<string, bool> &visited, map<string, bool> &recStack,
																						map<string, Transaction *> &txnDetails, vector<string> currP) {
	if (!visited[txn]) {
		visited[txn] = true;
		recStack[txn] = true;

		if (adjacencyList.count(txn)) {
			for (const auto & it : adjacencyList[txn]) {
				if (!visited[it]) {
					currP.push_back(it);
					return minTransRec(it, visited, recStack, txnDetails, currP);
				} else if (recStack[it])
					return currP;
			}
		}
	}
	recStack[txn] = false;
	return {};
}

string DeadlockManager::resolveDeadlock(map<string, Transaction *> &txn) {
	map<string, bool> visited;
	map<string, bool> recurStack;
	for (const auto & it : nodeList) {
		visited.insert(make_pair(it, false));
		recurStack.insert(make_pair(it, false));
	}

	for (auto & it : adjacencyList) {
		vector<string> temp;
		temp.push_back(it.first);
		vector<string> res = minTransRec(it.first, visited, recurStack, txn, temp);
		if (!res.empty()) {
			string maxTxn = res[0];
			for (int i = 1; i < res.size(); i++) {
				if (txn[maxTxn]->getStartTime() < txn[res[i]]->getStartTime()) {
					maxTxn = res[i];
				}
			}
			return maxTxn;
		}
	}
	return "";
}