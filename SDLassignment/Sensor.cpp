#include "Sensor.h"
#include <cstdlib>
#include <ctime>

Sensor::Sensor(int min, int max) : dataRangeMin(min), dataRangeMax(max) {
	std::srand(std::time(0));
}

int Sensor::dataPointGenerator() {
	return dataRangeMin + (std::rand() % (dataRangeMax - dataRangeMin + 1));
}

std::vector<int> Sensor::collectDataPoint(int count) {
	std::vector<int> data;
	for (int i = 0; i < count; ++i) {
		data.push_back(dataPointGenerator());
	}
	return data;

}
