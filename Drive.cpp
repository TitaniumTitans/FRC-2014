#include "Drive.h"

Drive::Drive(Controllers* driverInput, int leftMotor, int rightMotor)
{
	this->driverInput = driverInput;
	myRobot = new RobotDrive(leftMotor, rightMotor);
	myRobot->SetExpiration(0.1);
	myRobot->SetSafetyEnabled(false);
	this->leftSolenoid = new Solenoid(1);	
	this->rightSolenoid = new Solenoid(2);
}

void Drive::SetDriveCommand(float leftDriveCmd, float rightDriveCmd){
	LeftDriveCommand = leftDriveCmd;
	RightDriveCommand = rightDriveCmd;
}

void Drive::SetHighGear(){
	SmartDashboard::init();
	if (HighGear == true) {
		leftSolenoid->Set(false);
		rightSolenoid->Set(true);
		SmartDashboard::PutString("Gear", "High Gear");
	}
	if (HighGear == false) {
		leftSolenoid->Set(true);
		rightSolenoid->Set(false);
		SmartDashboard::PutString("Gear", "Low Gear");
	}
}

void Drive::GetInputs(){
	HighGear = driverInput->GetHighGear();
	LeftDriveMotorOutput = driverInput->GetLeftDriveInput();
	RightDriveMotorOutput = driverInput->GetRightDriveInput();
}
void Drive::ExecStep()
{
	this->SetHighGear();
	this->SetDriveCommand(LeftDriveMotorOutput, RightDriveMotorOutput);
	this->SetOutputs();
}
void Drive::SetOutputs(){
	myRobot->TankDrive(LeftDriveMotorOutput, RightDriveMotorOutput);
	Drive::SetHighGear();
}
