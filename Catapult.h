#ifndef CATAPULT_H
#define CATAPULT_H

#include "WPILib.h"
#include "Controllers.h"
#include "Feeder.h"

class Catapult
{
  public:
	Catapult(Controllers* driverInput, Feeder* feeder, int catapaultPWM, int limitSwitch, int red, int blue);
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
	Feeder* GetFeeder();
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
	
	bool Flashing;
	
	CATAPULT_STATE catapultState;
	Controllers* driverInput;
	DigitalInput* LimitSwitch;
	
	Timer* lighttimer;
	
	Feeder* feeder;
};

#endif /* CATAPULT_H */
