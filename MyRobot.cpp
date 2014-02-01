#include "WPILib.h"
#include "Feeder.h"
<<<<<<< HEAD
=======

#define AREA_MINIMUM 50
>>>>>>> 8416ec77980e2ba5833fadb6e224b951d56a93b5

class RobotDemo : public SimpleRobot
{
	
	
	AnalogChannel range;
	AnalogChannel feederAngle;
	RobotDrive myRobot;
	Joystick stick1;
	Joystick stick2;
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
		stick2(2), 
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
<<<<<<< HEAD

=======
		Threshold threshold(115, 180, 230, 255, 225, 255);
		/*ParticleFilterCriteria2 criteria[] = {
						{IMAQ_MT_AREA, AREA_MINIMUM, 65535, false, false}
		};*/
		//BinaryImage *bimage2;
		
>>>>>>> 8416ec77980e2ba5833fadb6e224b951d56a93b5
				
		while(IsAutonomous() && IsEnabled())
		if(true){
			
			Wait(0.075);
		ColorImage *image;
		image = camera.GetImage();
<<<<<<< HEAD

		light.Set(light.kForward);
		
		Wait(0.125);

		BinaryImage *bimage2 = image->ThresholdRGB(0,50, 200, 255, 0, 255);
		delete &image;
		delete image;
=======
		//image->Write("/original.bmp");
		
		//image->Write("Orig.bmp");
		light.Set(light.kOn);
		
		Wait(0.125);
		//BinaryImage *bimage = image->ThresholdHSV(threshold);
		BinaryImage *bimage2 = image->ThresholdRGB(0,50, 200, 255, 0, 255);
		//bimage->Write("/bimage.bmp");
		//bimage2->Write("/bimage2.bmp");
		
		//BinaryImage *filteredImage = bimage2->ParticleFilter(criteria, 1);
		//filteredImage->Write("/filtered.bmp");
		
		//bimage->Write("/bimage.png");
		//Wait(0.2);
		//light.Set(light.kOff);
>>>>>>> 8416ec77980e2ba5833fadb6e224b951d56a93b5
		
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
<<<<<<< HEAD
		delete &bimage2;
		delete bimage2;
=======
>>>>>>> 8416ec77980e2ba5833fadb6e224b951d56a93b5
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
<<<<<<< HEAD
				light.Set(light.kForward);
=======
				light.Set(light.kOn);
>>>>>>> 8416ec77980e2ba5833fadb6e224b951d56a93b5
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
