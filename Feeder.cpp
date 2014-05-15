//98	3.55
//40.5 	2.23
//90	3.38

#include "Feeder.h"


//
// Feeder Constructor
//
Feeder::Feeder(Controllers* driverInput, int feederArmInput, int feederWheelInput, int feederAngleAnalog) 
{
	this->driverInput = driverInput;
	feederAnglePotentiometer = new AnalogChannel(feederAngleAnalog);
	feederArm = new Victor(feederArmInput);
	feederWheel = new Victor(feederWheelInput);
	feederAngle = 0;
	feederAngleMotorSpeed = 0.0;
	feederWheelMotorSpeed = 0.0;
	feederState = FEEDER_STATE_INIT;
	feederAngleMotorSpeed = 0.0;
	feederWheelMotorSpeed = 0.0;
	LeftButtonPressed = false;
	RightButtonPressed = false;
	EjectButtonPressed = false;
	FireButtonPressed = false;
	PrevFeederArmAngle = 0.0;
	CurrFeederArmSpeed = 0.0;
	
	//angles = new float[5];
	
	arrayIndex = 0;
	
	TargetFeederArmSpeed = 0;
	K1 = -2;
	
	timer = new Timer();
	profile.SetAccel(90.0);
	profile.SetMaxVelocity(45.0);
	
	pidControl.SetKp(0.02);
	pidControl.SetKi(0.0);
	pidControl.SetKd(0.0);
}

//
//  Return the feeder wheel object
//
Victor* Feeder::GetWheel()
{
	return feederWheel;
}

//
//  Get Inputs
//
void Feeder::GetInputs()
{
	LeftButtonPressed = driverInput->IsFeederLeftButtonPressed();
	RightButtonPressed = driverInput->IsFeederRightButtonPressed();
	EjectButtonPressed = driverInput->IsEjectButtonPressed();
	EjectButtonFront = driverInput->IsEjectButtonFront();
	FireButtonPressed = driverInput->IsFireButtonPressed();
	feederAngle = this->GetAngleFromVoltage(feederAnglePotentiometer->GetVoltage());
	angles[arrayIndex] = feederAngle;
	arrayIndex = arrayIndex>=4?0:arrayIndex+1;
	
	SmartDashboard::PutNumber("Potentiometer Voltage", feederAnglePotentiometer->GetVoltage());
	SmartDashboard::PutNumber("Potentiometer Angle", feederAngle);
	
}

