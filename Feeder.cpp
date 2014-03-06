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

Victor* Feeder::GetWheel()
{
	return feederWheel;
}

void Feeder::GetInputs()
{
	LeftButtonPressed = driverInput->IsFeederLeftButtonPressed();
	RightButtonPressed = driverInput->IsFeederRightButtonPressed();
	EjectButtonPressed = driverInput->IsEjectButtonPressed();
	FireButtonPressed = driverInput->IsFireButtonPressed();
	feederAngle = this->GetAngleFromVoltage(feederAnglePotentiometer->GetVoltage());
	angles[arrayIndex] = feederAngle;
	arrayIndex = arrayIndex>=4?0:arrayIndex+1;
	
	SmartDashboard::PutNumber("Potentiometer Voltage", feederAnglePotentiometer->GetVoltage());
	SmartDashboard::PutNumber("Potentiometer Angle", feederAngle);
	
}

void Feeder::SetState(FEEDER_STATE state)
{
	feederState = state;
}

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
				feederWheelMotorSpeed = 1.0;			
			}
			break;
		
		case FEEDER_STATE_DOWN:

			feederWheelMotorSpeed = 1.0;
			
			if (feederAngle > (DOWN_FEEDER_ANGLE + 5.0))
			{
				desiredVel = profile.GetDesiredVel(timer->Get());
				//feederAngleMotorSpeed = pidControl.CalcMotorOutput(desiredVel, CurrFeederArmSpeed, timer->Get());
				feederAngleMotorSpeed = 0.2;
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

		if (feederAngle >= (HOME_FEEDER_ANGLE - 5.0))
		{
			feederWheelMotorSpeed = 0.0;
			feederAngleMotorSpeed = 0.0;
		}
		else if (feederAngle >= (HOME_FEEDER_ANGLE - 10.0))
		{
			feederWheelMotorSpeed = 0.0;
			desiredVel = profile.GetDesiredVel(timer->Get());
			//feederAngleMotorSpeed = pidControl.CalcMotorOutput(desiredVel, CurrFeederArmSpeed, timer->Get());
			feederAngleMotorSpeed = -0.4;
		}
		else
		{
			feederWheelMotorSpeed = 1.0;
			desiredVel = profile.GetDesiredVel(timer->Get());
			//feederAngleMotorSpeed = pidControl.CalcMotorOutput(desiredVel, CurrFeederArmSpeed, timer->Get());
			feederAngleMotorSpeed = -0.4;
		}

		if (EjectButtonPressed)
		{
			feederWheelMotorSpeed = -1.0;	
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

float Feeder::GetAngle()
{
	return feederAngle;
}

void Feeder::SetOutputs()
{
	feederWheel->Set(feederWheelMotorSpeed);//feederWheelMotorSpeed);
	feederArm->Set(feederAngleMotorSpeed);//feederAngleMotorSpeed);
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
