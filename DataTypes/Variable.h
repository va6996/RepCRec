//
// Created by Vinayak Agarwal on 12/4/21.
//

#ifndef REPCREC_VARIABLE_H
#define REPCREC_VARIABLE_H

#include <string>
#include <vector>

using namespace std;

/**
 * Class representing individual variables and their values
 */
class Variable {
		string var;
		vector<pair<int, string>> value;
		string stagedValue;
		int stagingTime;
		bool isStale;

public:
		Variable(string var, string value);

		/**
		 * Return the latest value for the variable
		 * @return the value along with write time
		 */
		pair<int, string> getLatestValue();

		/**
		 * Return the latest value for the variable after before given time
		 * @param time the time before which the value should be fetched
		 * @return the value along with write time
		 */
		pair<int, string> getLatestValue(int time);

		/**
		 * Stage the value to a temporary storage
		 * @param newValue the value
		 */
		void stageValue(string newValue);

		/**
		 * Convert staged value to permanent value
		 */
		void commitStagedValue();

		/**
		 * Mark the variable value as stale, to be not read until written to.
		 */
		void markStale();

		/**
		 * Test whether the variable data is stale
		 * @return result of operation
		 */
		bool isDataStale() const;
};

#endif //REPCREC_VARIABLE_H
