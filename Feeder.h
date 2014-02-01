#include "WPILib.h"

	const float HOME_FEEDER_ANGLE = 90.0;
	const float MIN_FEEDER_ANGLE = 50.0;
	const float MAX_FEEDER_ANGLE = 120.0;

class Feeder
{
  public:
	Feeder();
<<<<<<< HEAD
	void Initialize();
	void GetInputs();
	void SetOutputs();
	void ExecStep();
=======
	void initialize();
	void getInputs();
	void setOutputs();
	void runStep();
>>>>>>> 8416ec77980e2ba5833fadb6e224b951d56a93b5
	
  private:
	
	enum FEEDER_STATE 
	{
		FEEDER_STATE_HOME = 1,
		FEEDER_STATE_DOWN = 2,
		FEEDER_STATE_HOLD = 3
	};

	
	AnalogChannel feederAnglePotentiometer;
	Joystick stick2;
	Victor feederArm;
	Victor feederWheel;
	float feederAngle;
	FEEDER_STATE feederState;
	float feederAngleMotorSpeed;
	float feederWheelMotorSpeed;
	
	float getAngleFromVoltage(float voltage);
};
