#include "Saccade.h"

using namespace std;

Saccade::Saccade(vector<Scan> points, Eye eye){
	dataPoints = points;
	this->eye = eye;
	onsetTimestamp = dataPoints.at(0).getTime();
	completionTimestamp = dataPoints.at(dataPoints.size()).getTime();

	determinePeakVelocity();
	determineDurations();
	determineAmplitude();
}

void Saccade::determinePeakVelocity(){
	peakVelocity = 0;
	for (int i = 0; i < dataPoints.size(); i++){
		Velocity current;
		switch(eye){
			case RIGHT:
			current = dataPoints.at(i).getRightVelocity();
			break;

			case LEFT:
			current = dataPoints.at(i).getLeftVelocity();
			break;
		}

		double velocity = current.totalComponent;

		if (velocity > peakVelocity){
			peakVelocity = velocity;
			peakVelocityOnsetTimestamp = dataPoints.at(i).getTime();
			peakVelocityCompletionTimestamp = dataPoints.at(i).getTime();
		} else if (velocity == peakVelocity){
			peakVelocityCompletionTimestamp = dataPoints.at(i).getTime();
		}
	}
}

void Saccade::determineDurations(){
	onsetDuration = peakVelocityOnsetTimestamp - onsetTimestamp;
	peakDuration = peakVelocityCompletionTimestamp - peakVelocityOnsetTimestamp;
	completionDuration = completionTimestamp - peakVelocityCompletionTimestamp;
	duration = onsetTimestamp - completionTimestamp;
}

void Saccade::determineAmplitude(){
	GazePos initGaze;
	GazePos finalGaze;

	switch(eye){
		case RIGHT:
		initGaze = dataPoints.at(0).getRightGazePos();
		finalGaze = dataPoints.at(dataPoints.size()).getRightGazePos();
		break;

		case LEFT:
		initGaze = dataPoints.at(0).getLeftGazePos();
		finalGaze = dataPoints.at(dataPoints.size()).getLeftGazePos();
		break;
	}

	xAmplitude = initGaze.xPos - finalGaze.xPos;

	yAmplitude = initGaze.yPos - finalGaze.yPos;
}