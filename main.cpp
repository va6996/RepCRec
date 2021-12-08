#include <iostream>
#include <fstream>
#include "Driver/Driver.h"

int main(int argc, char** argv) {
	Driver *d = new Driver();
//	if(argc<2)
//		cout<<"FileName Missing\n";

//    ifstream inp(argv[1]);
    string fileName;
    cout<<"Enter Input File Name:";
    cin>>fileName;
    ifstream inp(fileName);
	if(inp.is_open()){
		string line;
		while(getline(inp, line)) {
			d->processLine(line);
		}
	}
	inp.close();
	return 0;
}
