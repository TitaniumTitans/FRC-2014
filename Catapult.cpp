#include "Catapult.h"

const float MIN_FIRING_TIME_IN_SECONDS = 1.0;

Catapult::Catapult(Controllers* driverInput, Feeder* feeder, int catapaultPWM, int limitSwitch, int red, int blue) 
{
	this->driverInput = driverInput;
	ChooChooMotor = new Victor(catapaultPWM);
	LimitSwitch = new DigitalInput(limitSwitch);
	catapultState = CATAPULT_STATE_ARM;
	MaxChooChooMotorSpeed = 0.8;
	timer = new Timer();
	timer->Reset();
	CatapultArmed = false;
	SmartDashboard::PutNumber("Catapaut State Constructor", catapultState);
	//redled = new Relay(red);
	//whiteled = new Relay(blue);
	//lighttimer = new Timer();
	//lighttimer->Start();
	this->feeder = feeder;
}

void Catapult::SetState(CATAPULT_STATE state)
{
	catapultState = state;
}

void Catapult::SetSafeToFire(bool safeFire)
{
	SafeToFire = safeFire;
}

void Catapult::GetInputs()
{
	CommandToFire = driverInput->IsFireButtonPressed();
	SafeCommandToFire = driverInput->IsFireSafetyButtonPressed();
	//CatapultArmed = (!LeftLimitSwitch->Get() || !RightLimitSwitch->Get() || driverInput->IsDebugArmButtonPressed());
	CatapultArmed = (!LimitSwitch->Get());// || driverInput->IsDebugArmButtonPressed());
	SmartDashboard::PutBoolean("Catapult Button", LimitSwitch->Get());
	
}

void Catapult::ExecStep(void)
{
	SafeToFire = feeder->GetAngle()<85;
	//ChooChooMotorSpeed = MaxChooChooMotorSpeed;	
	SmartDashboard::PutBoolean("Catapaut Armed", CatapultArmed);
	SmartDashboard::PutNumber("Catapaut State", catapultState);
	switch (catapultState)
	{
		case CATAPULT_STATE_ARM:
			/*
			if (lighttimer->Get()<0.25) {
				redled->Set(redled->kOn);
				whiteled->Set(whiteled->kOff);
			}
			else if(lighttimer->Get()<0.5){
				whiteled->Set(whiteled->kOn);
				redled->Set(redled->kOff);
			}
			else {
				lighttimer->Reset();
			}
			*/
			SmartDashboard::PutString("Arm State", "Arm");
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
			//redled->Set(redled->kOff);
			//whiteled->Set(whiteled->kOff);
			SmartDashboard::PutString("Arm State", "Armed");
			ChooChooMotorSpeed = 0.0;
			if (CommandToFire && SafeCommandToFire)
			{
				catapultState = CATAPULT_STATE_FIRE;
			}
			break;
			
		case CATAPULT_STATE_FIRE:
			SmartDashboard::PutString("Arm State", "Fire");
			feeder->SetState(feeder->FEEDER_STATE_DOWN);
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
			/*
			if (lighttimer->Get()<0.25) {
				redled->Set(redled->kOn);
				whiteled->Set(whiteled->kOff);
			}
			else if(lighttimer->Get()<0.5){
				whiteled->Set(whiteled->kOn);
				redled->Set(redled->kOff);
			}
			else {
				lighttimer->Reset();
			}
			*/
			SmartDashboard::PutString("Arm State", "Firing");
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


Feeder* Catapult::GetFeeder(){
	return feeder;
}

void Catapult::SetOutputs()
{
	SmartDashboard::PutNumber("choochoomotorspeed2", ChooChooMotorSpeed);
	ChooChooMotor->Set(ChooChooMotorSpeed);
}


