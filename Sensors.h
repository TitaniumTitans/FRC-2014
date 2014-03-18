#ifndef SENSORS_H
#define SENSORS_H

#include "WPILib.h"
#include "Controllers.h"
#include <algorithm>

class Sensors
{
  public:
	Sensors(int rangeAnalogIn, int left1, int left2, int right1, int right2, int top1, int top2);
	void GetInputs();
	float GetDistance();
	float GetDistanceTraveled();
	float GetInch(float voltage);
	AnalogChannel* range;
	
  private:
	
	Encoder* leftEncoder;
	Encoder* rightEncoder;
	Encoder* topEncoder;
	float distanceRange;
	float distanceEncod;
	int count;
	//Relay light;
	float distances [20];
	int index;
	int sampleSize;
	//AxisCamera &camera;
	
};

#endif /* SENSORS_H */
