#include "Controllers.h"

#define FIRE_CATAPULT_BUTTON	1
#define SAFE_CATAPULT_BUTTON	9
#define EJECT_BALL_BUTTON		6
#define EJECT_BALL_FRONT		7
#define FEEDER_TOGGLE_BUTTON	3
#define GEAR_SHIFT_DOWN_BUTTON	4
#define GEAR_SHIFT_UP_BUTTON	5
#define CAMERA_LIGHT_BUTTON		11
#define DEBUG_ARM_BUTTON		15
#define SWITCH_DIRECTION_BUTTON 8


Controllers::Controllers(float period, int driverStickNum, int helperStickNum)
{
	//helperStick = new Joystick(helperStickNum);
	driverStick = new Joystick(driverStickNum);
	//DriveCommandLeft = 0;
	//DriveCommandRight = 0;
	FireCatapult = false;
	EjectBall = false;
	FeederLeftPressed = false;
	FeederRightPressed = false;
	HighGearToggle = false;
	PrevHighGearButton = false;
	LightButtonPressed = false;
	PrevLightButtonPressed = false;
	this->period = period;
	
}    

void Controllers::GetInputs()
{

	
	FireCatapult = driverStick->GetRawButton(FIRE_CATAPULT_BUTTON);
	SafetyFireCatapult = driverStick->GetRawButton(SAFE_CATAPULT_BUTTON);
	EjectBall = driverStick->GetRawButton(EJECT_BALL_BUTTON);
	EjectBallFront = driverStick->GetRawButton(EJECT_BALL_FRONT);
	
	bool CurrentHighGearToggleButton = driverStick->GetRawButton(GEAR_SHIFT_DOWN_BUTTON) || driverStick->GetRawButton(GEAR_SHIFT_UP_BUTTON);
	if (! PrevHighGearButton && CurrentHighGearToggleButton)
	{
		HighGearToggle = !HighGearToggle;
	} 
	PrevHighGearButton=CurrentHighGearToggleButton;
	 
	bool CurrentFeederLeftPressed = driverStick->GetRawButton(FEEDER_TOGGLE_BUTTON);
	if( !PrevFeederLeftPressed && CurrentFeederLeftPressed)
		FeederLeftPressed=true;
	else
		FeederLeftPressed=false;
	PrevFeederLeftPressed = CurrentFeederLeftPressed;
	
	bool CurrentFeederRightPressed = driverStick->GetRawButton(FEEDER_TOGGLE_BUTTON);
	if( !PrevFeederRightPressed && CurrentFeederRightPressed)
		FeederRightPressed=true;
	else
		FeederRightPressed=false;
	PrevFeederRightPressed = CurrentFeederRightPressed;
	
	DebugArmButton = driverStick->GetRawButton(DEBUG_ARM_BUTTON);
	
	bool CurrentLightPressed = driverStick->GetRawButton(CAMERA_LIGHT_BUTTON);
	if( !PrevLightButtonPressed && CurrentLightPressed)
		LightButtonPressed=true;
	else
		LightButtonPressed=false;
	PrevLightButtonPressed = CurrentLightPressed;
	
	bool BackwardDirection = driverStick->GetRawButton(SWITCH_DIRECTION_BUTTON);
	if (!ForwardDirection && BackwardDirection){
		BackwardButton = true;
	}
	else {
		BackwardButton = false;
	}
	ForwardDirection = BackwardDirection;
}
	
bool Controllers::IsHighGearButtonPressed()
{
	return HighGearToggle;
}

bool Controllers::IsFireButtonPressed()
{
	return FireCatapult;
}

bool Controllers::IsFireSafetyButtonPressed()
{
	return SafetyFireCatapult;
}

bool Controllers::IsEjectButtonPressed()
{
	return EjectBall;
}
bool Controllers::IsEjectButtonFront()
{
	return EjectBallFront;
}
bool Controllers::IsFeederLeftButtonPressed()
{
	return FeederLeftPressed;
}

bool Controllers::IsFeederRightButtonPressed()
{
	return FeederRightPressed;
}

Joystick* Controllers::GetDriverJoystick()
{
	return driverStick;
}

bool Controllers::IsDebugArmButtonPressed()
{
	return DebugArmButton;
}

bool Controllers::IsLightButtonPressed()
{
	return LightButtonPressed;
}

float Controllers::GetPeriod()
{
	return period;
}

bool Controllers::IsBackwardDirectionPressed()
{
	return BackwardButton;
}
