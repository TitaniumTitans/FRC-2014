#ifndef _Operater_
#define _Operater_

#include "WPILib.h"

class Operater
{
public:
	Operater(int driverStickNum, int helperStickNum);
	void GetInputs();
	bool GetHighGear();
	float GetLeftDriveInput();
	float GetRightDriveInput();
	bool IsFireButtonPressed();
	bool IsEjectButtonPressed();
	bool IsFeederLeftButtonPressed();
	bool IsFeederRightButtonPressed();
	
	private:
	
	
	float DriveCommandLeft;
	float DriveCommandRight;
	bool FireCatapult;
	bool EjectBall;
	bool FeederLeftPressed;
	bool FeederRightPressed;
	bool HighGearToggle;
	bool PrevHighGearButton;
	
	Joystick* driverStick;
	Joystick* helperStick;
	
	
};

#endif



