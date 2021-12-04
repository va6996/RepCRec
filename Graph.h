//
// Created by Vinayak Agarwal on 12/4/21.
//
#ifndef REPCREC_GRAPH_H
#define REPCREC_GRAPH_H

#include <string>
#include <vector>

using namespace std;

class Graph {
		string id;
		vector<string> edges;

		void addEdge(string src, string dst);
		void deleteEdge(string src, string dst);
		bool detectCycle();
};

#endif //REPCREC_GRAPH_H
