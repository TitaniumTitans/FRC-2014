#include "WPILib.h"
#include "Drive.h"
#include "Operater.h"
#include "Feeder.h"



class RobotDemo : public SimpleRobot
{
	
	
	AnalogChannel range;
	//AnalogChannel* feederAngle;
	Feeder* myFeeder;
	Operater* driverInput;
	//Catapult* catapult;
	Drive* drive;
	
	
public:
	RobotDemo():
		
		range(1)
		//feederAngle(2),
		
		
	{
		driverInput = new Operater(1, 2);
		myFeeder = new Feeder(3, 4);
		drive = new Drive(driverInput);
	}

	
	void Autonomous()
	{
		//myRobot.SetSafetyEnabled(false);
				
		while(IsAutonomous() && IsEnabled())
		{
	
		}
	}

	void OperatorControl()
	{
		SmartDashboard::init();
		//myRobot.SetSafetyEnabled(true);
		
		
		
		//int n = 0;
		//float sum = 0;
		/*bool buttonState = stick1.GetRawButton(6);
		bool lightState = false;
		bool changed = false;*/
		while(IsOperatorControl() && IsEnabled())
		{
			
			driverInput->GetInputs();
			drive->GetInputs();
			//catapult.GetInputs();
			myFeeder->GetInputs();
			
			drive->ExecStep();
			//catapult.ExecStep();
			myFeeder->ExecStep();
			
		
			//catapult.SetOutput();
			myFeeder->SetOutputs();
			
			Wait(0.005);				
		}
	}

	void Test() {

	}

};

START_ROBOT_CLASS(RobotDemo);
