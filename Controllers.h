#ifndef _Controllers_
#define _Controllers_

#include "WPILib.h"

class Controllers
{
public:
	Controllers(int driverStickNum, int helperStickNum);
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
	bool PrevFeederLeftPressed;
	bool FeederRightPressed;
	bool PrevFeederRightPressed;
	bool HighGearToggle;
	bool PrevHighGearButton;
	
	Joystick* driverStick;
	Joystick* helperStick;
	
	
};

#endif



