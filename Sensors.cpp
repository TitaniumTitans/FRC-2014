#include "Sensors.h"

Sensors::Sensors(Controllers* driverInput, int rangeAnalogIn, int lightRelayPort)
{
	this->driverInput = driverInput;
	range = new AnalogChannel(rangeAnalogIn);
	distance = 0;
	count=0;
	distances = new vector<float>();
}

void Sensors::GetInputs()
{
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
	
	distance = ave;
	
	if(distances->size()>=20)
	{
		distances->erase(0);
	}
	
}

float Sensors::GetDistance()
{
	return distance;
}

float Sensors::GetInch(float voltage){
		float scale = 5./512.;
		return voltage/scale;
}
