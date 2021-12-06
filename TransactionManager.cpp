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
    bool canRead = true;
    if(waitQueue.count(cmd->var)) {
        for (list<Command *>::iterator it = waitQueue[cmd->var]->begin(); it != waitQueue[cmd->var]->end(); it++) {
            if(!(*it)->txn->isEnded && (*it)->type==Write){
                canRead = false;
                break;
            }
        }
    }
    if(canRead) {
        string val = sm->read(cmd);
        cout << cmd->txnId << (cmd->txn->getTxnType() == RO ? " ReadOnly Txn," : " ReadWrite Txn,") << " Reading "
             << cmd->var << "\n";
        if (val != "")
            cout << cmd->txnId << " Reading " << cmd->var << ": " << val << "\n";
        else {
            cout << cmd->txnId << " Reading " << cmd->var << " Failed\n";
            set<string> conflictingTxn = sm->getConflictingLocks(cmd);
            for (set<string>::iterator it = conflictingTxn.begin(); it != conflictingTxn.end(); it++) {
                dm->addEdge(cmd->txnId, *it);
            }

            if (waitQueue.count(cmd->var)) {
                for (list<Command *>::iterator it = waitQueue[cmd->var]->begin(); it != waitQueue[cmd->var]->end(); it++) {
                    if (!cmd->txn->isEnded)
                        dm->addEdge(cmd->txnId, (*it)->txnId);
                }
                waitQueue[cmd->var]->push_back(cmd);
            } else {
                list<Command *> *newW = new list<Command *>();
                newW->push_back(cmd);
                waitQueue.insert(make_pair(cmd->var, newW));
            }
        }
    } else {
        for (list<Command *>::iterator it = waitQueue[cmd->var]->begin(); it != waitQueue[cmd->var]->end(); it++) {
            if(!(*it)->txn->isEnded){
                dm->addEdge(cmd->txnId, (*it)->txnId);
            }
        }
        waitQueue[cmd->var]->push_back(cmd);
    }
}

void TransactionManager::executeWrite(Command *cmd){
    cout<<cmd->txnId<<" Writing "<<cmd->var<<"\n";
	if(sm->getWriteLock(cmd) == ExclusiveLockAcquired){
        cout<<cmd->txnId<<" "<<cmd->var<<" Written, Value:"<<cmd->value<<"\n";
        vector<int> writeSite = sm->stage(cmd);
		txnList[cmd->txnId]->addSites(cmd->var, writeSite);
        txnList[cmd->txnId]->addWriteTimes(cmd->var, cmd->startTime);
	} else {
        cout<<cmd->txnId<<" Writing "<<cmd->var<<" Failed\n";
		set<string> conflictingTxn = sm->getConflictingLocks(cmd);

		for(set<string>::iterator it = conflictingTxn.begin(); it != conflictingTxn.end(); it++) {
			dm->addEdge(cmd->txnId, *it);
		}

		if(waitQueue.count(cmd->var)){
			for(list<Command *>::iterator it = waitQueue[cmd->var]->begin(); it != waitQueue[cmd->var]->end(); it++){
				dm->addEdge(cmd->txnId, (*it)->txnId);
			}
			waitQueue[cmd->var]->push_back(cmd);
		} else{
			list<Command *> *newW = new list<Command *>();
			newW->push_back(cmd);
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
		cout<<txn<<" Aborted due to deadlock\n";
	}
}

void TransactionManager::endTxn(string txnId) {
    Transaction *txn = txnList[txnId];
	txn->isEnded = true;

	bool canWriteAll = true;
	for(map<string, set<int>>::iterator it = txn->variableSite.begin(); it != txn->variableSite.end(); it++){
		if(sm->wasSiteDownAfter(it->second, txn->variableWriteTime[it->first] )){
			canWriteAll = false;
			break;
		}
	}
	if(canWriteAll) {
		for (map<string, set<int>>::iterator it = txn->variableSite.begin(); it != txn->variableSite.end(); it++) {
			sm->commit(txn, it->second, it->first);
		}
        sm->abort(txn);
		cout<<txnId<<" Commited\n";
	} else {
		sm->abort(txn);
		cout<<txnId<<" Aborted as a site failed\n";
	}
	dm->removeTransaction(txnId);
}

void TransactionManager::checkWaitQueue() {
	for(map<string, list<Command *> *>::iterator it = waitQueue.begin(); it != waitQueue.end(); it++) {
		list<Command *>::iterator it1;
        bool canDelete = false;
		for (it1 = it->second->begin(); it1 != it->second->end(); it1++) {
			Transaction *txn = txnList[(*it1)->txnId];
			if(!txn->isEnded){
                (*it1)->startTime = GlobalClock::getTime();
                if((*it1)->type == Read){
					string val = sm->read(*it1);
					if(val != ""){
                        Command *cmd = *it1;
                        cout<<cmd->txnId<<" Reading "<<cmd->var<<": "<<val<<"\n";
                        canDelete = true;
						break;
					}
				} else {
					Command *cmd = *it1;
                    LockCodes lockType = sm->getWriteLock(cmd);
					if(lockType == ExclusiveLockAcquired){
                        cout<<cmd->txnId<<" "<<cmd->var<<" Written, Value:"<<cmd->value<<"\n";
                        vector<int> writeSite = sm->stage(cmd);
                        txnList[cmd->txnId]->addSites(cmd->var, writeSite);
                        txnList[cmd->txnId]->addWriteTimes(cmd->var, cmd->startTime);
                        canDelete = true;
                    }
                    break;
				}
			}
		}
		if(canDelete)
			it->second->erase(it1);
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
