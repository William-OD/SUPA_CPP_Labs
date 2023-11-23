/* William O'Donnell 
15/11/23
C++ SUPA Course
Assignment 1 -Main Tasks
*/

#include "AnalyseData.h"

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
    std::cout << " "<< std::endl;
    if (choice == "data") {
        bool print_all = false; //Print all lines if true, else print num_lines
        std::cout << "How many lines of data would you like to print? (Maximum "<< x_arr.size() <<")" << std::endl;
        int num_lines;
        std::cin >> num_lines;
        std::cout << " " << std::endl;
        std::string header_data = "(x, y)";
        print_vectors(header_data, x_arr, y_arr, num_lines, print_all);
    }
    else if (choice == "m") {
        //Calculate and print magnitudes
        std::vector<double> mag_arr = vectorMag(x_arr, y_arr);
        int c = mag_arr.size();
        std::string fname_mag = "output_magnitudes.txt";
        std::string header_mag = "Magnitudes";
        print_vectors(header_mag, mag_arr);
        writeToFile("output_Magnitudes.txt", header_mag, mag_arr);

    }
    else {   
        std::cout << "Invalid input, please enter 'data' or 'm'" << std::endl;
    }


/* Task 3: Fit a straight line to the data using the least squares method and asess the goodness of this fit with a chi-squared test
   Additional Instructions: */

/*Calculate gradient and intercept of least squares fit*/


/* Calculate Chi-Squared Values*/

    auto err_data = read_data("error2D_float.txt");
    std::vector<double> x_arr_err = std::get<0>(err_data);
    std::vector<double> y_arr_err = std::get<1>(err_data);
    auto lsq_chisq_result = leastsq_chisq(x_arr, y_arr, x_arr_err, y_arr_err);
    double grad_val = std::get<0>(lsq_chisq_result);
    double intercept_val = std::get<1>(lsq_chisq_result); 
    double chi_sq = std::get<2>(lsq_chisq_result);
    double red_chi_sq = std::get<3>(lsq_chisq_result);

    std::string fit_info = "The best fit (straight) line to the data is y = " + std::to_string(grad_val) + "*x + " + std::to_string(intercept_val) + "\n" + "Chi-Squared: " + std::to_string(chi_sq) + "\n" + "Reduced Chi-Squared: " + std::to_string(red_chi_sq);
    std::string file_out = "output_Data.txt";
    std::cout << fit_info << std::endl;
    std::cout << " "<< std::endl;
    writeToFile("output_Fit.txt", fit_info);


/* Calculate x to the power of y*/
    std::vector<double> xpowy_arr;
    XpowY(x_arr, y_arr, xpowy_arr, 0);
    std::string header_xpowy = "x^y";
    print_vectors(header_xpowy, xpowy_arr);
    writeToFile("output_XpowY.txt", header_xpowy, xpowy_arr);

    return 0;
}