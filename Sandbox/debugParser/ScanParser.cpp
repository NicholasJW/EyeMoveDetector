/*
 * ScanParser.cpp
 *
 *  Created on: Nov 8, 2016
 *      Author: KWChen
 */

#include "ScanParser.h"



ScanParser::ScanParser(string filename) {
	// TODO Auto-generated constructor stub
	Scan s;


	myFormatCorrect = true;

	ifstream in;
	in.open(filename.c_str());

	if (in.bad()) {
		myFormatCorrect = false;

	}
	else {
		string line;
		while (getline(in, line)) {
			cout << line << endl;

			try {
				if (isComment(line) || isText(line) || isBlank(line) ) {continue;}

				if (!(isComment(line) || isText(line) || isBlank(line) ) ){break;}
			}
			catch (out_of_range) {
				break;
			}

		}
		while (getline(in, line)) {
			bool inData = false;
			bool lineIsTarget = false;

//			cout << line << endl;

			if (isTargetMsg(line)){
				parseTarget(line);
				continue;
			}

			if (!isTargetMsg(line)) {
				if (isComment(line) || isText(line) || isBlank(line) ) {continue;}
//				lineIsTarget = true;
			}


			string dataEntry[80];
			int cell_count = 0;


			if (line.length() ==0) {
				continue;
			}


			getTokens(line, dataEntry, cell_count, lineIsTarget);

			bool success = setValues(s, dataEntry, cell_count, lineIsTarget); //TODO: continue

			if (!success) {
				//invalid number of cells read
				myFormatCorrect = false;
				break;
			}
			myScans.push_back(s);
		}
	}

	myScanIndex = 0;

}

ScanParser::~ScanParser() {
	// TODO Auto-generated destructor stub

}


Scan ScanParser::getNextScan() {
	if (myScanIndex < (int) (myScans.size())) {
		myScanIndex++;
		return myScans[myScanIndex - 1];
	}
	Scan s;
	return s;
}

Scan ScanParser::getNextTarget() {
	if (myTargetIndex < (int) (myTargets.size())) {
		myTargetIndex++;
		return myTargets[myTargetIndex - 1];
	}
	Scan t;
	return t;
}

bool ScanParser::setValues(Scan& s, string* entry, int cell_count, bool isTarget) {

	if (isTarget) {
		return true;
	}
	else if (cell_count != NUMFIELDS) {
		//		cout << "fail" << cell_count << endl;
		return false;
	}


	/*	• timestamp is the time in milliseconds since the monitoring computer was started.
	• leye x is the x coordinate of the left eye gaze position in pixels.
	• leye y is the y coordinate of the left eye gaze position in pixels.
	• l pupil is the diameter of the left pupil in millimeters.
	• reye x is the x coordinate of the right eye gaze position in pixels.
	• reye y is the y coordinate of the right eye gaze position in pixels.
	• r pupil is the diameter of the right pupil in millimeters.
	3
	• leye xvel is the x component of the left eye’s velocity in degrees per second.
	• leye yvel is the y component of the left eye’s velocity in degrees per second.
	• reye xvel is the x component of the right eye’s velocity in degrees per second.
	• reye yvel is the y component of the right eye’s velocity in degrees per second.
	• xres is the resolution for the x dimension in pixels per degree.
	• yres is the resolution for the y dimension in pixels per degree*/

	s.setTime(cvtNumString2Number(entry[TIME]));

	s.setLeftGazePos(GazePos (cvtNumString2Number(entry[L_EYE_X]),cvtNumString2Number(entry[L_EYE_Y])) );

	s.setRightGazePos(GazePos (cvtNumString2Number(entry[R_EYE_X]), cvtNumString2Number(entry[R_EYE_Y])) );

	s.setLeftPupil(Pupil (cvtNumString2Number( entry[L_PUPIL])));

	s.setRightPupil(Pupil (cvtNumString2Number( entry[R_PUPIL])));

	s.setResolution(Resolution (cvtNumString2Number( entry[X_RES]), cvtNumString2Number( entry[Y_RES])) );

	s.setLeftVelocity(Velocity( cvtNumString2Number( entry[L_EYE_XVEL] ), cvtNumString2Number( entry[L_EYE_YVEL])) );

	s.setRightVelocity(Velocity( cvtNumString2Number( entry[R_EYE_XVEL] ), cvtNumString2Number( entry[R_EYE_YVEL])) );

	s.setTargetPos(myPreviousTargetPos);

	//	cout << "good" << endl;


	return true;
}

