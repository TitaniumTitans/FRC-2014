#include "WPILib.h"
#include "Drive.h"
#include "Controllers.h"
#include "Feeder.h"
#include "Catapult.h"
#include "Sensors.h"

#define CATAPULT_WHEEL_PWM	2
#define LEFT_MOTOR_PWM 		4
#define RIGHT_MOTOR_PWM		5
#define FEEDER_ARM_PWM		6
#define FEEDER_WHEEL_PWM	8 // or 0
#define CAMERA_LED			7

#define RANGE_FINDER_ANALOG	2
#define FEEDER_ANGLE_ANALOG	3

#define LEFT_LIMIT_SWITCH	1
#define RIGHT_LIMIT_SWITCH	3 //changed from 2

#define LEFT_SOLENOID		1
#define RIGHT_SOLENOID		2

//Alpha bot 
//#define LEFT_SOLENOID		2
//#define RIGHT_SOLENOID	4

//LIMIT_SWITCH				2

#define PERIOD_IN_SECONDS	0.01


class Robot : public SimpleRobot
{	
	Feeder* feeder;
	Controllers* driverInput;
	Catapult* catapult;
	Drive* drive;
	Timer* timer;
	
	
public:
	Robot()	
	{
		timer = new Timer();
		driverInput = new Controllers(PERIOD_IN_SECONDS, 1, 2);
		feeder = new Feeder(driverInput, FEEDER_ARM_PWM, FEEDER_WHEEL_PWM, FEEDER_ANGLE_ANALOG);
		drive = new Drive(driverInput, LEFT_MOTOR_PWM, RIGHT_MOTOR_PWM, LEFT_SOLENOID, RIGHT_SOLENOID);
		catapult = new Catapult(driverInput, CATAPULT_WHEEL_PWM, LEFT_LIMIT_SWITCH, RIGHT_LIMIT_SWITCH);
	}

	
	void Autonomous()
	{
		SmartDashboard::init();
		//myRobot.SetSafetyEnabled(false);
				
		while(IsAutonomous() && IsEnabled())
		{
			//drive->ExecStep();
			
			//SmartDashboard::PutString("State", "Started");
			
			/*
			DigitalInput *limitswitch = new DigitalInput(1);
			limitswitch->Get();
			*/
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
		//int n = 0;
		
		
		timer->Start();
		while(IsOperatorControl() && IsEnabled())
		{
			
			//SmartDashboard::PutNumber("tasdfajhsdfsetetsettests", n++);
			//SmartDashboard::PutNumber("feeder angle", feederAngle->GetVoltage());
			
			driverInput->GetInputs();
			drive->GetInputs();
			catapult->GetInputs();
			feeder->GetInputs();
			//SmartDashboard::PutNumber("Feeder Angle", feeder->GetAngle());
			//myFeeder->SetState(myFeeder->FEEDER_STATE_DOWN);
			
			//wheel->Set(1);
			
			//catapult->SetSafeToFire(feeder->GetAngle()<95); 
			
			drive->ExecStep(); 
			//catapult->ExecStep();
			feeder->ExecStep(); 
			
		
			//catapult->SetOutputs();
			feeder->SetOutputs();
			
			while(timer->Get()<(PERIOD_IN_SECONDS));
			timer->Reset();
			//Wait(0.005);
		}
	}

	void Test() {
		
		//while(IsTest()&&IsEnabled()){
			
		//}
		
	}

};

START_ROBOT_CLASS(Robot);
