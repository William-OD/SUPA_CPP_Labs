/* William O'Donnell 
15/11/23
C++ SUPA Course
Assignment 1 - Preliminary Tasks
*/

#include <iostream> //Compiler directive to include the iostream standard file
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

double vectorMag2D(double x, double y){
  return std::sqrt(x * x + y * y);
}

void task1(){
     // Opening File
    std::ifstream myData;
    myData.open("input2D_float.txt");
    if(!myData.is_open()){
        std::cout << "Error opening file" << std::endl;
        exit(1);
    }

    // Asking user to prompt number of lines to be read
    int numLine;
    std::cout << "Enter the number of lines from 'inpout2D_float.txt' to be read: " << std::endl;
    std::cin >> numLine;
    if (numLine < 0){
        std::cout << "Error: Number of lines must be positive" << std::endl;
        exit(1);
    }
    std::cout << " "<< std::endl;
    std::cout << "The first " << numLine << " lines of the file are: " << std::endl;


    // This Skips the Header line (in our case x,y) if its applicable
    std::string line;
    std::getline(myData, line); // Consume the header line if present


    // Reading the data

    double x_arr[] = {};
    double y_arr[] = {};

    double x, y;
    for (int i = 0; i <= numLine; i++) {
        std::getline(myData, line);

        // Use an istringstream to parse the comma-separated values
        std::istringstream ss(line);
        std::string token;

        // Read the values separated by commas
        std::getline(ss, token, ','); 
        x = std::stod(token); // Convert the string to double

        std::getline(ss, token, ',');
        y = std::stod(token); // Convert the string to double

        // x_arr[i] = x;
        // y_arr[i] = y;

        std::cout << "Line "<< i << ": " << x << " " << y << std::endl;
    }

    myData.close();
}


int main(){
    task1();
    return 0;
}