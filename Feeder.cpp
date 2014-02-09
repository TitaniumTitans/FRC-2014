#include "Feeder.h"

Feeder::Feeder(Controllers* driverInput, int feederArmInput, int feederWheelInput, int feederAngleAnalog) {
	this->driverInput = driverInput;
	feederAnglePotentiometer = new AnalogChannel(feederAngleAnalog);
	feederArm = new Victor(feederArmInput);
	feederWheel = new Victor(feederWheelInput);
	feederAngle = 0;
	feederState = (FEEDER_STATE_HOME);
	feederAngleMotorSpeed = 0.0;
	feederWheelMotorSpeed = 0.0;
	feederState = FEEDER_STATE_HOME;
	feederAngleMotorSpeed = 0.0;
	feederWheelMotorSpeed = 0.0;
	LeftButtonPressed = false;
	RightButtonPressed = false;
	EjectButtonPressed = false;
	ArmPID = new PIDController(0.1,0.001,0.0,feederAnglePotentiometer, feederArm);
	ArmPID->Enable();
}

Victor* Feeder::GetWheel(){
	return feederWheel;
	//feederWheel->Set(1);
}

void Feeder::GetInputs()
{
	LeftButtonPressed = driverInput->IsFeederLeftButtonPressed();
	RightButtonPressed= driverInput->IsFeederRightButtonPressed();
	EjectButtonPressed= driverInput->IsEjectButtonPressed();
	feederAngle = this->GetAngleFromVoltage(feederAnglePotentiometer->GetVoltage());
}

void Feeder::SetState(FEEDER_STATE state){
	feederState = state;
}

void Feeder::ExecStep()
{
	switch (feederState)
	{
	case FEEDER_STATE_DOWN:
		feederWheelMotorSpeed = 0.5;
		/*if (feederAngle > DOWN_FEEDER_ANGLE+2.5)
		{
			feederAngleMotorSpeed = 0.2;
		}
		else if(feederAngle < DOWN_FEEDER_ANGLE-2.5){
			feederAngleMotorSpeed = -0.4;
		}
		else
		{
			feederAngleMotorSpeed = 0.0;
		}*/
		
		ArmPID->SetSetpoint(2.3);//GetVoltageFromAngle(DOWN_FEEDER_ANGLE));
		
		if(LeftButtonPressed){
			feederState = FEEDER_STATE_HOME;
		}
		else if(RightButtonPressed){
			feederState = FEEDER_STATE_HOLD;
		}
		
		break;
		
	case FEEDER_STATE_HOLD:
		feederWheelMotorSpeed = 0.0;
		/*if (feederAngle > HOLD_FEEDER_ANGLE+2.5)
		{
			feederAngleMotorSpeed = 0.4;
		}
		else if(feederAngle < HOLD_FEEDER_ANGLE-2.5){
			if(feederAngle < HOME_FEEDER_ANGLE){
				feederAngleMotorSpeed = -0.4;
				feederWheelMotorSpeed = 1.0;
			}
			else
				feederAngleMotorSpeed = -0.2;
		}
		else
		{
			feederAngleMotorSpeed = 0.0;
		}*/
		
		ArmPID->SetSetpoint(3.6);//GetVoltageFromAngle(HOLD_FEEDER_ANGLE));
		
		if(feederAngle < HOME_FEEDER_ANGLE){
			feederWheelMotorSpeed = 0.5;
		}
		
		if(LeftButtonPressed || driverInput->IsFireButtonPressed()){
			feederState = FEEDER_STATE_HOME;
		}
		
		/*if(EjectButtonPressed){
			feederWheelMotorSpeed = -1;	
		}*/
		
		break;
		
	case FEEDER_STATE_HOME:
	default:
		/*if (feederAngle > (HOME_FEEDER_ANGLE + 1.0) )
		{
			feederWheelMotorSpeed = 0.0;
			feederAngleMotorSpeed = 0.2;
		}
		else if (feederAngle < (HOME_FEEDER_ANGLE - 1.0) )
		{
			feederWheelMotorSpeed = -0.2;
			feederAngleMotorSpeed = -0.2;
		}
		else
		{
			feederWheelMotorSpeed = 0.0;
			feederAngleMotorSpeed = 0.0;
		}*/
		
		ArmPID->SetSetpoint(3.6);//GetVoltageFromAngle(HOME_FEEDER_ANGLE));
		
		if(LeftButtonPressed){
			feederState = FEEDER_STATE_DOWN;
		}
		else if(RightButtonPressed){
			feederState = FEEDER_STATE_HOLD;
		}
		
		break;
	}
	
	if(EjectButtonPressed){
		feederWheelMotorSpeed = -1;	
	}
	
	return;
}

float Feeder::GetAngle(){
	return feederAngle;
}

void Feeder::SetOutputs()
{
	feederWheel->Set(feederWheelMotorSpeed);
	//feederArm->Set(feederAngleMotorSpeed);
	return;
}

float Feeder::GetAngleFromVoltage(float voltage)
{
	//float scale = 5.0/250.0;
	//return voltage/scale;
	return 46.80187207*voltage-77.5975039;
}

float Feeder::GetVoltageFromAngle(float angle)
{
	return (angle+77.5975039)/46.80187207;
}
