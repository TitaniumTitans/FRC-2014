#ifndef PROFILE_H
#define PROFILE_H

#include "WPILib.h"

class Profile
{
  public:

	Profile(void);
	void SetAccel(float accel);
	void SetMaxVelocity(float maxVel);
	void SetDist(float dist);
	void CalcProfile();
	void CalcProfile(float accel, float maxVel, float dist);
	float GetDesiredVel(float elapsedTime);
	
  private:
	
	float Accel;
	float MaxVelocity;
	float Dist;
	float TConstVel;
	float TDecel;
	float TMax;
	bool DirForward;
	
};

#endif
