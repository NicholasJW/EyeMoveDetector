/*
 * ScanParser.h
 *
 * The ScanParser parses an input data file, continuously verifies if input is
 * syntactically correct, and creates a collection of data entries that
 * are ready for future processing.
 *
 *  Created on: Nov 8, 2016
 *      Author: KWChen
 *
 */

#ifndef SCANPARSER_H_
#define SCANPARSER_H_

using namespace std;

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <cmath>
#include <stdlib.h>
#include <vector>
#include "Scan.h"
#include <stdexcept>

enum Location{
	TIME,
	L_EYE_X,
	L_EYE_Y,
	L_PUPIL,
	R_EYE_X,
	R_EYE_Y,
	R_PUPIL,
	L_EYE_XVEL,
	L_EYE_YVEL,
	R_EYE_XVEL,
	R_EYE_YVEL,
	X_RES,
	Y_RES,
	TERMINATOR,
	NUMFIELDS,
};

enum TargetLocation{
	//MSG	2958082.0 -16  !V TARGET_POS TARG1 (960, 600) 1 0
	TGT_TIME,
	SKIP, //-16
	SKIP1, //!V
	SKIP2, //TGT_POS
	SKIP3, //TARG1
	XPOS,
	YPOS,
	SKIP4, //1
	SKIP5, //0

};


class ScanParser {

public:
	/* Specify a text file containing scan data. Function
	 * checks syntactic correctness of file and creates a list of Scans.
	 */
	ScanParser(string filename);

	~ScanParser();

	/*
	 * Returns true if the file specified was syntactically correct.  Otherwise,
	 * returns false.
	 */
	bool isFormatCorrect() {return myFormatCorrect; };

	/*	   Iterator that returns the next Scan in the list of Scans.*/
	Scan getNextScan();

	//Returns true if scan itr not at the end
	bool hasNextScan() {return myScanIndex < myScans.size(); };

	/*	   Iterator that returns the next Target Scan in the list of Scans.*/
	Scan getNextTarget();

	//Returns true if target itr not at the end
	bool hasNextTarget() {return myTargetIndex < myTargets.size(); };


//private:
	vector<Scan> myScans;//list of scans
	vector<Scan> myTargets; //list of targets
	int myScanIndex; //Scans iterator index
	int myTargetIndex; //Targets iterator index
	bool myFormatCorrect;
	TargetPos myPreviousTargetPos;

	void getTokens (string line, string* cell, int& numCells, bool isTarget); //gets tokens from line of data and sets values
	bool setValues (Scan& s, string* cell, int cell_count, bool isTarget);
	//	void getData (Scan& s);

	bool isScan(string s);

	// Returns true if character is white space
	bool isWhitespace(char c)    { return (c == ' '|| c == '\t'); };

	// Returns true if character is a digit
	bool isDigit(char c)         { return (c >= '0' && c <= '9'); };

	// Returns true if character is an uppercase letter
	bool isAlphaUpper(char c)    { return (c >= 'A' && c <= 'Z'); };

	// Returns true if character is a lowercase letter
	bool isAlphaLower(char c)    { return (c >= 'a' && c <= 'z'); };

	// Returns true if character is a plus or minus
	bool isSign(char c)          { return (c == '-' || c == '+'); };

	bool isSymbol (char c) 		{ return (c == '!' || c == '(' || c == ')'); };

	// Returns true if character is an alphabetic character
	bool isAlpha(char c)         {return (isAlphaUpper(c) || isAlphaLower(c)); };

	// Returns true if character is a decimal point
	bool isDecPoint (char c) 	{return (c == '.'); };

	// Returns true if string starts with an asterisk (*)
	bool isComment (string s ) { return (s.at(0) == '*'); } ;

	// Returns true if string starts with an alphabet -- presumed to be text
	bool isText (string s) { return (isAlpha(s.at(0))) ; };

	bool isBlank (string s) {return (s.at(0) == '\n'); };
	// Returns true if s represents a valid decimal integer
	bool isNumberString(string s);

	bool isTargetMsg (string s) ;

	// Converts a string to an integer.  Assumes s is something like "-231" and produces -231
	double  cvtNumString2Number(string s);

	int cvtNumString2Int(string s);


	void parseTarget(string line);
};


#endif /* SCANPARSER_H_ */
