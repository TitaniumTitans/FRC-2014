#include "Profile.h"

Profile::Profile(void) 
{
	SetAccel(0.1);
	SetMaxVelocity(0.1);
	SetDist(0.0);
	TConstVel = 0.0;
	TDecel = 0.0;
	TMax = 0.0;
	DirForward = true;
}

void Profile::SetAccel(float accel)
{
	Accel = accel;
}

void Profile::SetMaxVelocity(float maxVel)
{
	MaxVelocity = maxVel;
}

void Profile::SetDist(float dist)
{
	if (dist >= 0)
	{
		Dist = dist;
		DirForward = true;
	}
	else
	{
		Dist = -dist;
		DirForward = false;
	}

}

void Profile::CalcProfile(float accel, float maxVel, float dist)
{
	SetAccel(accel);
	SetMaxVelocity(maxVel);
	SetDist(dist);
}

// Calculate the profile shape -- essentially we just need to calculate the duration of the
// acceleration, deceleration, and constant velocity phases
void Profile::CalcProfile()
{
	// acceleration period ends when we reach our max velocity
	TConstVel = MaxVelocity / Accel;
	
	// deceleration period begins at this time
	TDecel = Dist / MaxVelocity;
	
	// max travel time is the sum of the previous two values
	TMax = TDecel + TConstVel;
	
	SmartDashboard::PutNumber("TConstVel", TConstVel);
	SmartDashboard::PutNumber("TDecel", TDecel);
	SmartDashboard::PutNumber("TMax", TMax);
}

// Get the desired velocity based on the amount of time that has elapsed
float Profile::GetDesiredVel(float elapsedTime)
{
	float desiredVel = 0.0;
	
	// if we are in the initial acceleration period
	if (elapsedTime < TConstVel)
	{
		desiredVel =  Accel * elapsedTime;
	}
	// if we are in the constant velocity period
	else if (elapsedTime < TDecel)
	{
		desiredVel = MaxVelocity;
	}
	// if we are in the final deceleration period
	else if (elapsedTime < TMax)
	{
		desiredVel = MaxVelocity - (Accel * (elapsedTime - TDecel));
	}
	
	// if we are moving in reverse, our desired velocity will be negative
	if (!DirForward)
	{
		desiredVel = -desiredVel;
	}
	
	return desiredVel;
}
