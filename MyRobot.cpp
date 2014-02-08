#include "WPILib.h"
#include "Drive.h"
#include "Controllers.h"
#include "Feeder.h"
#include "Catapult.h"

#define LEFT_MOTOR_PWM 		4
#define RIGHT_MOTOR_PWM		5
#define FEEDER_ARM_PWM		6
#define FEEDER_WHEEL_PWM	10
#define CATAPAULT_WHEEL_PWM	2

#define FEEDER_ANGLE_ANALOG	3

#define LEFT_LIMIT_SWITCH	1
#define RIGHT_LIMIT_SWITCH	2


class Robot : public SimpleRobot
{	
	AnalogChannel range;
	//AnalogChannel* feederAngle;
	Feeder* feeder;
	Controllers* driverInput;
	Catapult* catapult;
	Drive* drive;
	
	
public:
	Robot():
		
		range(1)
		//feederAngle(2),
		
		
	{
		//feederAngle = new AnalogChannel(3);
		driverInput = new Controllers(1, 2);
		feeder = new Feeder(driverInput, FEEDER_ARM_PWM, FEEDER_WHEEL_PWM, FEEDER_ANGLE_ANALOG);
		drive = new Drive(driverInput, LEFT_MOTOR_PWM, RIGHT_MOTOR_PWM);
		catapult = new Catapult(driverInput, CATAPAULT_WHEEL_PWM, LEFT_LIMIT_SWITCH, RIGHT_LIMIT_SWITCH);
	}

	
	void Autonomous()
	{
		SmartDashboard::init();
		//myRobot.SetSafetyEnabled(false);
				
		while(IsAutonomous() && IsEnabled())
		{
			SmartDashboard::PutString("tasdfajhsdfsetetsettests", "iosjdfio");
			//drive->ExecStep();

		}
	}

	void OperatorControl()
	{
		SmartDashboard::init();
		//myRobot.SetSafetyEnabled(true);
		
		//AnalogChannel* pot = new AnalogChannel(1);
		
		//int n = 0;
		//float sum = 0;
		/*bool buttonState = stick1.GetRawButton(6);
		bool lightState = false;
		bool changed = false;*/
		//Victor* wheel = myFeeder->GetWheel();
		int n = 0;
		while(IsOperatorControl() && IsEnabled())
		{
			//SmartDashboard::init();
			
			//SmartDashboard::PutNumber("tasdfajhsdfsetetsettests", n++);
			//SmartDashboard::PutNumber("feeder angle", feederAngle->GetVoltage());
			
			driverInput->GetInputs();
			drive->GetInputs();
			catapult->GetInputs();
			feeder->GetInputs();
			SmartDashboard::PutNumber("feeder angle", feeder->GetAngle());
			//myFeeder->SetState(myFeeder->FEEDER_STATE_DOWN);
			
			//wheel->Set(1);
			
			
			catapult->SetSafeToFire(feeder->GetAngle()<95);
			
			drive->ExecStep();
			catapult->ExecStep();
			feeder->ExecStep();
			
		
			catapult->SetOutputs();
			//myFeeder->SetOutputs();
			
			Wait(0.005);				
		}
	}

	void Test() {
		
		//while(IsTest()&&IsEnabled()){
			
		//}
		
	}

};

START_ROBOT_CLASS(Robot);
