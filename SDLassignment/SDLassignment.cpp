#include <iostream>
#include "Sensor.h"
#include "DataProcessor.h"
#include <fstream>
#include <ctime>
#include <sstream>


int main()
{
    int dataPoints=0 , rangeMin =0, rangeMax=0, filterType=0, windowsize = 0;

    //user inputs
    while (dataPoints <= 0) {
        std::cout << "Number of data points (must be greater than 0): ";
        std::cin >> dataPoints;

        if (dataPoints <= 0) {
            std::cout << "Invalid input! Please enter a positive number of data points.\n";
        }
    }
    std::cout << "Minimum value for data range :";
    std::cin >> rangeMin;
    std::cout << "Maximum value for data range :";
    std::cin >> rangeMax;

    while (filterType != 1 && filterType != 2) {
        std::cout << "Choose the filter type,\n";
        std::cout << "1 - Simple average filter\n";
        std::cout << "2 - Moving average filter\n";
        std::cin >> filterType;

        if (std::cin.fail() || (filterType != 1 && filterType != 2)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid filter type! Please choose 1 or 2.\n";
        }
    }

   
    if (filterType == 2) {
        while (windowsize <= 0 || windowsize > dataPoints) {
            std::cout << "Subset size for Moving Average (1 to " << dataPoints << "): ";
            std::cin >> windowsize;

            if (std::cin.fail() || windowsize <= 0 || windowsize > dataPoints) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid window size! Please enter a value between 1 and " << dataPoints << ".\n";
            }
        }
    }
    Sensor sensor(rangeMin, rangeMax);
    std::vector<int>data = sensor.collectDataPoint(dataPoints);


    DataProcessor processor(data);

    if (filterType == 1 )
    {
        processor.simpleAvarageFilter();
    }
    else if (filterType == 2) {
        processor.movingAvarageFilter(windowsize);
    }
    else
    {
        throw std::runtime_error("Error: Invalid filter type selected.");
        return 1;
    }
    //rawdata
    double rawAverage = processor.overallAvarage();
    int rawMin = processor.findMinValue();
    int rawMax = processor.findMaxValue();
    //processed data
    double processedSum=0;
    int processedCount = processor.getProcessedData().size();
    double processedMin = processedCount > 0 ? processor.getProcessedData()[0] : 0;
    double processedMax = processedCount > 0 ? processor.getProcessedData()[0] : 0;

    for (double val : processor.getProcessedData())
    {
        processedSum += val;
        if (val < processedMin) processedMin = val;
        if (val > processedMax) processedMax = val;
    }
    double processedAverage = processedCount > 0 ? processedSum / processedCount : 0;

    //outputs
    std::cout << "\n- - Results - -";
    std::cout << "\nRaw Data : ";
    for (int val : data )
    {
        std::cout << val << " ";
    }
    std::cout << "\n";
    std::cout << "Raw Data - Minimum Value : " << rawMin << "\n";
    std::cout << "Raw Data - Maximum Value : " << rawMax << "\n";
    std::cout << "Raw Data - Average :  " << rawAverage << "\n";

    std::cout << "\nProcessed Data: ";
    for (double val : processor.getProcessedData())
    {
        std::cout << val << " ";
    }
    std::cout << "\n";
    std::cout << "Processed Data - Minimum Value : " << processedMin << "\n";
    std::cout << "Processed - Maximum Value : " << processedMax << "\n";
    std::cout << "Processed - Average :  " << processedAverage << "\n";

    //create file for outputs
    std::time_t now = std::time(0);
    std::tm localTime;
    localtime_s(&localTime, &now);

    std::ostringstream fileNameStream;
    fileNameStream << "results_"
        << (1900 + localTime.tm_year) << "_"
        << (1 + localTime.tm_mon) << "_"
        << localTime.tm_mday << "_"
        << localTime.tm_hour << "_"
        << localTime.tm_min << "_"
        << localTime.tm_sec << ".txt";
    std::string fileName = fileNameStream.str();
    std::ofstream outputFile(fileName);

    if (outputFile.is_open())
    {
        outputFile << "\n- - Results - -";
        outputFile << "\nRaw Data : ";
        for (int val : data)
        {
            outputFile << val << " ";
        }
        outputFile << "\n";
        outputFile << "Raw Data - Minimum Value : " << rawMin << "\n";
        outputFile << "Raw Data - Maximum Value : " << rawMax << "\n";
        outputFile << "Raw Data - Average :  " << rawAverage << "\n";

        outputFile << "\nProcessed Data: ";
        for (double val : processor.getProcessedData())
        {
            outputFile << val << " ";
        }
        outputFile << "\n";
        outputFile << "Processed Data - Minimum Value : " << processedMin << "\n";
        outputFile << "Processed - Maximum Value : " << processedMax << "\n";
        outputFile << "Processed - Average :  " << processedAverage << "\n";

        outputFile.close();
        std::cout << "Result file created\n";
    }
    else {
        std::cerr << "error occurred while creating the file. \n";
    }
    std::cout << "File Name : " << fileName << std::endl;

    return 0;
}

