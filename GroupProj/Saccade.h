 /*
Saccade.h

Created On: November 8th
Author: Tanner Bina
*/
#ifndef __Saccade_H__
#define __Saccade_H__

#include "ScanParser.h"
#include <vector>

using namespace std;

enum SaccadeType{
	PRIMARY, SECONDARY, OTHER
};

enum Eye{
	RIGHT, LEFT
};

enum Plane{
	X, Y
};

/*
Holds data for saccades identified within the eye data.
Classifies saccades into Type 1, primary, and type 2
secondary saccades. As well as includes timestamps for
each stage of the saccade, amplitude durations, and 
peak velocity.
*/
class Saccade
{
private:
	//data points which make up the saccade.
	vector<Scan> dataPoints;

	//specifies the type of saccade.
	SaccadeType type;

	//the target movement that the saccade corresponds to
	//For type OTHER saccades, empty.
	Scan targetMovement;

	Eye eye;

	//timestamps for all stages
	Time onsetTimestamp;
	Time peakVelocityOnsetTimestamp;
	Time peakVelocityCompletionTimestamp;
	Time completionTimestamp;

	//amplitude based on change in degrees.
	double xAmplitude;
	double yAmplitude;

	//duration of full saccade.
	double duration;

	//peak velocity the saccade reaches
	double peakVelocity;

	//durations of each stage of the saccade.
	double onsetDuration;
	double peakDuration;
	double completionDuration;

	//determines the peak velocity for the saccade.
	void determinePeakVelocity();
	//determine the duration for all stages.
	void determineDurations();
	//determine amplitude of saccade.
	void determineAmplitude();

public:
	//construct a saccade from a vector of scanned data.
	Saccade(vector<Scan> points, Eye eye);
	~Saccade();

	void setType(SaccadeType type){this->type = type;}
	void setTargetMovement(Scan target){targetMovement = target;}

	const Time getOnsetTimestamp(){return onsetTimestamp;}
	const Time getPeakOnsetTimestamp(){return peakVelocityOnsetTimestamp;}
	const Time getPeakCompletionTimestamp(){return peakVelocityCompletionTimestamp;}
	const Time getCompletionTimestamp(){ return completionTimestamp;}

	const double getOnsetDuration(){return onsetDuration;}
	const double getPeakDuration(){return peakDuration;}
	const double getCompletionDuration(){return completionDuration;}
};

#endif