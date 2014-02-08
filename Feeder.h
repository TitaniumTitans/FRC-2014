#include "WPILib.h"
#include "Controllers.h"


class Feeder
{
  public:
	enum FEEDER_STATE 
		{
			FEEDER_STATE_HOME = 1,
			FEEDER_STATE_DOWN = 2,
			FEEDER_STATE_HOLD = 3
		};
	Feeder(Controllers* driverInput, int feederArmInput, int feederWheelInput, int feederAngleAnalog);
	void GetInputs();
	void SetOutputs();
	void ExecStep();
	float GetAngle();
	void SetState(FEEDER_STATE state);
	Victor* GetWheel();
	static const float MIN_FEEDER_ANGLE = 32.0;
	static const float MAX_FEEDER_ANGLE = 135.0;
	
	static const float HOME_FEEDER_ANGLE = 90.0;
	static const float DOWN_FEEDER_ANGLE = 45.0;
	static const float HOLD_FEEDER_ANGLE = 120.0;
	
  private:
	
	

	Controllers* driverInput;
	AnalogChannel* feederAnglePotentiometer;
	Victor* feederArm;
	Victor* feederWheel;
	float feederAngle;
	FEEDER_STATE feederState;
	float feederAngleMotorSpeed;
	float feederWheelMotorSpeed;
	
	bool LeftButtonPressed;
	bool RightButtonPressed;
	bool EjectButtonPressed;
	
	
	float GetAngleFromVoltage(float voltage);
};
