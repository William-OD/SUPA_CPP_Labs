#include <iostream>
#include "FiniteFunctions.h"
#include <fstream>
#include <sstream>
// #include <algorithm>
// #include <cmath>

int main() {

 // Read in the mystery data
    std::ifstream MysteryData;
    MysteryData.open("Outputs/data/MysteryData10326.txt");
    if (!MysteryData.is_open()) {
        std::cout << "Error opening file" << std::endl;
        exit(1);
    }
    std::vector<double> testData;
    std::string line;
    double dataLine;
    while (std::getline(MysteryData, line)) {
        // Use an istringstream to parse the values separated by the given delimiter
        std::istringstream ss(line);
        std::string token;

        // Read the values separated by the specified delimiter
        std::getline(ss, token, ',');
        dataLine = std::stod(token); // Convert the string to the template type

        // Adding the values to the arrays
        testData.push_back(dataLine);
    }
    MysteryData.close();
    std::cout << "************************************" << std::endl;
    std::cout << "Read in " << testData.size() << " points." << std::endl;
    std::cout << "************************************" << std::endl;

    
// Test: Create a default FiniteFunction
    FiniteFunction defaultFunction;
    // Print information about the default function
    std::cout << "Default Function Info:" << std::endl;
    defaultFunction.printInfo();
    // Compute and print the integral
    std::cout << "Integral: " << defaultFunction.integral() << std::endl;

// Plot the default function
    defaultFunction.plotFunction();

// // Plot the data points
    defaultFunction.plotData(testData, 150, true);

    return 0;
}