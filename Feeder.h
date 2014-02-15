#include "WPILib.h"
#include "Controllers.h"

class Feeder
{
  public:
	enum FEEDER_STATE 
		{
			FEEDER_STATE_HOME = 1,
			FEEDER_STATE_DOWN = 2
		};
	Feeder(Controllers* driverInput, int feederArmInput, int feederWheelInput, int feederAngleAnalog);
	void GetInputs();
	void SetOutputs();
	void ExecStep();
	float GetAngle();
	void SetState(FEEDER_STATE state);
	Victor* GetWheel();
	//static const float MIN_FEEDER_ANGLE = 32.0;
	//static const float MAX_FEEDER_ANGLE = 135.0;
	
	static const float HOME_FEEDER_ANGLE = 97.0;
	//static const float FEEDER_STOP_OUT_ANGLE = 50.0;
	//static const float FEEDER_STOP_IN_ANGLE = 95.0;
	static const float DOWN_FEEDER_ANGLE = 42.0;
	static const float HOLD_FEEDER_ANGLE = 130.0;
	
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
	
	float PrevFeederArmAngle;
	float CurrFeederArmSpeed;
	float TargetFeederArmSpeed;
	
	float K1;
	
	bool LeftButtonPressed;
	bool RightButtonPressed;
	bool EjectButtonPressed;
	bool FireButtonPressed;
	
	
	float GetAngleFromVoltage(float voltage);
};
