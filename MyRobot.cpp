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
#define CAMERA_LED			5 //also B
#define RED_LED				4 //Working
#define BLUE_LED			2 //Not Working

/*ANALOG INPUTS*/
#define RANGE_FINDER_ANALOG	2
#define FEEDER_ANGLE_ANALOG	1

/*DIGITAL IO*/
#define LIMIT_SWITCH		2//1
#define LEFT_ENCODER_1		4
#define LEFT_ENCODER_2		5
#define RIGHT_ENCODER_1		7
#define RIGHT_ENCODER_2		8
#define TOP_ENCODER_1		6
#define TOP_ENCODER_2		7

/*SOLENOIDS*/
#define LEFT_SOLENOID		2
#define RIGHT_SOLENOID		4

/*AUTONOMOUS*/
#define STOP_DISTANCE_RANGE	24
#define STOP_DISTANCE_ENCOD	60
#define STOP_DRIVING_TIME	1

#define AUTO_RANGEONLY		0
#define AUTO_RANGEANDENCOD	1
#define AUTO_ENCODONLY		2
#define AUTO_TIMEONLY		3

#define COMPRESSOR_RELAY	2
#define COMPRESSOR_SWITCH	1

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
		catapult = new Catapult(driverInput, feeder, CATAPULT_WHEEL_PWM, LIMIT_SWITCH, RED_LED, BLUE_LED);
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
		
		//AxisCamera &camera = AxisCamera::GetInstance();
		
		//Relay* redddlight = new Relay(4);
		//Timer* lighttimer = new Timer();
		//lighttimer->Start();
		while(IsAutonomous() && IsEnabled())
		{
			/*
			if (lighttimer->Get()<=0.25) {
				redddlight->Set(redddlight->kForward);
			}
			else if(lighttimer->Get()<0.5){
				redddlight->Set(redddlight->kOff);
			}
			else {
				lighttimer->Reset();
			}
			*/
			feeder->GetInputs();
			sensors->GetInputs();
			
			//ColorImage *image;
			//image = camera.GetImage();
		

			//SmartDashboard::PutNumber("Range Finder Distance", sensors->GetInch(sensors->range->GetVoltage()));
			//SmartDashboard::PutNumber("Range Finder Average Distance", sensors->GetDistance());
			autonomous->GetInputs();
			
			autonomous->ExecStep();
			
			autonomous->SetOutputs();
			
			//delete &image;
			//delete image;
			
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
		Relay* reddlight = new Relay(4);
		//Timer* lighttimer = new Timer();
		//lighttimer->Start();
		while (IsOperatorControl() && IsEnabled())
		{
			reddlight->Set(reddlight->kForward);
			/*
			if (lighttimer->Get()<=0.5) {
				reddlight->Set(reddlight->kForward);
			}
			else if(lighttimer->Get()<1){
				reddlight->Set(reddlight->kOff);
			}
			else {
				lighttimer->Reset();
			}
			*/
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
			//catapult->SetSafeToFire(feeder->GetAngle()<95); 
			
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
			while (timer->Get()<(PERIOD_IN_SECONDS));
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
		
		Relay* compressor = new Relay(COMPRESSOR_RELAY);
		DigitalInput* compressorLimitSwitch = new DigitalInput(COMPRESSOR_SWITCH);
		//Compressor* compressor = new Compressor(1,1);//COMPRESSOR_SWITCH, COMPRESSOR_RELAY);
		//compressor->Start();
		Relay* cameraLights = new Relay(CAMERA_LED);
		//Solenoid* right = new Solenoid(6);
		//Solenoid* left = new Solenoid(5);
		
		//right->Set(true);
		//left->Set(true);
		
		//Relay* redlights = catapult->redled;
		//Relay* whitelights = catapult->whiteled;
		
		//redlights->Set(redlights->kForward);
		//whitelights->Set(whitelights->kForward);
		//cameraLights->Set(cameraLights->kForward);
		
		bool compressorOn = false;

		while (IsTest() && IsEnabled())
		{
			bool curShiftButtonPressed = driverStick->GetRawButton(10);
			
			//sensors->GetInputs();
			
			//SmartDashboard::PutNumber("Rangefinder", sensors->GetDistance());
			
			/*FEEDER WHEEL*/
			if (driverStick->GetRawButton(2)) 
			{
				motors[0]->Set(0.4);
			}
			
			else 
			{
				motors[0]->Set(0);
			}
			
			/*FEEDER ARM*/
			if (driverStick->GetRawButton(3)) 
			{
				motors[1]->Set(-0.6);
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
			/*
			if (driverStick->GetRawButton(6)) 
			{
				redlights->Set(redlights->kForward);
			}
			
			else 
			{
				redlights->Set(redlights->kOff);
			}
			*/
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
			
			/*
			if (curShiftButtonPressed && !prevShiftButttonPressed) 
			{
				drive->SetHighGear(!gear);
			}
			*/
			
			if (driverStick->GetRawButton(10))
			{
				drive->SetHighGear(true);//!gear
				
				gear = !gear;
			}
			else{
				drive->SetHighGear(false);
			}
			
			/*COMPRESSOR*/
			if(driverStick->GetRawButton(11)) 
			{
				compressorOn = true;
				//compressor->Set(compressor->kOn);
				//compressor->Start();
			}
			else 
			{
				//compressor->Stop();
			}
			if(driverStick->GetRawButton(9))
			{
				compressorOn = false;
				//compressor->Set(compressor->kOff);
				//compressor->Stop();
			}
			
			if(compressorOn){
				if(!compressorLimitSwitch->Get()){
					compressor->Set(compressor->kOn);
				}
				else{
					compressor->Set(compressor->kOff);
					compressorOn = false;
				}
					
					
			}
			else
				compressor->Set(compressor->kOff);
			
			
			prevShiftButttonPressed = curShiftButtonPressed;
		}		
	}

};

START_ROBOT_CLASS(Robot);
