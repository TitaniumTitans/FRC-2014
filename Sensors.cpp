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
	
	count=0;
	distances = new vector<float>();
}

void Sensors::GetInputs()
{
	
	distanceEncod = (leftEncoder->GetDistance() + rightEncoder->GetDistance()) / 2;
	
	distances->push_back(GetInch(range->GetVoltage()));
	count++;
	
	std::sort(distances->begin(), distances->end());
	
	float ave = 0;
	int cnt = 0;
	for(int i = distances->size()/4; i < distances->size()*0.75; i++)
	{
		cnt++;
		ave= ave + distances->at(i);
	}
	ave/=cnt;
	
	distanceRange = ave;
	
	if(distances->size()>=20)
	{
		distances->erase(0);
	}
	
}

float Sensors::GetDistanceTraveled()
{
	return distanceEncod;
}

float Sensors::GetDistance()
{
	return distanceRange;
}

float Sensors::GetInch(float voltage)
{
		float scale = 5./512.;
		return voltage/scale;
}
