/*
 * ScanParser_test.cpp
 *
 *  Created on: Nov 8, 2016
 *      Author: KWChen
 */

#include "ScanParser.h"
#include <iostream>
//#include <stdlib.h>

using namespace std;

int main (int argc, char * argv[]) {
	ScanParser *parser;

	if (argc != 2) {
		cerr<<"Need to enter input file name" << endl;
		exit(1);
	}

	parser = new ScanParser(argv[1]);

	cout << parser->myScans.size() << endl;
	cout << parser->myTargets.size() << endl;

	while (parser->hasNextTarget()) {
//		cout << (parser->getNextTarget()) << endl; //TODO: write toString
	}
}

