#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <vector>

class DataProcessor {
	private:
		std::vector<int> rawData;
		std::vector<double> processedData;
	public:
		DataProcessor(const std::vector<int>& data);
		void simpleAvarageFilter();
		void movingAvarageFilter(int windowSize);
		double overallAvarage();
		int findMinValue();
		int findMaxValue();
		const std::vector<double>& getProcessedData() const;
};

#endif // !DATAPROCESSOR_H