//
// Execute a step
//
void Feeder::ExecStep()
{
	float desiredVel = 0.0;
	feederWheelMotorSpeed = 0.0;
	feederAngleMotorSpeed = 0.0;
	
	float aveFeederAngle = 0;
	for(int i =0; i<5; i++)
	{
		aveFeederAngle+=angles[i];
	}
	aveFeederAngle/=5;
	
	CurrFeederArmSpeed = (aveFeederAngle - PrevFeederArmAngle) / driverInput->GetPeriod();
	
	
	switch (this->feederState)
	{
	    default:
		case FEEDER_STATE_INIT:
			if (LeftButtonPressed)
			{
				feederState = FEEDER_STATE_HOME;
				profile.SetDist(HOME_FEEDER_ANGLE - feederAngle);
				profile.CalcProfile();
				pidControl.Reset();
				timer->Reset();
				timer->Start();
			}			
			else if (RightButtonPressed)
			{
				feederState = FEEDER_STATE_DOWN;
				profile.SetDist(DOWN_FEEDER_ANGLE - feederAngle);
				profile.CalcProfile();
				pidControl.Reset();
				timer->Reset();
				timer->Start();			
				feederWheelMotorSpeed = 0.65;			
			}
			break;
		
		case FEEDER_STATE_DOWN:

			feederWheelMotorSpeed = 0.65;
			
			if (feederAngle > (DOWN_FEEDER_ANGLE + 5.0))
			{
				desiredVel = profile.GetDesiredVel(timer->Get());
				//feederAngleMotorSpeed = pidControl.CalcMotorOutput(desiredVel, CurrFeederArmSpeed, timer->Get());
				feederAngleMotorSpeed = 0.4;
			}
			else
			{
				feederAngleMotorSpeed = 0.0;
			}
						
			if (LeftButtonPressed || RightButtonPressed)
			{
				feederState = FEEDER_STATE_HOME;
				profile.SetDist(HOME_FEEDER_ANGLE - feederAngle);
				profile.CalcProfile();
				pidControl.Reset();
				timer->Reset();
				timer->Start();
			}			
			break;
				
	case FEEDER_STATE_HOME:

		if (feederAngle >= (HOME_FEEDER_ANGLE + 5))
		{
			feederWheelMotorSpeed = 0.0;
			feederAngleMotorSpeed = 0.0;
		}
		else if (feederAngle >= (HOME_FEEDER_ANGLE - 10.0))
		{
			feederWheelMotorSpeed = 0.0;
			desiredVel = profile.GetDesiredVel(timer->Get());
			//feederAngleMotorSpeed = pidControl.CalcMotorOutput(desiredVel, CurrFeederArmSpeed, timer->Get());
			feederAngleMotorSpeed = -0.3;
		}
		else
		{
			//feederWheelMotorSpeed = 0.55;
			desiredVel = profile.GetDesiredVel(timer->Get());
			//feederAngleMotorSpeed = pidControl.CalcMotorOutput(desiredVel, CurrFeederArmSpeed, timer->Get());
			feederAngleMotorSpeed = -0.5;
		}

		if (feederAngle < 70){
			feederWheelMotorSpeed = 0.65;
		}
		
		if (EjectButtonPressed)
		{
			feederWheelMotorSpeed = -0.55;	
			if (feederAngle <= (HOME_FEEDER_ANGLE))
			{
				feederAngleMotorSpeed = -0.3;
			}
		}
		
		if (EjectButtonFront)
		{
			feederWheelMotorSpeed=0.0;
			//feederWheelMotorSpeed = 0.55;
			if (feederAngle <= (HOME_FEEDER_ANGLE))
			{
				feederAngleMotorSpeed = -0.3;
			}
		}
		
		if (LeftButtonPressed || RightButtonPressed || FireButtonPressed)
		{
			feederState = FEEDER_STATE_DOWN;
			profile.SetDist(DOWN_FEEDER_ANGLE - feederAngle);
			profile.CalcProfile();
			pidControl.Reset();
			timer->Reset();
			timer->Start();			
			feederWheelMotorSpeed = -1.0;	
		}
		
		break;
	}
	
	PrevFeederArmAngle = aveFeederAngle;
	
	SmartDashboard::PutNumber("feeder state", feederState);
	SmartDashboard::PutNumber("Feeder Timer", timer->Get());
	SmartDashboard::PutNumber("Feeder Motor Speed", feederAngleMotorSpeed);
	SmartDashboard::PutNumber("Feeder Current Arm Speed", CurrFeederArmSpeed);
	SmartDashboard::PutNumber("Feeder Desired Velocity", desiredVel);
	//return;
}

//
// Set Outputs
//
void Feeder::SetOutputs()
{
	feederWheel->Set(feederWheelMotorSpeed);//feederWheelMotorSpeed);
	//feederWheel->Set(0.55);
	feederArm->Set(feederAngleMotorSpeed);//feederAngleMotorSpeed);
	return;
}

//
// Return the feeder angle
//
float Feeder::GetAngle()
{
	return feederAngle;
}

//
// Set the feeder state
//
void Feeder::SetState(FEEDER_STATE state)
{
	feederState = state;
}

//
// Calculate the feeder angle from a given potentiometer voltage
//
float Feeder::GetAngleFromVoltage(float voltage)
{
	//float scale = 5.0/250.0;
	//return voltage/scale;
	//return 46.80187207*voltage-77.5975039;
	//return 45.22590787*voltage+7.543095126;
	return 1176.280248*voltage-112.4281092;
	//return 1176.280248*voltage-85.4281092;
}

//
// Calculate the feeder potentiometer voltage from a given angle
//
float Feeder::GetVoltageFromAngle(float angle)
{
	return (angle+56.26320383)/43.37222833;
}
