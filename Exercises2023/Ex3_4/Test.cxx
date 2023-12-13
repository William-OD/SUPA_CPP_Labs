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
    

// Test: Create a default FiniteFunction
    FiniteFunction defaultFunction;
    defaultFunction.printInfo();
    defaultFunction.plotFunction();
    defaultFunction.plotData(testData, 100, true);
    defaultFunction.metropolisSampling(10000, 1.2);


// Normal Distribution Test
    NormalFunction normal;
    normal.setMean(-3.0);
    normal.setStdDev(2.0);
    normal.printInfo();
    normal.plotFunction();
    normal.plotData(testData, 100, true);   
    normal.metropolisSampling(10000, 1.2);


// Cauchy-Lorentz Distribution Test
    CauchyLorentzFunction cauchy;
    cauchy.setX0(-3.0);
    cauchy.setGamma(2.0);
    cauchy.printInfo();
    cauchy.plotFunction();
    cauchy.plotData(testData, 100, true);
    cauchy.metropolisSampling(10000, 1.2);

// Negative Crystal Ball Distribution Test
    NegativeCrystalBallFunction ncb;
    ncb.setMean(-3.0);
    ncb.setStdDev(2.0);
    ncb.setAlpha(1.25);
    ncb.setN(1.5);
    ncb.printInfo();
    ncb.plotFunction();
    ncb.plotData(testData, 100, true);
    ncb.metropolisSampling(10000, 1.2);
    
return 0;
}