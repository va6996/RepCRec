//
// Created by Anurag Gupta on 12/4/21.
//

#ifndef REPCREC_DEADLOCKMANAGER_H
#define REPCREC_DEADLOCKMANAGER_H


#include <map>
#include <set>
#include "../Transactions/Transaction.h"
#include "iostream"

using namespace std;

/**
 * Class responsible for creating wait-for graph
 * and detecting if there is a cycle present in the graph
 * If a cycle is detected, return the youngest TXN.
 */
class DeadlockManager {
    map<string, set<string>> adjacencyList;
    set<string> nodeList;

    /**
     * Detects is a cycle is present in the graph
     * @param txn current node to be checked
     * @param visited map of nodes visited for cycle check
     * @param recStack current path for cycle check function call
     * @return true if a cycle is present, otherwise it returns false
     */
    bool isCycleRec(const string& txn, map<string, bool> &visited, map<string, bool> &recStack);

    /**
     * Function to detect and get the set of txns
     * in a cycle. The function is called when
     * a deadlock is present.
     * @param txn cureent node to be checked
     * @param visited map of nodes visited for cycle check
     * @param recStack current path for cycle check
     * @param txnDetails details of all txns
     * @param currP current set of txns in the path to curr node
     * @return array of txns in a cycle
     */
    vector<string> minTransRec(const string& txn, map<string, bool> &visited, map<string, bool> &recStack,
                               map<string, Transaction *> &txnDetails, vector<string> currP);
public:
    /**
     * Adds a edge between node t1 and t2
     * @param t1 source node
     * @param t2 destination node
     */
    void addEdge(const string& t1, const string& t2);

    /**
     * When a txn ends, this func removes all
     * the edges from and to the node txn from the graph
     * @param txn node to be removed
     */
    void removeTransaction(const string& txn);

    /**
     * Checks if deadlock is present in the
     * graph by checking if cycle is present in the graph
     * @return true if deadlock is present, otherwise returns false
     */
    bool detectDeadlock();

    /**
     * If a deadlock is present, then the function
     * returns the youngest txn from the set of txns causing deadlock
     * @param txn contains information about all the txns
     * @return name of the youngest txn causing deadlock
     */
    string resolveDeadlock(map<string, Transaction *> &txn);
};

#endif //REPCREC_DEADLOCKMANAGER_H
