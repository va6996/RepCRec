//
// Created by Vinayak Agarwal on 12/4/21.
//

#include "TransactionManager.h"

TransactionManager::TransactionManager(SiteManager *siteManager){
	dm = new DeadlockManager();
	sm = siteManager;
}

void TransactionManager::beingTxn(string txnId, TxnType type, int currTime){
	Transaction *txn = new Transaction(txnId, currTime, type);
	txnList.insert(make_pair(txnId, txn));
}

void TransactionManager::executeCmd(Command *cmd) {
	if(Read == cmd->type)
		executeRead(cmd);
	else executeWrite(cmd);
}

void TransactionManager::executeRead(Command *cmd){
	string val = sm->read(cmd);
	if(val != "")
		cout<<cmd->var<<": "<<val<<"\n";
	else {
		set<string> conflictingTxn = sm->getConflictingLocks(cmd);
		for(set<string>::iterator it = conflictingTxn.begin(); it != conflictingTxn.end(); it++) {
			dm->addEdge(cmd->txnId, *it);
		}

		if(waitQueue.count(cmd->var)){
			for(list<Command *>::iterator it = waitQueue[cmd->var].begin(); it != waitQueue[cmd->var].end(); it++){
				dm->addEdge(cmd->txnId, (*it)->txnId);
			}
			waitQueue[cmd->var].push_back(cmd);
		} else{
			list<Command *> newW;
			newW.push_back(cmd);
			waitQueue.insert(make_pair(cmd->var, newW));
		}
	}
}

void TransactionManager::executeWrite(Command *cmd){
	if(sm->getWriteLock(cmd) == SharedLockAcquired){
		vector<int> writeSite = sm->stage(cmd);
		txnList[cmd->txnId]->addSites(cmd->var, writeSite);
	} else {
		set<string> conflictingTxn = sm->getConflictingLocks(cmd);
		for(set<string>::iterator it = conflictingTxn.begin(); it != conflictingTxn.end(); it++) {
			dm->addEdge(cmd->txnId, *it);
		}

		if(waitQueue.count(cmd->var)){
			for(list<Command *>::iterator it = waitQueue[cmd->var].begin(); it != waitQueue[cmd->var].end(); it++){
				dm->addEdge(cmd->txnId, (*it)->txnId);
			}
			waitQueue[cmd->var].push_back(cmd);
		} else{
			list<Command *> newW;
			newW.push_back(cmd);
			waitQueue.insert(make_pair(cmd->var, newW));
		}
	}
}

void TransactionManager::detectResolveDeadlock(){
	if(dm->detectDeadlock()){
		string txn = dm->resolveDeadlock(txnList);
		sm->abort(txnList[txn]);
		dm->removeTransaction(txn);
		txnList[txn]->isEnded = true;
		cout<<txn<<" Aborted\n";
	}
}

void TransactionManager::endTxn(string txnId) {
	Transaction *txn = txnList[txnId];
	txn->isEnded = true;

	bool canWriteAll = true;
	for(map<string, set<int>>::iterator it = txn->variableSite.begin(); it != txn->variableSite.end(); it++){
		if(sm->wasSiteDownAfter(it->second, txn->getStartTime())){
			canWriteAll = false;
			break;
		}
	}
	if(canWriteAll) {
		for (map<string, set<int>>::iterator it = txn->variableSite.begin(); it != txn->variableSite.end(); it++) {
			sm->commit(txn, it->second, it->first);
		}
		cout<<txnId<<" Commited\n";
	} else {
		sm->abort(txn);
		cout<<txnId<<" Aborted\n";
	}
	dm->removeTransaction(txnId);
}

void TransactionManager::checkWaitQueue() {
	for(map<string, list<Command *>>::iterator it = waitQueue.begin(); it != waitQueue.end(); it++) {
		list<Command *>::iterator it1;
		for (it1 = it->second.begin(); it1 != it->second.end(); it1++) {
			Transaction *txn = txnList[(*it1)->txnId];
			if(!txn->isEnded){
				if((*it1)->type == Read){
					string val = sm->read(*it1);
					if(val != ""){
						cout<<(*it1)->var<<": "<<val<<"\n";
						break;
					}
				} else {
					Command *cmd = *it1;
					if(sm->getWriteLock(cmd) == SharedLockAcquired){
						vector<int> writeSite = sm->stage(cmd);
						txnList[cmd->txnId]->addSites(cmd->var, writeSite);
						break;
					}
				}
			}
		}
		if(it1 != it->second.end())
			it->second.erase(it1);
	}
}

void TransactionManager::beforeCommandChecks(){
	detectResolveDeadlock();
	checkWaitQueue();
}

Transaction * TransactionManager::getTxn(string txnId){
	if(txnList.count(txnId))
		return txnList[txnId];
	return NULL;
}
