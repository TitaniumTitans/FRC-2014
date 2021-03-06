#include "Drive.h"

Drive::Drive(Controllers* driverInput, int leftMotor, int rightMotor, int leftSolenoidNum, int rightSolenoidNum)
{
	this->driverInput = driverInput;
	leftDrive = new Victor(leftMotor);
	rightDrive = new Victor(rightMotor);
	myRobot = new RobotDrive(leftDrive, rightDrive);
	myRobot->SetExpiration(0.1);
	myRobot->SetSafetyEnabled(false);
	this->leftSolenoid = new Solenoid(2);//leftSolenoidNum);	
	this->rightSolenoid = new Solenoid(4);//rightSolenoidNum);
}

void Drive::SetDriveCommand(float leftDriveCmd){
	LeftDriveCommand = leftDriveCmd;
	RightDriveCommand = rightDriveCmd;
}

void Drive::SetHighGear(){
	SmartDashboard::init();
	if (HighGear) {
		leftSolenoid->Set(false);
		rightSolenoid->Set(true);
		SmartDashboard::PutString("Gear", "High Gear");
	}
	else {
		leftSolenoid->Set(true);
		rightSolenoid->Set(false);
		SmartDashboard::PutString("Gear", "Low Gear");
	}
}

void Drive::SetHighGear(bool high){
	SmartDashboard::init();
	if (high) {
		leftSolenoid->Set(false);
		rightSolenoid->Set(true);
		SmartDashboard::PutString("Gear", "High Gear");
	}
	else {
		leftSolenoid->Set(true);
		rightSolenoid->Set(false);
		SmartDashboard::PutString("Gear", "Low Gear");
	}
}


void Drive::GetInputs(){
	HighGear = driverInput->IsHighGearButtonPressed();
	BackwardButton = driverInput ->IsBackwardDirectionPressed();
	//LeftDriveMotorOutput = driverInput->GetLeftDriveInput();
	//RightDriveMotorOutput = driverInput->GetRightDriveInput();
}
void Drive::ExecStep()
{
	this->SetHighGear();
	this->SetDriveCommand(LeftDriveMotorOutput);
	this->SetOutputs();
}
void Drive::SetOutputs(){
	myRobot->ArcadeDrive(driverInput->GetDriverJoystick());
	//myRobot->ArcadeDrive(LeftDriveMotorOutput, RightDriveMotorOutput);
	Drive::SetHighGear();
}
