//#include "Include.h"
/*
class Catapult
{
  public:
	
  private:
	bool CommandToFire;
	bool SafeToFire;
	int FireTickCount;
	float ChooChooMotorSpeed;
	bool CatapultArmed;
	enum CATAPULT_STATE{
		CATAPULT_STATE_ARM = 0,
		CATAPULT_STATE_FIRE = 1,
		CATAPULT_STATE_ARMED = 2,
		CATAPULT_STATE_FIRING = 3
	};
	CATAPULT_STATE catapultState;
};
/*
void SetFire(bool fireCmd){
	CommandedToFire = fireCmd;
}
void SetSafeToFire(bool safeFire){
	SafeToFire = safeFire;
}
void GetInputs(){
	CatapultArmed = (LimitSwitch1 || LimitSwitch2);
}
void ExecStep(void){
	switch(catapultState){
		case CATAPULT_STATE_ARM:
			if(CatapultArmed){
				ChooChooGearMotorSpeed = 0.0;
				catapultState = CATAPULT_STATE_ARMED;
			}
			else{
				ChooChooMotorSpeed = 1.0;
			}
			break;
		case CATAPULT_STATE_ARMED:
			ChooChooGearMotorSpeed = 0.0;
			if(CommandedToFire){
				catapultState = CATAPULT_STATE_FIRE;
			}
			break;
		case CATAPULT_STATE_FIRE:
			if(SafeToFire){
				ChooChooGearMotorSpeed = 1.0;
				catapultState = CATAPULT_STATE_FIRE;
				FireTickCount = GetTickCount();
			}
			else{
				ChooChooGearMotorSpeed = 0.0;				
			}
			break;
		case CATAPULT_STATE_FIRING:
			if((GetTickCount() - FireTickCount) >= MIN_FIRING_TIME){
				catapultState = CATAPULT_STATE_ARM;
			}
			ChooChooGearMotorSpeed = 1.0;
			break;
	}
	void SetOutputs(){
		ChooChooGearMotor(ChooChooGearMotorSpeed);
	}
}
*/
