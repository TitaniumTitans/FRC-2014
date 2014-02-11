#include "WPILib.h"
#include "Controllers.h"

#define LEFT_MOTOR 4
#define RIGHT_MOTOR 5

class Drive
{
  public:
	Drive(Controllers* driverInput, int leftMotor, int rightMotor, int leftSolenoidNum, int rightSolenoidNum);

	void SetHighGear();
	void SetDriveCommand(float leftDriveCmd);
	void GetInputs();
	void ExecStep();
	void SetOutputs();
	
  private:
	RobotDrive* myRobot;
	float LeftDriveCommand, RightDriveCommand;
	bool HighGear;
	float LeftDriveMotorOutput, RightDriveMotorOutput;
	bool highGear;
	//float leftDriveCmd;
	float rightDriveCmd;
	Controllers* driverInput;
	
	Solenoid *rightSolenoid;
	Solenoid *leftSolenoid;
	
};
