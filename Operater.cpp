#include "Operater.h"

Operater::Operater(int driverStickNum, int helperStickNum)
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

void Operater::GetInputs()
{
	
	DriveCommandLeft = driverStick->GetRawAxis(5);
	DriveCommandRight = driverStick->GetRawAxis(2);
	FireCatapult = helperStick->GetRawButton(2);
	EjectBall = helperStick->GetRawButton(3);
	FeederLeftPressed=helperStick->GetRawButton(5);
	FeederRightPressed=helperStick->GetRawButton(5);
	bool CurrentHighGearToggleButton = driverStick->GetRawButton(2);
	if (! PrevHighGearButton && CurrentHighGearToggleButton)
	{
		HighGearToggle = !HighGearToggle;
	} 
	
	PrevHighGearButton=CurrentHighGearToggleButton;
				
}
	
bool Operater::GetHighGear()
{
	return HighGearToggle;
}
	
float Operater::GetLeftDriveInput()
{
	return DriveCommandLeft;
}
float Operater::GetRightDriveInput()
{
	return DriveCommandRight;
}
bool Operater::IsFireButtonPressed()
{
	return FireCatapult;
}
bool Operater::IsEjectButtonPressed()
{
	return EjectBall;
}
bool Operater::IsFeederLeftButtonPressed()

{
	return FeederLeftPressed;
}

bool Operater::IsFeederRightButtonPressed()

{
	return FeederRightPressed;
}

