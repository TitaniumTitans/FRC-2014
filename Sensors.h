#ifndef SENSORS_H
#define SENSORS_H

#include "WPILib.h"
#include "Controllers.h"
#include <vector>

class Sensors
{
  public:
	Sensors(int rangeAnalogIn, int left1, int left2, int right1, int right2, int top1, int top2);
	void GetInputs();
	float GetDistance();
	float GetDistanceTraveled();
	
  private:
	AnalogChannel* range;
	Encoder* leftEncoder;
	Encoder* rightEncoder;
	Encoder* topEncoder;
	float distanceRange;
	float distanceEncod;
	float GetInch(float voltage);
	int count;
	//Relay light;
	std::vector<float>* distances;
	//AxisCamera &camera;
	
};

#endif /* SENSORS_H */
