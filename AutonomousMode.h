#ifndef AUTONOMOUSMODE_H
#define AUTONOMOUSMODE_H

#include "WPILib.h"
#include "Sensors.h"
#include "Catapult.h"

#define LEFT_MOTOR 4
#define RIGHT_MOTOR 5

class AutonomousMode
{
	public:
		AutonomousMode(int mode, RobotDrive* myRobot, Sensors* sensors, Catapult* catapult, int stopDistRange, int stopDistEncod, float stopTime, int lightPort);
		void GetInputs();//ColorImage* cImage);
		void ExecStep();
		void SetOutputs();
	
	private:
		RobotDrive* myRobot;
		Sensors* sensors;
		Catapult* catapult;
		Relay* light;
		Timer* timer;
		float distance;
		float distanceTrav;
		float stopTime;
		int stopDistEncod;
		int stopDistRange;
		bool shoot;
		bool camShoot;
		float motorOut;
		int mode;
		bool firedAlready;
};

#endif /* AUTONOMOUSMODE_H */
