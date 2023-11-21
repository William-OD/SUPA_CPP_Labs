/* William O'Donnell 
15/11/23
C++ SUPA Course
Assignment 1 -Main Tasks
*/

#include "AnalyseData.h"

#include <iostream> //Compiler directive to include the iostream standard file
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <tuple>


int main() 
{

/* Task 1: Print n lines of data in plain text to the terminal.*/
    //task1();

/* Task 2: Ask user to either print the a specified number of lines of data, or calculate the magnitude
             of each set of data points assuming the coordinates make a vector with (0, 0), displaying the result to the terminal.
    Additional Instructions: */

    /*Read in data from file and assign to vectors*/
    auto data = read_data("input2D_float.txt");
    std::vector<double> x_arr = std::get<0>(data);
    std::vector<double> y_arr = std::get<1>(data);

    /*Ask User to print x, y data or magnitudes*/
    std::cout << "Would you like to print the x, y data or the magnitudes? (data, m)" << std::endl;
    std::string choice;
    std::cin >> choice;
    if (choice == "data") {
        bool print_all = false; //Print all lines if true, else print num_lines
        std::cout << "How many lines of data would you like to print? (Maximum 25)" << std::endl;
        int num_lines;
        std::cin >> num_lines;
        print_vectors(x_arr, y_arr, num_lines, print_all);
    }
    else if (choice == "m") {
        //Calculate and print magnitudes
        auto data_mag = vectorMag(x_arr, y_arr);
        std::vector<double> mag_arr = std::get<2>(data_mag);
        int c = mag_arr.size();
        std::cout << "Magnitudes: " ;
        for (int i = 0; i < c; ++i) {
            std::cout << mag_arr[i] << ", ";
        }
        std::cout << std::endl;

    }
    else {
        std::cout << "Invalid input, please enter 'data' or 'm'" << std::endl;
    }


/* Task 3: Fit a straight line to the data using the least squares method and asess the goodness of this fit with a chi-squared test
   Additional Instructions: */

/*Calculate gradient and intercept of least squares fit*/
    auto Least_sq_result = least_squares(x_arr, y_arr);
    double grad_val = std::get<0>(Least_sq_result);
    double intercept_val = std::get<1>(Least_sq_result); 

    //Write equation to file and terminal
    std::string equation = "y = " + std::to_string(grad_val) + "*x + " + std::to_string(intercept_val);

    std::string file_out = "output_equation.txt";
    writeStringToFile(equation, file_out); //Write the linear best fit equation to a file
    std::cout << "Calculating the best fit line for all the data..." << std::endl;
    std::cout << "The equation of the best fit line is: " << equation << std::endl;

/* Calculate Chi-Squared Values*/


    return 0;
}