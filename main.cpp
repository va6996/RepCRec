#include <iostream>
#include <fstream>
#include "Driver/Driver.h"

int main(int argc, char **argv) {
	auto *d = new Driver();

	string fileName;
	cout << "Enter the full path for Input File:";
	cin >> fileName;
	ifstream inp(fileName);
	if (inp.is_open()) {
		string line;
		while (getline(inp, line)) {
			d->processLine(line);
		}
	}
	inp.close();
	return 0;
}
