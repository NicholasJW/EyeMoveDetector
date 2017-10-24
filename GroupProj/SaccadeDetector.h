/*
SaccadeDetector.h

Created On: November 8th
Author: Tanner Bina
*/
#ifndef __SaccadeDetector_H__
#define __SaccadeDetector_H__

#include "ScanParser.h"
#include "Saccade.h"

using namespace std;

class SaccadeDetector
{
private:
	vector<Scan> flattenedScans;
	vector<Scan> targetMovements;
	vector<Saccade> rightSaccades;
	vector<Saccade> leftSaccades;

	/*
	The size of segmenets for the moving average.
	 */
	const static int SEGMENTSIZE = 8;
	/*
	Flattens the velocity data in the scans to a vector.
	Uses the moving average for velocity.
	Removes the first scans up to the Segment size.
	 */
	void flattenData(ScanParser parser);
	/*
	Averages the velocity of the scans and creates a scan from the
	scan at the specified basePosition
	 */
	Scan getAverageScan(Scan scans[], int numScans, int basePosition);

	const static int CUTOFFVELOCITY = 5;
	const static int CUTOFFSIZE = 5;
	void findSaccades(Eye eye);
	void determineSaccadeTypes(Eye eye);
	//returns the last target movement before the time.
	Scan getNearestTarget(Time t);
public:
	SaccadeDetector(ScanParser data);
	~SaccadeDetector();

	const vector<Saccade> getRightSaccades(){return rightSaccades;}
	const vector<Saccade> getLeftSaccades(){return leftSaccades;}
};

#endif