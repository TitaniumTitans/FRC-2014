#include "AutonomousMode.h"

#define TIME_FORWARD	1.1
#define TIME_WAIT_SHOOT	0.25
#define TIME_SHOOT		2
#define TIME_PICKUPBALL	2.2
#define TIME_WAIT		1
#define TIME_BACKWARD	1.1
#define TIME_FORWARD2	1.6
#define TWO_BALL_AUTO	false


AutonomousMode::AutonomousMode(int mode, RobotDrive* myRobot, Sensors* sensors, Catapult* catapult, int stopDistRange, int stopDistEncod, float stopTime, int lightPort)
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
	catapult->GetFeeder()->HOME_FEEDER_ANGLE;
	firedAlready = false;
}

void AutonomousMode::GetInputs()//ColorImage* image)
{
	sensors->GetInputs();
	
	distanceTrav = sensors->GetDistanceTraveled();
	distance = sensors->GetDistance();
	
	
	//SmartDashboard::PutNumber("Encoder Dist Traveled");
	
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
	//delete image;
}

void AutonomousMode::ExecStep()
{
/*
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
		if (timer->Get()<stopTime)
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
	*/
	
	
	if(TWO_BALL_AUTO){
		//going forward first time
		if (timer->Get() < TIME_FORWARD)//stopTime+0.25)
		{
			motorOut=1;
		}
		//Wait before shoot
		else if(timer->Get() < TIME_FORWARD + TIME_WAIT_SHOOT)
		{
			motorOut=0;
		}
		//time to shoot
		else if(timer->Get() < TIME_FORWARD + TIME_WAIT_SHOOT + TIME_SHOOT)
		{
			//motorOut=0;
			shoot = true;
		}
		//time going backwards
		else if(timer->Get() < TIME_FORWARD + TIME_WAIT_SHOOT + TIME_SHOOT + TIME_BACKWARD)
		{
			shoot=false;
			firedAlready=false;
			motorOut=-1;//-1
			catapult->GetFeeder()->SetState(catapult->GetFeeder()->FEEDER_STATE_DOWN);
		}
		//Wait
		else if(timer->Get() < TIME_FORWARD + TIME_WAIT_SHOOT + TIME_SHOOT + TIME_BACKWARD + 0.8)
		{
			motorOut=0;
		}
		//time picking up the second ball
		else if(timer->Get() < TIME_FORWARD + TIME_WAIT_SHOOT + TIME_SHOOT + TIME_BACKWARD + TIME_PICKUPBALL)
		{
			motorOut=-0.3;
		}
		else if(timer->Get() < TIME_FORWARD + TIME_WAIT_SHOOT + TIME_SHOOT + TIME_BACKWARD + TIME_PICKUPBALL + 1)
		{
			motorOut=0;
		}
		//time driving forward with the second ball
		else if(timer->Get() < TIME_FORWARD + TIME_WAIT_SHOOT + TIME_SHOOT + TIME_BACKWARD + TIME_PICKUPBALL + TIME_FORWARD2)
		{
			motorOut=1;//1
			catapult->GetFeeder()->SetState(catapult->GetFeeder()->FEEDER_STATE_HOME);
		}
		//Time waiting
		else if(timer->Get() > TIME_FORWARD + TIME_WAIT_SHOOT + TIME_SHOOT + TIME_BACKWARD + TIME_PICKUPBALL + TIME_FORWARD2 + TIME_WAIT + 0.1)
		{
			motorOut=0;
			shoot=true;
		}
	}
	else{
		if (timer->Get()< TIME_FORWARD)
		{
			motorOut=1;
		}
		else if (timer->Get() < TIME_FORWARD + 0.5){
			motorOut = 0;
		}
		else{
			//motorOut = 0;
			shoot=true;
		}
	}
	
	
	
}

void AutonomousMode::SetOutputs(){
	myRobot->TankDrive(-motorOut, -motorOut);
	
	catapult->GetFeeder()->GetInputs();
	catapult->GetFeeder()->ExecStep();
	catapult->GetFeeder()->SetOutputs();
	
	
	if (shoot&&!firedAlready)
	{
		//catapult->SetSafeToFire();
		catapult->SetState(catapult->CATAPULT_STATE_FIRE);
		firedAlready = true;
	}
	catapult->GetInputs();
	catapult->ExecStep();
	catapult->SetOutputs();
}