void ScanParser::getTokens(string line, string* cell, int& numCells, bool isTarget) {

	string dataLabel = line.substr(0, 3);



	while (isAlpha(line[0]) ) {//skip the preamble
		numCells = 0;
		return;
	}

	if (dataLabel.compare("MSG") == 0) {
		parseTarget(line);
		isTarget = true;
		return;
	}

	/*if (dataLabel.compare("MSG") == 0) {//line is a target pos
		parseTarget(line);
		isTarget = true;//tells parser that this scan is a target

		int len = line.length();
		int p = 0; //position in line

		int i = 0;

		while (p < len) {
			//target entry looks like this
			//MSG	2958082.0 -16  !V TARGET_POS TARG1 (960, 600) 1 0

			while (p < len && isWhitespace(line.at(p)))
				p++;

			if (line.at(p) == '(' || line.at(p) == ')')
				p++;
			//data entry starts

			bool flag = false;

			while (p < len && !isWhitespace(line.at(p)) && !isSymbol(line.at(p))){
				cell[i] = cell[i] + line.at(p);
				flag = true;
				p++;
			}

			if (flag == true){
				numCells ++;
			}
			i++;
		}



		return;
	}*/



	if (!isAlpha(line[0])){//scan line start
		isTarget = false;

		int len = line.length();

		if (len == 0) return;
		int p = 0; // position in line


		int i = 0;
		while (p < len) {

			while (p < len && isWhitespace(line.at(p)))
				p++;
			//data entry may start

			bool flag = false;

			while (p < len && !isWhitespace(line.at(p))){
				cell[i] = cell[i] + line.at(p);
				flag = true;
				p++;
			}

			if (flag == true){
				numCells ++;
			}
			i++;
		}
	}
}

void ScanParser::parseTarget(string line) {
	TargetPos t;

	int len = line.length();

	if (len == 0) return;

	int p = 0;//position in line

	// line.at(p) is whitespace or p >= len
	while (p < len && ( isWhitespace(line.at(p)) || isAlpha(line.at(p)) ) )
		p++;

	//time starts
	string timeStr = "";
	while (p < len && !isWhitespace(line.at(p))){
		timeStr += line.at(p);
		p++;
	}
	t.recentTargetTime = cvtNumString2Number(timeStr);

	//time ends

	//look for coordinate
	while (p < len && (line.at(p) != '(' ) ) {
		p++;
	}

	//coordinate starts
	string coordinateX = "";
	while (p < len && line.at(p) != ','){
		coordinateX += line.at(p);
		p++;
	}
	t.targetGazePos.xPos = cvtNumString2Number(coordinateX);

	while (p < len && ( isAlpha(line.at(p)) || isWhitespace(line.at(p))) ) {
		p++;
	}

	string coordinateY = "";
	while (p < len && !isAlpha(line.at(p))){
		coordinateY += line.at(p);
		p++;
	}
	t.targetGazePos.yPos = cvtNumString2Number(coordinateY);

	myPreviousTargetPos = t;

	Scan target;
	target.setTargetPos(t);
	target.toggleIsTarget();
	myTargets.push_back(target);

}


bool ScanParser::isScan(string s) {
	return false;
}

bool ScanParser::isNumberString(string s)
// Returns true if s represents a valid decimal integer
{
	int len = s.length();
	if (len == 0) return false;
	if ((isSign(s.at(0)) && len > 1) || isDigit(s.at(0)) || isDecPoint (s.at(0)))
	{
		// check remaining characters
		for (int i=1; i < len; i++)
		{
			if (!isdigit(s.at(i))) return false;
		}
		return true;
	}
	return false;
}


double ScanParser::cvtNumString2Number(string s) {
	//	stringstream ss = new stringstream();

	//	ss << "d";

	int k = 1;
	int val = 0;

	int decimal = 0;
	int decK = 0.1;

	int decPt = 0;

	for ( ; decPt < s.length() - 1; decPt ++) {//find decimal point index
		char c = s.at(decPt);

		if (c == '.') {break;}
	}


	for (int i = decPt + 1; i < s.length() - 1; i++) {//
		char c = s.at(i);

		decimal += k*((int)(c - '0'));
		decK /= 10;
	}

	for (int i = decPt - 1; i > 0; i--) {
		char c = s.at(i);
		val = val + k*((int) (c - '0'));
		k *= 10;
	}

	if (isSign(s.at(0))) {
		if (s.at(0) == '-') val *= -1;
	}
	else {
		val += k*((int)(s.at(0) - '0'));
	}

	return val + decimal;

}

int ScanParser::cvtNumString2Int(string s)
// Converts a string to an integer.  Assumes s is something like "-231" and produces -231
{
	if (!isNumberString(s))
	{
		cerr << "Non-numberic string passed to cvtNumString2Number"
				<< endl;
		return 0;
	}
	int k = 1;
	int val = 0;
	for (int i = s.length()-1; i>0; i--)
	{
		char c = s.at(i);
		val = val + k*((int)(c - '0'));
		k = k*10;
	}
	if (isSign(s.at(0)))
	{
		if (s.at(0) == '-') val = -1*val;
	}
	else
	{
		val = val + k*((int)(s.at(0) - '0'));
	}
	return val;
}



bool ScanParser::isTargetMsg(string s) {
	//MSG	2958082.0 -16  !V TARGET_POS TARG1 (960, 600) 1 0
	if (s.find("TARGET_POS") != s.npos) {
//	if (s.at(0) == 'M'){
		return true;
	}
	return false;
}





