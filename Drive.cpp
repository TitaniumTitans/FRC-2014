#include "Drive.h"

Drive::Drive(Operater* driverInput)
{
	myRobot = new RobotDrive(1, 2);
	myRobot->SetExpiration(0.1);
	this->driverInput = driverInput;
}

void Drive::SetHighGear(bool highGear){
	HighGear = highGear;
}

void Drive::SetDriveCommand(float leftDriveCmd, float rightDriveCmd){
	LeftDriveCommand = leftDriveCmd;
	RightDriveCommand = rightDriveCmd;
}

void Drive::GetInputs(){
	return;
}
void Drive::ExecStep(){
	LeftDriveMotorOutput = driverInput->GetLeftDriveInput();
	RightDriveMotorOutput = driverInput->GetRightDriveInput();
	this->SetHighGear(HighGear);
	this->SetDriveCommand(LeftDriveMotorOutput, RightDriveMotorOutput);
	this->SetOutputs();
}
void Drive::SetOutputs(){
	myRobot->TankDrive(LeftDriveMotorOutput, RightDriveMotorOutput);
	//GearShift.Set(HighGear);
}
