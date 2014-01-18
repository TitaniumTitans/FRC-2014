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
		light.Set(light.kOn);
	}

	
	void Autonomous()
	{
		myRobot.SetSafetyEnabled(false);
		
		Wait(0.25);
		AxisCamera &camera = AxisCamera::GetInstance();
				
		while(IsAutonomous()){
			light.Set(light.kOn);
			Wait(0.2);
		ColorImage *image;
		image = camera.GetImage();
		
		//image->Write("Orig.bmp");
		
		Wait(0.2);
		
		BinaryImage *bimage = image->ThresholdRGB(0,50, 200, 255, 0, 255);
		
		//bimage->Write("/bimage.png");
		Wait(0.2);
		//light.Set(light.kOff);
		
		Wait(1);
		
		if(bimage->GetNumberParticles()<2){
			//light.Set(light.kOff);
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
		}
		
		
		
	}


	void OperatorControl()
	{
		SmartDashboard::init();
		myRobot.SetSafetyEnabled(true);
		
		
		
		int n = 0;
		float sum = 0;
		bool buttonState = stick.GetRawButton(6);
		bool lightState = false;
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

			myRobot.TankDrive(-stick.GetRawAxis(5), -stick.GetRawAxis(2));
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
