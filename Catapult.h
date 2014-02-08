#include "WPILib.h"
#include "Controllers.h"

class Catapult
{
  public:
	Catapult::Catapult(Controllers* driverInput, int catapaultPWM, int leftLimitSwitch, int rightLimitSwitch);
	void Catapult::SetSafeToFire(bool safeFire);
	void Catapult::GetInputs();
	void Catapult::ExecStep(void);
	void Catapult::SetOutputs();
	
  private:
	Victor* ChooChooMotor;
	bool CommandToFire;
	bool SafeToFire;
	int FireTickCount;
	float ChooChooMotorSpeed;
	bool CatapultArmed;
	enum CATAPULT_STATE{
		CATAPULT_STATE_ARM = 0,
		CATAPULT_STATE_FIRE = 1,
		CATAPULT_STATE_ARMED = 2,
		CATAPULT_STATE_FIRING = 3
	};
	CATAPULT_STATE catapultState;
	Controllers* driverInput;
	DigitalIOButton* LeftLimitSwitch;
	DigitalIOButton* RightLimitSwitch;
};

