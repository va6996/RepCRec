//
// Created by Vinayak Agarwal on 12/4/21.
//

#ifndef REPCREC_VARIABLE_H
#define REPCREC_VARIABLE_H

#include <string>
#include <vector>

using namespace std;

class Variable {
		string var;
		vector<pair<int, string>> value;
		string stagedValue;
		int stagingTime;
		bool isStale;

public:
		Variable(string var, string value);

		string getLatestValue();
		string getLatestValue(int time);
		void stageValue(string newValue);
		void commitStagedValue();

		void markStale();
		bool isDataStale();
};

#endif //REPCREC_VARIABLE_H
