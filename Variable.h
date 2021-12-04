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

public:
		Variable(string var, string value);

		string getLatestValue();
		string getLatestValue(int time);
		void stageValue(string newValue);
		void commitStagedValue();
};

#endif //REPCREC_VARIABLE_H
