#include "WPILib.h"

class Controller
{
public:
	Controller();
	
	float GetLeftJoystick();
	float GetRightJoystick();
	
	bool GetEjectButton();
	bool GetFeederDownButton();
	bool GetFeederUpButton();
	
};
