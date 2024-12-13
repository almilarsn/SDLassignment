#ifndef SENSOR_H
#define SENSOR_H

#include <vector>

class Sensor {
private:
	int dataRangeMin;
	int dataRangeMax;

public:
	Sensor(int min, int max);
	int dataPointGenerator();
	std::vector<int> collectDataPoint(int count);

};

#endif
