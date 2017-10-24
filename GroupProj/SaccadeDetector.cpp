#include "SaccadeDetector.h"

using namespace std;

SaccadeDetector::SaccadeDetector(ScanParser data)
{
	while(data.hasNextTarget()){
		targetMovements.push_back(data.getNextTarget());
	}
	flattenData(data);
	findSaccades(RIGHT);
	findSaccades(LEFT);
}

void SaccadeDetector::findSaccades(Eye eye){
	bool startSaccade = false;

	vector<Scan> currentSaccade;

	for (int i = 1; i < flattenedScans.size(); i++){
		Velocity current;
		Velocity old;
		double difference;

		switch (eye){
			case RIGHT:
			current = flattenedScans.at(i).getRightVelocity();
			old = flattenedScans.at(i-1).getRightVelocity();
			break;

			case LEFT:
			current = flattenedScans.at(i).getLeftVelocity();
			old = flattenedScans.at(i-1).getLeftVelocity();
			break;
		}

		difference = current.totalComponent -old.totalComponent;

		if (!startSaccade && abs(difference) > CUTOFFVELOCITY){
			startSaccade = true;
		}

		if (startSaccade && abs(difference) < CUTOFFVELOCITY){
			startSaccade = false;
			if (currentSaccade.size() > CUTOFFSIZE){
				Saccade s(currentSaccade, eye);
				switch(eye){
					case (RIGHT):
					rightSaccades.push_back(s);
					break;

					case (LEFT):
					leftSaccades.push_back(s);
					break;
				}
			}
			currentSaccade.clear();
		} 
	}

	determineSaccadeTypes(eye);
}

void SaccadeDetector::determineSaccadeTypes(Eye eye){
	vector<Saccade> saccades;
	switch(eye){
		case RIGHT:
		saccades = rightSaccades;
		break;

		case LEFT:
		saccades = leftSaccades;
		break;
	}

	for (int i = 0; i < saccades.size(); i++){
		if (i == 0){
			if (saccades.at(i).getOnsetTimestamp() < targetMovements.at(0).getTime()){
				saccades.at(i).setType(OTHER);
			} else {
				saccades.at(i).setType(PRIMARY);
				saccades.at(i).setTargetMovement(targetMovements.at(0));
			}
		} else {
			Scan target = getNearestTarget(saccades.at(i).getOnsetTimestamp());
		}
	}
}

Scan SaccadeDetector::getNearestTarget(Time t){
	int index = 0;
	Scan closest = targetMovements.at(index);
	while(targetMovements.at(index).getTime() < t
		&& index < targetMovements.size()){

		closest = targetMovements.at(index);
		index++;
	}

	return closest;
}

void SaccadeDetector::flattenData(ScanParser parser){
	Scan previous [SEGMENTSIZE]; 
	int position = 0;
	for (position; position < SEGMENTSIZE; position++){
		previous[position] = parser.getNextScan();
	}
	flattenedScans.push_back(getAverageScan(previous, SEGMENTSIZE, SEGMENTSIZE-1));

	while(parser.hasNextScan()){
		previous[position % SEGMENTSIZE] = parser.getNextScan();
		flattenedScans.push_back(getAverageScan(previous, SEGMENTSIZE, position%SEGMENTSIZE));
		position++;
	}
}

Scan SaccadeDetector::getAverageScan(Scan scans[], int numScans, int basePosition){
	Scan result(scans[basePosition]);

	double rightXVelSum = 0;
	double leftXVelSum = 0;
	double rightYVelSum = 0;
	double leftYVelSum = 0;

	for (int i = 0; i < numScans; i++){
		rightXVelSum += scans[i].getRightVelocity().xComponent;
		rightYVelSum += scans[i].getRightVelocity().yComponent;
		leftXVelSum += scans[i].getLeftVelocity().xComponent;
		leftYVelSum += scans[i].getLeftVelocity().yComponent;
	}

	Velocity newRight;
	newRight.xComponent = rightXVelSum/(double)numScans;
	newRight.yComponent = rightYVelSum/(double)numScans;
	newRight.totalComponent = sqrt(newRight.xComponent * newRight.xComponent
		+ newRight.yComponent * newRight.yComponent);
	result.setRightVelocity(newRight);

	Velocity newLeft;
	newLeft.xComponent = leftXVelSum/(double)numScans;
	newLeft.yComponent = leftYVelSum/(double)numScans;
	newLeft.totalComponent = sqrt(newLeft.xComponent * newLeft.xComponent
		+ newLeft.yComponent * newLeft.yComponent);
	result.setLeftVelocity(newLeft);

	return result;
}