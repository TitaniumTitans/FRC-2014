#include "Sensors.h"

Sensors::Sensors(int rangeAnalogIn, int left1, int left2, int right1, int right2, int top1, int top2)
{
	range = new AnalogChannel(rangeAnalogIn);
	leftEncoder = new Encoder(left1 , left2);
	rightEncoder= new Encoder(right1,right2);
	topEncoder  = new Encoder(top1  ,  top2);
	
	leftEncoder->SetDistancePerPulse(1);
	rightEncoder->SetDistancePerPulse(1);
	topEncoder->SetDistancePerPulse(1);
	
	leftEncoder->Start();
	rightEncoder->Start();
	topEncoder->Start();
	
	distanceRange = 0;
	distanceEncod = 0;
	index = 0;
	count=0;
	sampleSize = 20;
	//distances = new vector<float>();
}

void Sensors::GetInputs()
{
	float leftDist = leftEncoder->GetDistance();
	float rightDist=rightEncoder->GetDistance();
	
	SmartDashboard::PutNumber("Left Encoder" , leftDist);
	SmartDashboard::PutNumber("Right Encoder",rightDist);
	
	distanceEncod = (leftDist + rightDist) / 2;
	
	distances[index] = (GetInch(range->GetVoltage()));
	this->count++;
	this->index++;
	//distanceRange = index;
	if(count%sampleSize){
		std::sort(distances, distances+sampleSize);
			
		float ave = 0;
		int cnt = 0;
		for(int i = sampleSize/4; i < sampleSize*0.75; i++)
		{
			cnt++;
			ave= ave + distances[i];
		}
		ave/=cnt;
		
		distanceRange = ave;
	}
	if(index>sampleSize-1)
		index = 0;
	
	
	/*
	if(distances->size()>=20)
	{
		distances->erase(0);
	}*/
	
}

float Sensors::GetDistanceTraveled()
{
	return distanceEncod;
}

float Sensors::GetDistance()
{
	//distanceRange = 1.8978;
	return distanceRange;
}

float Sensors::GetInch(float voltage)
{
		float scale = 5./512.;
		return voltage/scale;
}

