#include "WPILib.h"


class RobotDemo : public SimpleRobot
{
	
	
	AnalogChannel range;
	RobotDrive myRobot;
	Joystick stick;
	Relay light;
	
	
public:
	RobotDemo():
		
		range(1),
		myRobot(1, 2),	
		stick(1),		
		light(1)
	{
		myRobot.SetExpiration(0.1);
	}

	
	void Autonomous()
	{
		myRobot.SetSafetyEnabled(false);

	}


	void OperatorControl()
	{
		SmartDashboard::init();
		myRobot.SetSafetyEnabled(true);
		int n = 0;
		float sum = 0;
		bool buttonState = stick.GetRawButton(6);
		bool lightState = 0;
		bool changed = false;
		while(IsOperatorControl())
		{
			bool state = stick.GetRawButton(6);
			
			if(state!=buttonState){
				if(state){
					lightState = !lightState;
					changed = true;
				}
			}
			
			
			if(lightState) light.Set(light.kOn);
			else light.Set(light.kOff);
			
			changed = false;
			
			buttonState=state;

			myRobot.TankDrive(stick.GetRawAxis(2), stick.GetRawAxis(5));
			float distance = getInch(range.GetAverageVoltage());
			sum+=distance;
			if(n%100==0){
				SmartDashboard::PutNumber("distance", sum/100.);
				sum=0;
			}
			n++;
			Wait(0.005);				
		}
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {

	}
	
	float getInch(float voltage){
		float scale = 5./512.;
		return voltage/scale;
	}
};

START_ROBOT_CLASS(RobotDemo);
