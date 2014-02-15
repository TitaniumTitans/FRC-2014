//98	3.55
//40.5 	2.23
//90	3.38

#include "Feeder.h"

Feeder::Feeder(Controllers* driverInput, int feederArmInput, int feederWheelInput, int feederAngleAnalog) 
{
	this->driverInput = driverInput;
	feederAnglePotentiometer = new AnalogChannel(feederAngleAnalog);
	feederArm = new Victor(feederArmInput);
	feederWheel = new Victor(feederWheelInput);
	feederAngle = 0;
	feederAngleMotorSpeed = 0.0;
	feederWheelMotorSpeed = 0.0;
	feederState = FEEDER_STATE_HOME;
	feederAngleMotorSpeed = 0.0;
	feederWheelMotorSpeed = 0.0;
	LeftButtonPressed = false;
	RightButtonPressed = false;
	EjectButtonPressed = false;
	FireButtonPressed = false;
	PrevFeederArmAngle = 0.0;
	CurrFeederArmSpeed = 0.0;
	
	TargetFeederArmSpeed = 0;
	K1 = -2;
	
	//ArmPID = new PIDController(0.1,0.001,0.0,feederAnglePotentiometer, feederArm);
	//ArmPID->Enable();
}

Victor* Feeder::GetWheel(){
	return feederWheel;
	//feederWheel->Set(1);
}

void Feeder::GetInputs()
{
	LeftButtonPressed = driverInput->IsFeederLeftButtonPressed();
	RightButtonPressed = driverInput->IsFeederRightButtonPressed();
	EjectButtonPressed = driverInput->IsEjectButtonPressed();
	FireButtonPressed = driverInput->IsFireButtonPressed();
	feederAngle = this->GetAngleFromVoltage(feederAnglePotentiometer->GetVoltage());
	
	SmartDashboard::PutNumber("Potentiometer Voltage", feederAnglePotentiometer->GetVoltage());
	
}

void Feeder::SetState(FEEDER_STATE state){
	feederState = state;
}

void Feeder::ExecStep()
{
	
	//feederWheelMotorSpeed = 1.0;
	feederAngleMotorSpeed = 0.0;
	
	CurrFeederArmSpeed = (feederAngle-PrevFeederArmAngle)/driverInput->GetPeriod();
	
	switch (this->feederState)
	{
		case FEEDER_STATE_DOWN:
			TargetFeederArmSpeed = 25;
			//feederWheelMotorSpeed = 1.0;
			/*
			if (feederAngle > DOWN_FEEDER_ANGLE+2.5)
			{
				feederAngleMotorSpeed = 0.2;
			}
			else if(feederAngle < DOWN_FEEDER_ANGLE-2.5){
				feederAngleMotorSpeed = -0.4;
			}
			else
			{
				feederAngleMotorSpeed = 0.0;
			}
			*/
			//ArmPID->SetSetpoint(2.3);//GetVoltageFromAngle(DOWN_FEEDER_ANGLE));
			if(feederAngle < DOWN_FEEDER_ANGLE+10){
				float error = CurrFeederArmSpeed-TargetFeederArmSpeed;
				feederAngleMotorSpeed = feederAngleMotorSpeed-(K1*error);
			}
			else if(feederAngle < DOWN_FEEDER_ANGLE+5){
				feederAngleMotorSpeed = 0.2;
			}
			else{
				feederAngleMotorSpeed = 0;
			}
			
			if (LeftButtonPressed || RightButtonPressed)
			{
				feederState = FEEDER_STATE_HOME;
			}			
			break;
				
	case FEEDER_STATE_HOME:
	default:
		TargetFeederArmSpeed = -25;
		/*if (feederAngle >= HOME_FEEDER_ANGLE)
		{
			feederWheelMotorSpeed = 0.0;
			//feederAngleMotorSpeed = 0.2;
		}
		else
		{
			feederWheelMotorSpeed = 1.0;
			//feederAngleMotorSpeed = 0.0;
		}*/
		
		if(feederAngle < HOME_FEEDER_ANGLE-10){
			float error = CurrFeederArmSpeed-TargetFeederArmSpeed;
			feederAngleMotorSpeed = feederAngleMotorSpeed-(K1*error);
		}
		else if(feederAngle < HOME_FEEDER_ANGLE-5){
			feederAngleMotorSpeed = -0.2;
		}
		else{
			feederAngleMotorSpeed = 0;
		}
				
		//ArmPID->SetSetpoint(3.6);//GetVoltageFromAngle(HOME_FEEDER_ANGLE));
		
		if (LeftButtonPressed || RightButtonPressed || FireButtonPressed)
		{
			feederState = FEEDER_STATE_DOWN;
		}
		
		break;
	}
	
	if(feederAngle <= 90){
		feederWheelMotorSpeed = 1;
	}
	else{
		feederWheelMotorSpeed = 0;
	}
	
	if(driverInput->IsEjectButtonPressed()){
		feederWheelMotorSpeed = -1;
	}
	
	PrevFeederArmAngle = feederAngle;

	return;
}

float Feeder::GetAngle()
{
	return feederAngle;
}

void Feeder::SetOutputs()
{
	feederWheel->Set(feederWheelMotorSpeed);
	feederArm->Set(0);//feederAngleMotorSpeed);
	return;
}

float Feeder::GetAngleFromVoltage(float voltage)
{
	//float scale = 5.0/250.0;
	//return voltage/scale;
	//return 46.80187207*voltage-77.5975039;
	return 43.37222833*voltage-56.26320383;
}

float Feeder::GetVoltageFromAngle(float angle)
{
	return (angle+56.26320383)/43.37222833;
}
