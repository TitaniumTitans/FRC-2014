#include "WPILib.h"

class PIDControl
{
  public:

	PIDControl(void);
	void SetKp(float kp);
	void SetKi(float ki);
	void SetKd(float kd);
	float CalcMotorOutput(float desiredVal, float actualVel, float elapsedTime);
	void Reset();

  private:
	
	float Kp;
	float Ki;
	float Kd;
	float PrevOutput;
	float PrevTime;
	float PrevError;
	float ErrorInt;
};
