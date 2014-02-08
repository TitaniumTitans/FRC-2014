#include "Controllers.h"

Controllers::Controllers(int driverStickNum, int helperStickNum)
{
	driverStick = new Joystick(driverStickNum);
	helperStick = new Joystick(helperStickNum);
	DriveCommandLeft = 0;
	DriveCommandRight = 0;
	FireCatapult = false;
	EjectBall = false;
	FeederLeftPressed = false;
	FeederRightPressed = false;
	HighGearToggle = false;
	PrevHighGearButton = false;
}

void Controllers::GetInputs()
{
	
	DriveCommandLeft = driverStick->GetRawAxis(2);
	DriveCommandRight = driverStick->GetRawAxis(5);
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
	
	
	
}
	
bool Controllers::GetHighGear()
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

