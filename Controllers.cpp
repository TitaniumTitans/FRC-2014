#include "Controllers.h"

Controllers::Controllers(float period, int driverStickNum, int helperStickNum)
{
	helperStick = new Joystick(helperStickNum);
	driverStick = new Joystick(driverStickNum);
	DriveCommandLeft = 0;
	DriveCommandRight = 0;
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
	
	//DriveCommandLeft = driverStick->GetRawAxis(2);
	//DriveCommandRight = driverStick->GetRawAxis(5);
	//DriveCommandFwdRev = driverStick->GetRawAxis(5);
	//DriveCommandRightLeft = driverStick->GetRawAxis(4);
	FireCatapult = helperStick->GetRawButton(2);
	EjectBall = helperStick->GetRawButton(3);
	
	bool CurrentHighGearToggleButton = driverStick->GetRawButton(2);
	if (! PrevHighGearButton && CurrentHighGearToggleButton)
	{
		HighGearToggle = !HighGearToggle;
	} 
	PrevHighGearButton=CurrentHighGearToggleButton;
	
	bool CurrentFeederLeftPressed = helperStick->GetRawButton(5);
	if( !PrevFeederLeftPressed && CurrentFeederLeftPressed)
		FeederLeftPressed=true;
	else
		FeederLeftPressed=false;
	PrevFeederLeftPressed = CurrentFeederLeftPressed;
	
	bool CurrentFeederRightPressed = helperStick->GetRawButton(6);
	if( !PrevFeederRightPressed && CurrentFeederRightPressed)
		FeederRightPressed=true;
	else
		FeederRightPressed=false;
	PrevFeederRightPressed = CurrentFeederRightPressed;
	
	DebugArmButton = helperStick->GetRawButton(7);
	
	bool CurrentLightPressed = helperStick->GetRawButton(1);
	if( !PrevLightButtonPressed && CurrentLightPressed)
		LightButtonPressed=true;
	else
		LightButtonPressed=false;
	PrevLightButtonPressed = CurrentLightPressed;
	
}
	
bool Controllers::IsHighGearButtonPressed()
{
	return HighGearToggle;
}
	
float Controllers::GetLeftDriveInput()
{
	return DriveCommandLeft;
}
float Controllers::GetRightDriveInput()
{
	return DriveCommandRight;
}
float Controllers::GetFwdRevDriveInput()
{
	return DriveCommandFwdRev;
}
float Controllers::GetRightLeftDriveInput()
{
	return DriveCommandRightLeft;
}
bool Controllers::IsFireButtonPressed()
{
	return FireCatapult;
}
bool Controllers::IsEjectButtonPressed()
{
	return EjectBall;
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
