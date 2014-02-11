#include "Catapult.h"

Catapult::Catapult(Controllers* driverInput, int catapaultPWM, int leftLimitSwitch, int rightLimitSwitch) 
{
	this->driverInput = driverInput;
	ChooChooMotor = new Victor(catapaultPWM);
	LeftLimitSwitch = new DigitalIOButton(leftLimitSwitch);
	RightLimitSwitch = new DigitalIOButton(rightLimitSwitch);
	catapultState = CATAPULT_STATE_ARM;
}

void Catapult::SetSafeToFire(bool safeFire){
	SafeToFire = safeFire;
}

void Catapult::GetInputs(){
	CommandToFire = driverInput->IsFireButtonPressed();
	CatapultArmed = (!LeftLimitSwitch->Get() || !RightLimitSwitch->Get() || driverInput->IsDebugArmButtonPressed());
	//CatapultArmed = (false);
}
void Catapult::ExecStep(void){
	//ChooChooMotorSpeed = 0.8;
	switch(catapultState){
		case CATAPULT_STATE_ARM:
			if(CatapultArmed){
				ChooChooMotorSpeed = 0.0;
				catapultState = CATAPULT_STATE_ARMED;
			}
			else{
				ChooChooMotorSpeed = 0.8;
			}
			break;
		case CATAPULT_STATE_ARMED:
			ChooChooMotorSpeed = 0.0;
			if(CommandToFire){
				catapultState = CATAPULT_STATE_FIRE;
			}
			break;
		case CATAPULT_STATE_FIRE:
			if(SafeToFire){
				ChooChooMotorSpeed = 0.8;
				//catapultState = CATAPULT_STATE_FIRE;
				//FireTickCount = GetTickCount();
			}
			if(!CatapultArmed){
				ChooChooMotorSpeed = 0.0;
				catapultState = CATAPULT_STATE_ARM;
			}
			break;
		case CATAPULT_STATE_FIRING:
			//if((GetTickCount() - FireTickCount) >= MIN_FIRING_TIME){
			//	catapultState = CATAPULT_STATE_ARM;
			//}
			ChooChooMotorSpeed = 0.8;
			break;
	}
}
	void Catapult::SetOutputs(){
			ChooChooMotor->Set(ChooChooMotorSpeed);
	}


