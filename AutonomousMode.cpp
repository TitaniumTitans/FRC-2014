#include "AutonomousMode.h"

AutonomousMode::AutonomousMode(int mode, RobotDrive* myRobot, Sensors* sensors, Catapult* catapult, int stopDistRange, int stopDistEncod, int stopTime, int lightPort)
{
	this->mode = mode;
	this->myRobot = myRobot;
	this->sensors = sensors;
	this->light = new Relay(lightPort);
	this->catapult = catapult;
	timer = new Timer();
	catapult->SetState(catapult->CATAPULT_STATE_ARMED);
	this->stopDistRange= stopDistRange;
	this->stopDistEncod= stopDistEncod;
	this->stopTime= stopTime;
	this->motorOut = 0;
	this->distanceTrav = 0;
	this->distance = 0;
	this->shoot = false;
	this->camShoot = false;
	light->Set(light->kForward);
	timer->Start();
}

void AutonomousMode::GetInputs(ColorImage* image)
{
	sensors->GetInputs();
	
	distanceTrav = sensors->GetDistanceTraveled();
	distance = sensors->GetDistance();
	/*

	BinaryImage *bimage2 = image->ThresholdRGB(0,50, 200, 255, 0, 255);
	
	//image->Write("/orig.png");
	//image->Write("orig2.png");
	image->Write("/orig.bmp");
	//image->Write("orig2.bmp");
	bimage2->Write("/thresh.bmp");
	
	//delete &image;
	delete image;

	if (bimage2->GetNumberParticles()>=2)
	{
		SmartDashboard::PutBoolean("Hot Goal", true);
		//camShoot = true;
	}
	else SmartDashboard::PutBoolean("Hot Goal", false);
	
	//delete &bimage2;
	delete bimage2;
	*/
}

void AutonomousMode::ExecStep()
{

	if (mode==0)		//Rangefinder
	{
		if(distance>stopDistRange) 
		{
			motorOut = 1;
		}
		else
		{
			motorOut = 0;
			if (camShoot) 
			{
				shoot = true;
			}
		}
	}
	else if (mode==1)//Rangefinder and Encoder
	{
		if (distance>stopDistRange && distanceTrav<stopDistEncod)
		{
			motorOut=1;
		}
		else
		{
			motorOut=0;
			if (camShoot)
			{
				shoot = true;
			}
		}
	}
	else if (mode==2)//Encoder
	{
		if (distanceTrav<stopDistEncod)
		{
			motorOut=1;
		}
		else
		{
			motorOut = 0;
			if (camShoot) 
			{
				shoot = true;
			}
		}
	}
	else if (mode==3)//Time
	{
		if (timer->Get()>stopTime)
		{
			motorOut=1;
		}
		else
		{
			motorOut=0;
			{
				if(camShoot) shoot = true;
			}
		}
			
	}
	
	if (timer->Get() > 7)
	{
		shoot = true;
	}
	
}

void AutonomousMode::SetOutputs(){
	myRobot->TankDrive(motorOut, motorOut);
	if (shoot)
	{
		catapult->SetSafeToFire(true);
		catapult->SetState(catapult->CATAPULT_STATE_FIRE);
	}
	catapult->ExecStep();
	//catapult->SetOutputs();
}

