#include "WPILib.h"
#include "Drive.h"
#include "Controllers.h"
#include "Feeder.h"
#include "Catapult.h"
#include "Sensors.h"
#include "AutonomousMode.h"

/*MOTORS*/
#define CATAPULT_WHEEL_PWM	2
#define LEFT_MOTOR_PWM 		4
#define RIGHT_MOTOR_PWM		5
#define FEEDER_ARM_PWM		6
#define FEEDER_WHEEL_PWM	8 // or 0

/*SPIKES*/
#define CAMERA_LED			4 //also B

/*ANALOG INPUTS*/
#define RANGE_FINDER_ANALOG	2
#define FEEDER_ANGLE_ANALOG	3

/*DIGITAL IO*/
#define LIMIT_SWITCH		1
#define LEFT_ENCODER_1		2
#define LEFT_ENCODER_2		3
#define RIGHT_ENCODER_1		4
#define RIGHT_ENCODER_2		5
#define TOP_ENCODER_1		6
#define TOP_ENCODER_2		7

/*SOLENOIDS*/
#define LEFT_SOLENOID		2
#define RIGHT_SOLENOID		4

/*AUTONOMOUS*/
#define STOP_DISTANCE_RANGE	24
#define STOP_DISTANCE_ENCOD	60
#define STOP_DRIVING_TIME	0.5

