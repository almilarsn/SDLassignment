#include "DataProcessor.h"
#include <algorithm>

DataProcessor::DataProcessor(const std::vector<int> & data) : rawData(data){}

//simple avarage filter
void DataProcessor::simpleAvarageFilter() {
	double sum = 0;
	for (int val : rawData)
	{
		sum += val;
	}
	double avg = sum / rawData.size();
	processedData.assign(rawData.size(), avg);

}

//moving avarage filter
void DataProcessor::movingAvarageFilter(int windowSize) {	
	std::vector<double> smoothedData;

	for (size_t i = 0; i <= rawData.size() - windowSize; ++i)
	{
		double sum = 0;

		for (size_t j = 1; j < 1 + windowSize; ++j) {
			sum += rawData[j];
		}
		smoothedData.push_back(sum / windowSize);
	}
	
	processedData = smoothedData;
}

//overall avarage
double DataProcessor::overallAvarage() {
	double sum=0;
	
	for (int val: rawData)
	{
		sum += val;
	}
	return sum / rawData.size();
}

//min value
int DataProcessor::findMinValue() {
	int minValue = rawData[0];

	for (size_t i = 1; i < rawData.size(); ++i)
	{
		if (rawData[i] < minValue )
		{
			minValue = rawData[i];
		}

	}
	return minValue;
}

//max value 

int DataProcessor::findMaxValue() {

	int maxValue = rawData[0];
	for (size_t i = 1; i < rawData.size(); ++i)
	{
		if (rawData[i] > maxValue) {
			maxValue = rawData[i];
		}
	}
	return maxValue;
}

//getter for processed data

const std::vector<double>& DataProcessor::getProcessedData() const {
	return processedData;
}

