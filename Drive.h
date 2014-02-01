#include "WPILib.h"
#include "Operater.h"

#define LEFT_MOTOR 1
#define RIGHT_MOTOR 2

class Drive
{
  public:
	Drive(Operater* driverInput);

	void SetHighGear(bool highGear);
	void SetDriveCommand(float leftDriveCmd, float rightDriveCmd);
	void GetInputs();
	void ExecStep();
	void SetOutputs();
	
  private:
	RobotDrive* myRobot;
	float LeftDriveCommand, RightDriveCommand;
	bool HighGear;
	float LeftDriveMotorOutput, RightDriveMotorOutput;
	bool highGear;
	float leftDriveCmd;
	float rightDriveCmd;
	Operater* driverInput;
	
};
