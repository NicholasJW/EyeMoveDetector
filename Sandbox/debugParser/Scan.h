/*
 * EyeData.h
 *
 *  Created on: Nov 8, 2016
 *      Author: KWChen
 */
//TODO: incorporate target position to Scan and SParser
#ifndef SCAN_H_
#define SCAN_H_

using namespace std;

typedef double Time;

/*enum Location{
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
	END,
};*/

/*enum DataFormat{
	TIME,
	LEYE_X,
	LEYE_Y,
	L_PUPIL,
	REYE_X,
	REYE_Y,
	R_PUPIL,
	LEYE_XVEL,
	LEYE_YVEL,
	REYE_XVEL,
	REYE_YVEL,
	XRES,
	YRES,
	NUMFIELDS
};*/


struct GazePos{//has left or right
	double xPos;
	double yPos;
	GazePos() {
		xPos = 0;
		yPos = 0;
	}
	GazePos(int x, int y) {
		xPos = x;
		yPos = y;
	}
};

struct TargetPos{
	Time recentTargetTime;
	GazePos targetGazePos;
	TargetPos () {
		recentTargetTime = 0;
		GazePos targetGazePos;
	}
	TargetPos (Time t, GazePos g) {recentTargetTime = t; targetGazePos = g;}
};

struct Pupil{//has left or right
	double Diameter;
	Pupil(){
		Diameter = 0;
	}
	Pupil (double d) { Diameter = d; }
};

struct Velocity{//has left or right
	double xComponent;
	double yComponent;
	Velocity() {
		xComponent = 0;
		yComponent = 0;
	}
	Velocity(int x, int y) {
		xComponent = x;
		yComponent = y;
	}
};


struct Resolution{
	double xResolution;
	double yResolution;
	Resolution() {
		xResolution = 0;
		yResolution = 0;
	}
	Resolution (double x, double y) {
		xResolution = x;
		yResolution = y;
	}
};

/*
 * This class stores information of a pair of left/right Eyes.
 * It stores data of gaze, pupil, velocity, and resolution.
 */
class Scan {

private:
	bool myIsTarget; //true if the Scan instance is a target position and not an actual scan.
	Time myTime; //The time stamp of the event
	GazePos myLeftGazePos; //The GazePos of left eye. Has info about x and y positions
	GazePos myRightGazePos;//The GazePos of right eye. Has info about x and y positions
	Pupil myLeftPupil; //The Pupil of left eye. Has info about diameter
	Pupil myRightPupil;//The Pupil of right eye. Has info about diameter
	Velocity myLeftVelocity; //The Velocity of left eye. Has info about x and y components
	Velocity myRightVelocity;//The Velocity of right eye. Has info about x and y positions
	Resolution myResolution; //The Resolution of the scan. Has info about x and y resolution
	TargetPos myTargetPos;

public:
	Scan();
	~Scan();

	bool isTarget() {return myIsTarget; }
	void toggleIsTarget() {myIsTarget = true;}

	Time getTime() const {
		return myTime;
	}

	void setTime(Time time) {
		this->myTime = time;
	}

	const GazePos& getLeftGazePos() const {
		return myLeftGazePos;
	}

	void setLeftGazePos(const GazePos& leftGazePos) {
		this->myLeftGazePos = leftGazePos;
	}

	const Pupil& getLeftPupil() const {
		return myLeftPupil;
	}

	void setLeftPupil(const Pupil& leftPupil) {
		this->myLeftPupil = leftPupil;
	}

	const Velocity& getLeftVelocity() const {
		return myLeftVelocity;
	}

	void setLeftVelocity(const Velocity& leftVelocity) {
		this->myLeftVelocity = leftVelocity;
	}

	const Resolution& getResolution() const {
		return myResolution;
	}

	void setResolution(const Resolution& resolution) {
		this->myResolution = resolution;
	}

	const GazePos& getRightGazePos() const {
		return myRightGazePos;
	}

	void setRightGazePos(const GazePos& rightGazePos) {
		this->myRightGazePos = rightGazePos;
	}

	const Pupil& getRightPupil() const {
		return myRightPupil;
	}

	void setRightPupil(const Pupil& rightPupil) {
		this->myRightPupil = rightPupil;
	}

	const Velocity& getRightVelocity() const {
		return myRightVelocity;
	}

	void setRightVelocity(const Velocity& rightVelocity) {
		this->myRightVelocity = rightVelocity;
	}

	const TargetPos& getTarget() const {
		return myTargetPos;
	}
	void setTargetPos(const TargetPos& target) {
		myTargetPos = target;
	}

};

#endif /* SCAN_H_ */
