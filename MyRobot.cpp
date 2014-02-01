#include "Robot.h"

class RobotDemo : public SimpleRobot
{
	
	
	AnalogChannel range;
	AnalogChannel feederAngle;
	RobotDrive myRobot;
	Joystick stick1;
	Relay light;
	DigitalInput limitSwitch; 
	Victor feederArm;
	Victor feederWheel;
	
public:
	RobotDemo():
		
		range(1),
		feederAngle(2),
		myRobot(1, 2),	
		stick1(1),
		light(1),
		limitSwitch(1),
		feederArm(6),
		feederWheel(8)
	{
		myRobot.SetExpiration(0.1);
		light.Set(light.kOn);
	}

	
	void Autonomous()
	{
		myRobot.SetSafetyEnabled(false);
		
		Wait(0.075);
		AxisCamera &camera = AxisCamera::GetInstance();

				
		while(IsAutonomous() && IsEnabled())
		if(true){
			
			Wait(0.075);
		ColorImage *image;
		image = camera.GetImage();

		light.Set(light.kForward);
		
		Wait(0.125);

		BinaryImage *bimage2 = image->ThresholdRGB(0,50, 200, 255, 0, 255);
		delete &image;
		delete image;
		
		Wait(0.075);
		
		if(bimage2->GetNumberParticles()<2){
			//light.Set(light.kOn);
		}
		else{
			light.Set(light.kOff);
			//Wait(1000);
			/*vector< ParticleAnalysisReport > * reports = bimage->GetOrderedParticleAnalysisReports(); 
			for(int i = 0; i<2; i++){
				Rect rect = reports->at(i).boundingRect;
				
				//vertical
				if(rect.height>rect.width){
					light.Set(light.kOff);
				}
				
				//horizontal
				else{
					
				}
			}*/
		}
		delete &bimage2;
		delete bimage2;
		}
		
		
		
	}


	void OperatorControl()
	{
		SmartDashboard::init();
		myRobot.SetSafetyEnabled(true);
		
		
		
		//int n = 0;
		//float sum = 0;
		bool buttonState = stick1.GetRawButton(6);
		bool lightState = false;
		bool changed = false;
		while(IsOperatorControl())
		{
			bool state = stick1.GetRawButton(6);
			
			if (state != buttonState)
			{
				if (state)
				{
					lightState = !lightState;
					changed = true;
				}
			}
			
			
			
			if (lightState)
			{
				light.Set(light.kForward);
			}
			else
			{
				light.Set(light.kOff);
			}
			
			changed = false;
			
			buttonState=state;

			myRobot.TankDrive(-stick1.GetRawAxis(5), -stick1.GetRawAxis(2));
			float distance = getInch(range.GetAverageVoltage());
			bool limswitch = limitSwitch.Get();
			SmartDashboard::PutNumber("distance", distance);
			//SmartDashboard::PutNumber("angle", angle);
			SmartDashboard::PutNumber("limit switch", limswitch);
			//sum+=distance;
			//if(n%100==0){
				//SmartDashboard::PutNumber("distance", sum/100.);
				//sum=0;
			//}
			//n++;
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
	
	float getAngle(float voltage){
		float scale = 5.0/250.0;
		return voltage/scale;
	}
};

START_ROBOT_CLASS(RobotDemo);
