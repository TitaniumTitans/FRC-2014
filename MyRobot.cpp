#include "WPILib.h"
#include "Drive.h"
#include "Controllers.h"
#include "Feeder.h"
#include "Catapult.h"
#include "Sensors.h"


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

/*SOLENOIDS*/
#define LEFT_SOLENOID		2
#define RIGHT_SOLENOID		4

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
		SmartDashboard::init();
		timer = new Timer();
		driverInput = new Controllers(PERIOD_IN_SECONDS, 1, 2);
		feeder = new Feeder(driverInput, FEEDER_ARM_PWM, FEEDER_WHEEL_PWM, FEEDER_ANGLE_ANALOG);
		drive = new Drive(driverInput, LEFT_MOTOR_PWM, RIGHT_MOTOR_PWM, LEFT_SOLENOID, RIGHT_SOLENOID);
		catapult = new Catapult(driverInput, CATAPULT_WHEEL_PWM, LIMIT_SWITCH);
	}

	
	void Autonomous()
	{
		SmartDashboard::init();
		//myRobot.SetSafetyEnabled(false);
				
		while(IsAutonomous() && IsEnabled())
		{
			//drive->ExecStep();
			
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
			
			catapult->SetSafeToFire(feeder->GetAngle()<95); 
			
			drive->ExecStep(); 
			catapult->ExecStep();
			
			feeder->ExecStep(); 
			
		
			catapult->SetOutputs();
			feeder->SetOutputs();
			while(timer->Get()<(PERIOD_IN_SECONDS));
			timer->Reset();
			//Wait(0.005);
		}
	}

	void Test() {
		SmartDashboard::init();
		Joystick* driverStick = driverInput->GetDriverJoystick();
		//Relay* redLights = new Relay(1, Relay::kForward);
		//Relay* blueLights = new Relay(2, Relay::kForward);
		Relay* cameraLights = new Relay(CAMERA_LED);
		//Relay* redLights = new Relay(1, Relay::kForward);
		
		
		Victor* motors [] = {feeder->feederWheel, feeder->feederArm, drive->leftDrive, drive->rightDrive, catapult->ChooChooMotor};	
		int index = 0;
		bool prevUp = false;
		bool prevDown = false;
		
		
		
		/*
		while(IsTest() && IsEnabled()){
			motors[index]->Set(0.2);
			bool curUp = driverStick->GetRawButton(3);
			bool curDown=driverStick->GetRawButton(2);
			
			if (curUp&&!prevUp){
				motors[index]->Set(0);
				if(index<(sizeof(motors)/sizeof(*motors))-1)
					index++;
				else
					index = 0;
				//SmartDashboard::PutString("Button 1", "Yes");
			}
			
			if (curDown&&!prevDown){
				motors[index]->Set(0);
				if(index>0)
					index--;
				else
					index = (sizeof(motors)/sizeof(*motors))-1;
				//SmartDashboard::PutString("Button 2", "Yes");
			}
			
			if(driverStick->GetRawButton(11))
				cameraLights->Set(cameraLights->kForward);
			else
				cameraLights->Set(cameraLights->kOff);
			
				
			prevUp = curUp;
			prevDown = curDown;
			
			SmartDashboard::PutNumber("Motor Currently Running", index+1);
		}
		
		*/

		while(IsTest() && IsEnabled()){
			if (driverStick->GetRawButton(1)) {
				motors[0]->Set(1.0);
			}
			
			else {
				motors[0]->Set(0);
			}
			
			if (driverStick->GetRawButton(2)) {
				motors[1]->Set(0.2);
			}
			
			else {
				motors[1]->Set(0);
			}
			
			if (driverStick->GetRawButton(3)) {
				motors[2]->Set(0.8);
			}
			
			else {
				motors[2]->Set(0);
			}
			
			if (driverStick->GetRawButton(4)) {
				motors[3]->Set(0.8);
			}
			
			else {
				motors[3]->Set(0);
			}
			
			if (driverStick->GetRawButton(4)) {
				motors[4]->Set(0.8);
			}
			
			else {
				motors[4]->Set(0);
			}
			
			if(driverStick->GetRawButton(5)) {
				cameraLights->Set(cameraLights->kForward);
			}
			else {
				cameraLights->Set(cameraLights->kOff);
			}
		}
		
		
		
	}

};

START_ROBOT_CLASS(Robot);
