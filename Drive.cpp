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

void Drive::SetHighGear(){
	SmartDashboard::init();
	SmartDashboard::PutString("sethighgear", "called");
	Solenoid *leftSolenoid;
	leftSolenoid = new Solenoid(1);
	Solenoid *rightSolenoid;
	rightSolenoid = new Solenoid(2);
	if (HighGear == true) {
		SmartDashboard::PutString("true", "true");
		leftSolenoid->Set(true);
		rightSolenoid->Set(false);
		//HighGear = false;
	}
	if (HighGear == false) {
		SmartDashboard::PutString("false", "false");
		leftSolenoid->Set(true);
		rightSolenoid->Set(false);
		//HighGear = true;
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
