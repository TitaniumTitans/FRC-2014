#include "Feeder.h"

Feeder::Feeder() :
	feederAnglePotentiometer(2),
	stick2(2), 
	feederArm(6),
	feederWheel(8),
	feederAngle(0),
	feederState(FEEDER_STATE_HOME),
	feederAngleMotorSpeed(0.0),
	feederWheelMotorSpeed(0.0)
{

}

void Feeder::Initialize()
{
	feederState = FEEDER_STATE_HOME;
	feederAngleMotorSpeed = 0.0;
	feederWheelMotorSpeed = 0.0;
	return;
}

void Feeder::GetInputs()
{
	//feederAngle = getAngleFromVoltage(feederAnglePotentiometer.GetAverageVoltage());
	return;
}

void Feeder::ExecStep()
{
	switch (feederState)
	{
	case FEEDER_STATE_DOWN:
		feederWheelMotorSpeed = 1.0;
		if (feederAngle > MIN_FEEDER_ANGLE)
		{
			feederAngleMotorSpeed = -1.0;
		}
		else
		{
			feederAngleMotorSpeed = 0.0;
		}
		break;
		
	case FEEDER_STATE_HOLD:
		break;
		
	case FEEDER_STATE_HOME:
	default:
		if (feederAngle > (HOME_FEEDER_ANGLE + 1.0) )
		{
			feederWheelMotorSpeed = 0.0;
			feederAngleMotorSpeed = -1.0;
		}
		else if (feederAngle < (HOME_FEEDER_ANGLE - 1.0) )
		{
			feederWheelMotorSpeed = 1.0;
			feederAngleMotorSpeed = 1.0;
		}
		else
		{
			feederWheelMotorSpeed = 0.0;
			feederAngleMotorSpeed = 0.0;
		}
		break;
	}
	return;
}

void Feeder::setOutputs()
{
	feederWheel.Set(feederWheelMotorSpeed);
	//feederAngle.Set(feederAngleMotorSpeed);
	return;
}

float Feeder::getAngleFromVoltage(float voltage)
{
	float scale = 5.0/250.0;
	return voltage/scale;
}

