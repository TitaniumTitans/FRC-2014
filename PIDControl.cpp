#include "PIDControl.h"

PIDControl::PIDControl(void) 
{
	Reset();
}

void PIDControl::SetKp(float kp)
{
	Kp = kp;
}

void PIDControl::SetKi(float ki)
{
	Kp = ki;
}

void PIDControl::SetKd(float kd)
{
	Kd = kd;
}

void PIDControl::Reset()
{
	//Kp = 0.0;
	//Ki = 0.0;
	//Kd = 0.0;
	PrevOutput = 0.0;
	PrevTime = 0.0;
	PrevError = 0.0;
	ErrorInt = 0.0;
}

// Calculate our motor output using a PID control loop
// P - Proportional, I - Integral, D - Derivitive
float PIDControl::CalcMotorOutput(float desiredVel, float actualVel, float elapsedTime)
{
	float errorDeriv = 0.0;
	float errorProp = 0.0;
	float motorOutput = 0.0;
	float deltaT = 0.0;
	
	// Calculate the time that has elapsed since the last time through
	//deltaT = elapsedTime - PrevTime;
	deltaT = 0.01;
	// Calculate the error values
	errorProp = actualVel - desiredVel;
	ErrorInt += (errorProp * deltaT);
	if (deltaT > 0)
	{
		errorDeriv = (errorProp - PrevError)/deltaT;
	}
	
	// Calculate our new output using Kp, Ki, Kd, & the corresponding error values;
	motorOutput = PrevOutput - (errorProp * Kp) - (ErrorInt * Ki) - (errorDeriv * Kd);
	SmartDashboard::PutNumber("Motor Output", motorOutput);
	SmartDashboard::PutNumber("Actually Velocity", actualVel);
	SmartDashboard::PutNumber("Error Prop", errorProp);
	SmartDashboard::PutNumber("Kp", Kp);
	// Save the current values for next time as needed
	PrevOutput = motorOutput;
	PrevError = errorProp;
	PrevTime = elapsedTime;

	return motorOutput;
	
}
