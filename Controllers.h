#ifndef _Controllers_
#define _Controllers_

#include "WPILib.h"

class Controllers
{
public:
	Controllers(float period, int driverStickNum, int helperStickNum);
	void GetInputs();
	bool IsHighGearButtonPressed();
	float GetLeftDriveInput();
	float GetRightDriveInput();
	float GetFwdRevDriveInput();
	float GetRightLeftDriveInput();
	bool IsFireButtonPressed();
	bool IsEjectButtonPressed();
	bool IsFeederLeftButtonPressed();
	bool IsFeederRightButtonPressed();
	bool IsDebugArmButtonPressed();
	bool IsLightButtonPressed();
	Joystick* GetDriverJoystick();
	float GetPeriod();
	
	
private:	
	float DriveCommandLeft;
	float DriveCommandRight;
	float DriveCommandFwdRev;
	float DriveCommandRightLeft;
	bool FireCatapult;
	bool EjectBall;
	bool FeederLeftPressed;
	bool PrevFeederLeftPressed;
	bool FeederRightPressed;
	bool PrevFeederRightPressed;
	bool HighGearToggle;
	bool PrevHighGearButton;
	bool DebugArmButton;
	bool LightButtonPressed;
	bool PrevLightButtonPressed;
	float period;
	
	Joystick* driverStick;
	Joystick* helperStick;
	
};

#endif



