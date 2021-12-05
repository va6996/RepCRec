//
// Created by Vinayak Agarwal on 12/4/21.
//

#include "Variable.h"

#include <utility>
#include "GlobalClock.h"

string Variable::getLatestValue() {
	if (value.empty()) return {};
	return value.back().second;
}

string Variable::getLatestValue(int time) {
	for (auto it=value.rbegin(); it!=value.rend();it++) {
		if (it->first <= time) return it->second;
	}
	return {};
}

void Variable::stageValue(string newValue) {
	stagedValue = std::move(newValue);
	stagingTime = GlobalClock::getTime();
}

void Variable::commitStagedValue() {
	value.emplace_back(stagingTime, stagedValue);
	isStale = false;
}

Variable::Variable(string var, string data) : var(std::move(var)) {
	value.emplace_back(0, std::move(data));
	isStale = false;
}

void Variable::markStale() {
	isStale = true;
}

bool Variable::isDataStale() {
	return isStale;
}


