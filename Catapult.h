#ifndef CATAPULT_H
#define CATAPULT_H

#include "WPILib.h"
#include "Controllers.h"

class Catapult
{
  public:
	Catapult(Controllers* driverInput, int catapaultPWM, int limitSwitch);
	enum CATAPULT_STATE{
			CATAPULT_STATE_ARM = 0,
			CATAPULT_STATE_FIRE = 1,
			CATAPULT_STATE_ARMED = 2,
			CATAPULT_STATE_FIRING = 3
		};
	
	void Catapult::SetSafeToFire(bool safeFire);
	void Catapult::GetInputs();
	void Catapult::ExecStep(void);
	void Catapult::SetOutputs();
	void SetState(CATAPULT_STATE state);
	Victor* ChooChooMotor;
	
  private:
	bool CommandToFire;
	bool SafeToFire;
	int FireTickCount;
	float ChooChooMotorSpeed;
	bool CatapultArmed;
	int catapultInput;
	float MaxChooChooMotorSpeed;
	Timer* timer; 
	
	
	
	CATAPULT_STATE catapultState;
	Controllers* driverInput;
	DigitalInput* LimitSwitch;
};

#endif /* CATAPULT_H */
