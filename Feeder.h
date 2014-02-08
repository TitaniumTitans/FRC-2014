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
	
	static const float HOME_FEEDER_ANGLE = 80.0;
	static const float DOWN_FEEDER_ANGLE = 35.0;
	static const float HOLD_FEEDER_ANGLE = 95.0;
	
  private:
	
	
	PIDController* ArmPID;
	Controllers* driverInput;
	AnalogChannel* feederAnglePotentiometer;
	Victor* feederArm;
	Victor* feederWheel;
	float feederAngle;
	FEEDER_STATE feederState;
	float feederAngleMotorSpeed;
	float feederWheelMotorSpeed;
	float GetVoltageFromAngle(float angle);
	
	bool LeftButtonPressed;
	bool RightButtonPressed;
	bool EjectButtonPressed;
	
	
	float GetAngleFromVoltage(float voltage);
};