#define AUTO_RANGEONLY		0
#define AUTO_RANGEANDENCOD	1
#define AUTO_ENCODONLY		2
#define AUTO_TIMEONLY		3


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
	Sensors* sensors;
	AutonomousMode* autonomous;
	
  public:
	
	//
	// Constructor
	//
	Robot()	
	{
		SmartDashboard::init();
		timer = new Timer();
		driverInput = new Controllers(PERIOD_IN_SECONDS, 1, 2);
		feeder = new Feeder(driverInput, FEEDER_ARM_PWM, FEEDER_WHEEL_PWM, FEEDER_ANGLE_ANALOG);
		drive = new Drive(driverInput, LEFT_MOTOR_PWM, RIGHT_MOTOR_PWM, LEFT_SOLENOID, RIGHT_SOLENOID);
		catapult = new Catapult(driverInput, CATAPULT_WHEEL_PWM, LIMIT_SWITCH);
		sensors = new Sensors(RANGE_FINDER_ANALOG, LEFT_ENCODER_1, LEFT_ENCODER_2, RIGHT_ENCODER_1, RIGHT_ENCODER_2, TOP_ENCODER_1, TOP_ENCODER_2);
		
	}

	//
	// Main Autonomous Mode function.  This function is called once, therefore a while loop that checks IsAutonomous and IsEnabled is used 
	// to maintain control until the end of autonomous mode
	//
	void Autonomous()
	{
		// Initialize Smart Dashboard
		SmartDashboard::init();
		
		autonomous = new AutonomousMode(AUTO_TIMEONLY, drive->myRobot, sensors, catapult, STOP_DISTANCE_RANGE, STOP_DISTANCE_ENCOD, STOP_DRIVING_TIME, CAMERA_LED);
		
		//myRobot->SetSafetyEnabled(false);
		
		AxisCamera &camera = AxisCamera::GetInstance();
		
		
		while(IsAutonomous() && IsEnabled())
		{
			feeder->GetInputs();
			sensors->GetInputs();
			
			ColorImage *image;
			image = camera.GetImage();
		

			SmartDashboard::PutNumber("Range Finder Distance", sensors->GetInch(sensors->range->GetVoltage()));
			SmartDashboard::PutNumber("Range Finder Average Distance", sensors->GetDistance());
			autonomous->GetInputs(image);
			
			//autonomous->ExecStep();
			
			//autonomous->SetOutputs();
			
			//delete &image;
			delete image;
			
			Wait(0.01);
			/*
			DigitalInput *limitswitch = new DigitalInput(1);
			limitswitch->Get();
			*/
		}
	}

	//
	// Main Tele Operator Mode function.  This function is called once, therefore a while loop that checks IsOperatorControl and IsEnabled is used 
	// to maintain control until the end of tele operator mode
	//
	void OperatorControl()
	{
		//myRobot.SetSafetyEnabled(true);
		
		timer->Start();
		
		while (IsOperatorControl() && IsEnabled())
		{
			
			//
			// Get inputs
			//
			driverInput->GetInputs();
			drive->GetInputs();
			catapult->GetInputs();
			feeder->GetInputs();
			
			//
			// Pass values between components as necessary
			//
			catapult->SetSafeToFire(feeder->GetAngle()<95); 
			
			//
			// Execute one step on each component
			//
			drive->ExecStep(); 
			catapult->ExecStep();
			feeder->ExecStep(); 
			
		    //
			// Set Outputs on all components
			//
			catapult->SetOutputs();
			feeder->SetOutputs();
			
			//
			// Wait for step timer to expire.  This allows us to control the amount of time each step takes. Afterwards, restart the 
			// timer for the next loop
			//
			while (timer->Get()<(PERIOD_IN_SECONDS))
				;
			timer->Reset();

		}
	}

	void Test() 
	{
		SmartDashboard::init();
		Joystick* driverStick = driverInput->GetDriverJoystick();
		//Relay* redLights = new Relay(1, Relay::kForward);
		//Relay* blueLights = new Relay(2, Relay::kForward);
		//Relay* cameraLights = new Relay(CAMERA_LED);
		//Relay* redLights = new Relay(1, Relay::kForward);
		//Solenoid *rightSolenoid;
		//Solenoid *leftSolenoid;
			
		bool gear = false;
		bool prevShiftButttonPressed = false;
		
		Victor* motors [] = {feeder->feederWheel, feeder->feederArm, drive->leftDrive, drive->rightDrive, catapult->ChooChooMotor};		
		Relay* compressorspike = new Relay(1);
		Relay* cameraLights = new Relay(4);

		while (IsTest() && IsEnabled())
		{
			bool curShiftButtonPressed = driverStick->GetRawButton(10);
			
			//sensors->GetInputs();
			
			//SmartDashboard::PutNumber("Rangefinder", sensors->GetDistance());
			
			/*FEEDER WHEEL*/
			if (driverStick->GetRawButton(2)) 
			{
				motors[0]->Set(1.0);
			}
			
			else 
			{
				motors[0]->Set(0);
			}
			
			/*FEEDER ARM*/
			if (driverStick->GetRawButton(3)) 
			{
				motors[1]->Set(-0.2);
			}
			
			else 
			{
				motors[1]->Set(0);
			}
			
			/*LEFT DRIVE*/
			if (driverStick->GetRawButton(4)) 
			{
				motors[2]->Set(0.8);
			}
			
			else 
			{
				motors[2]->Set(0);
			}
			
			/*RIGHT DRIVE*/
			if (driverStick->GetRawButton(5)) 
			{
				motors[3]->Set(0.8);
			}
			
			else 
			{
				motors[3]->Set(0);
			}
			
			/*CHOOCHOO MOTOR*/
			if (driverStick->GetRawButton(7) && driverStick->GetRawButton(1)) 
			{
				motors[4]->Set(0.6);
			}
			
			else 
			{
				motors[4]->Set(0);
			}
			
			/*CAMERA LED*/
			if (driverStick->GetRawButton(8)) 
			{
				cameraLights->Set(cameraLights->kForward);
			}
			else 
			{
				cameraLights->Set(cameraLights->kOff);
			}
			
			/*GEAR SHIFT*/
			/*
			if (curShiftButtonPressed && !prevShiftButttonPressed) 
			{
				drive->SetHighGear(!gear);
			}
			*/
			
			if (driverStick->GetRawButton(10))
			{
				drive->SetHighGear(!gear);
				//gear != gear;
			}
			
			/*COMPRESSOR*/
			if(driverStick->GetRawButton(11)) 
			{
				compressorspike->Set(compressorspike->kOn);
			}
			else 
			{
				compressorspike->Set(compressorspike->kOff);
			}
			prevShiftButttonPressed = curShiftButtonPressed;
		}		
	}

};

START_ROBOT_CLASS(Robot);
