//
// Created by Anurag Gupta on 12/4/21.
//

#include "Driver.h"

Driver::Driver() {
	map<int, set<string>> cfg;

	for (int i = 0; i < 10; i++) {
		cfg[i] = {};
	}

	for (int i = 1; i <= 20; i++) {
		if (i & 1) {
			cfg[(i % 10) + 1].insert('x' + to_string(i));
		} else {
			for (int j = 1; j <= 10; j++) {
				cfg[j].insert('x' + to_string(i));
			}
		}
	}
	sm = new SiteManager(cfg);
	tm = new TransactionManager(sm);
//	gc = new GlobalClock();
}

void Driver::processLine(const string &line) {
	tm->beforeCommandChecks();

	vector<string> tokens = getArgs(line);
	if (!tokens.empty()) {
		if (tokens[0] == "beginRO") {
			tm->beingTxn(tokens[1], RO, GlobalClock::getTime());
		} else if (tokens[0] == "begin") {
			tm->beingTxn(tokens[1], RW, GlobalClock::getTime());
		} else if (tokens[0] == "end") {
			tm->endTxn(tokens[1]);
		} else if (tokens[0] == "W") {
			auto *cmd = new Command();
			cmd->txnId = tokens[1];
			cmd->startTime = GlobalClock::getTime();
			cmd->txn = tm->getTxn(cmd->txnId);
			cmd->type = Write;
			cmd->var = tokens[2];
			cmd->value = tokens[3];

			tm->executeCmd(cmd);
		} else if (tokens[0] == "R") {
			auto *cmd = new Command();
			cmd->txnId = tokens[1];
			cmd->startTime = GlobalClock::getTime();
			cmd->txn = tm->getTxn(cmd->txnId);
			cmd->type = Read;
			cmd->var = tokens[2];

			tm->executeCmd(cmd);
		} else if (tokens[0] == "fail") {
			sm->fail(atoi(&tokens[1][0]));
			tm->checkTxnForSiteFail(atoi(&tokens[1][0]));
		} else if (tokens[0] == "recover") {
			sm->recover(atoi(&tokens[1][0]));
		} else if (tokens[0] == "dump") {
			sm->dump();
		}
	}

	GlobalClock::tick();
}

vector<string> Driver::getArgs(string str) {
	char *tokens = strtok(&str[0], " (,)\n");
	vector<string> args;
	while (tokens != nullptr) {
		args.emplace_back(tokens);
		tokens = strtok(nullptr, " (,)\n");
	}
	return args;
}

