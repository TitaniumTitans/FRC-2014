#include "WPILib.h"
#include "Controllers.h"
#include <vector>

class Sensors
{
  public:
	Sensors(Controllers* driverInput, int rangeAnalogIn, int lightRelayPort);
	void GetInputs();
	float GetDistance();
	
  private:
	Controllers* driverInput;
	AnalogChannel* range;
	float distance;
	float GetInch(float voltage);
	int count;
	//Relay light;
	std::vector<float>* distances;
	//AxisCamera &camera;
	
};
