#include "Catapult.h"

const float MIN_FIRING_TIME_IN_SECONDS = 1.0;

Catapult::Catapult(Controllers* driverInput, int catapaultPWM, int limitSwitch) 
{
	this->driverInput = driverInput;
	ChooChooMotor = new Victor(catapaultPWM);
	LimitSwitch = new DigitalInput(limitSwitch);
	catapultState = CATAPULT_STATE_ARM;
	MaxChooChooMotorSpeed = 0.8;
	timer = new Timer();
	timer->Reset();
}

void Catapult::SetSafeToFire(bool safeFire)
{
	SafeToFire = safeFire;
}

void Catapult::GetInputs()
{
	CommandToFire = driverInput->IsFireButtonPressed();
	//CatapultArmed = (!LeftLimitSwitch->Get() || !RightLimitSwitch->Get() || driverInput->IsDebugArmButtonPressed());
	CatapultArmed = (!LimitSwitch->Get() || driverInput->IsDebugArmButtonPressed());
	//SmartDashboard::PutBoolean("rightbutton", LimitSwitch->Get());
	//CatapultArmed = (false);
}
void Catapult::ExecStep(void)
{
	//ChooChooMotorSpeed = MaxChooChooMotorSpeed;
	switch (catapultState)
	{
		case CATAPULT_STATE_ARM:
			if (CatapultArmed)
			{
				ChooChooMotorSpeed = 0.0;
				catapultState = CATAPULT_STATE_ARMED;
			}
			else
			{
				ChooChooMotorSpeed = MaxChooChooMotorSpeed;
			}
			break;
			
		case CATAPULT_STATE_ARMED:
			ChooChooMotorSpeed = 0.0;
			if (CommandToFire)
			{
				catapultState = CATAPULT_STATE_FIRE;
			}
			break;
			
		case CATAPULT_STATE_FIRE:
			if (SafeToFire)
			{
				ChooChooMotorSpeed = MaxChooChooMotorSpeed;
				catapultState = CATAPULT_STATE_FIRING;
				timer->Reset();
				timer->Start();
			}
			/*if (!CatapultArmed)
			{
				ChooChooMotorSpeed = 0.0;
				catapultState = CATAPULT_STATE_ARM;
			}*/
			break;
		case CATAPULT_STATE_FIRING:
			if (timer->Get() >= MIN_FIRING_TIME_IN_SECONDS)
			{
				catapultState = CATAPULT_STATE_ARM;
			}
			ChooChooMotorSpeed = MaxChooChooMotorSpeed;
			break;
	}
	SmartDashboard::PutNumber("choochoomotorspeed", ChooChooMotorSpeed);
	SmartDashboard::PutNumber("state", catapultState);
}

void Catapult::SetOutputs()
{
	SmartDashboard::PutNumber("choochoomotorspeed2", ChooChooMotorSpeed);
		ChooChooMotor->Set(ChooChooMotorSpeed);
		//ChooChooMotor->Set(1.0);
		//ChooChooMotor->Set(0.8);
}


