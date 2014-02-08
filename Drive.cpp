#include "Drive.h"

Drive::Drive(Controllers* driverInput, int leftMotor, int rightMotor)
{
	this->driverInput = driverInput;
	myRobot = new RobotDrive(leftMotor, rightMotor);
	myRobot->SetExpiration(0.1);
	myRobot->SetSafetyEnabled(false);
}

void Drive::SetDriveCommand(float leftDriveCmd, float rightDriveCmd){
	LeftDriveCommand = leftDriveCmd;
	RightDriveCommand = rightDriveCmd;
}

void Drive::GetInputs(){
	HighGear = driverInput->GetHighGear();
	LeftDriveMotorOutput = driverInput->GetLeftDriveInput();
	RightDriveMotorOutput = driverInput->GetRightDriveInput();
}
void Drive::ExecStep()
{
	this->SetHighGear(HighGear);
	this->SetDriveCommand(LeftDriveMotorOutput, RightDriveMotorOutput);
	this->SetOutputs();
}
void Drive::SetOutputs(){
	myRobot->TankDrive(LeftDriveMotorOutput, RightDriveMotorOutput);
	//GearShift.Set(HighGear);
}
