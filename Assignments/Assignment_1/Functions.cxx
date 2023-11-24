/* William O'Donnell 
24/11/23
C++ SUPA Course
Assignment 1 - Functions file
*/

#include <iostream> //Compiler directive to include the iostream standard file
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <tuple>

/*----------------------------------------------------------------------------------------------------
--------------Function: read_data() is used to read in 2-D data from text files-----------------------
--------------Inputs the filename and delimiter type. Outputs a tuple of two vectors.-----------------
------------------------------------------------------------------------------------------------------*/

std::tuple<std::vector<double>, std::vector<double>> read_data(const std::string & filename, char delimiter = ',') {
    std::ifstream myData;
    myData.open(filename);
    if (!myData.is_open()) {
        std::cout << "Error opening file" << std::endl;
        exit(1);
    }

    // Skip the Header line (in our case x,y) if it's applicable
    std::string line;
    std::getline(myData, line); // Consume the header line if present

    // Initializing the arrays
    std::vector<double> x_arr;
    std::vector<double> y_arr;

    // Iterating through the now read-in file to get the x and y values
    double x, y;
    while (std::getline(myData, line)) {
        // Use an istringstream to parse the values separated by the given delimiter
        std::istringstream ss(line);
        std::string token;

        // Read the values separated by the specified delimiter
        std::getline(ss, token, delimiter);
        x = std::stod(token); // Convert the string to the template type

        std::getline(ss, token);
        y = std::stod(token); // Convert the string to the template type

        // Adding the values to the arrays
        x_arr.push_back(x);
        y_arr.push_back(y);
    }
    myData.close();

    return std::make_tuple(x_arr, y_arr); // Returning the tuple
}


/*----------------------------------------------------------------------------------------------------
--------------Function: print_vectors() contains overloads to print out the requirements--------------
------------- for instruction 3, or an input of a 1-D vector and relevant header.---------------------
------------------------------------------------------------------------------------------------------*/

//Inputs the x and y data, number of lines to be printed, and a boolean to print all lines if true.
void print_vectors(const std::string &,const std::vector<double> &, const std::vector<double> &, std::size_t, bool);
void print_vectors(const std::string & header, const std::vector<double> & x_array, const std::vector<double> & y_array, std::size_t n) { 

    if (n > x_array.size()) {
        std::cout << "Error: Number of lines to be printed is greater than the number of lines in the file. Printing the first 5 lines." << std::endl;
        std::cout << "        " << header << std::endl;
        for (int i = 0; i < 5; ++i) {
            std::cout << "Line " << i + 1 << ": " << x_array[i] << ", " << y_array[i]<< std::endl;
        }
    }
    else if (n < 1) {
        std::cout << "Error: Number of lines to be printed must be greater than 0. Printing the first 5 lines." << std::endl;
        std::cout << "        " << header << std::endl;
        for (int i = 0; i < 5; ++i) {
            std::cout << "Line " << i + 1 << ": " << x_array[i] << ", " << y_array[i]<< std::endl;
        }
    }
    else {
        std::cout << "        " << header << std::endl;
        for (int i = 0; i < n; ++i) {
            std::cout << "Line " << i + 1 << ": (" << x_array[i] << ", " << y_array[i] << ")" << std::endl;
        }
    }
    std:: cout << " " << std::endl;
}
//Inputs a 1-D array and relevant header and prints to terminal.
void print_vectors(const std::string &, const std::vector<double> &);
void print_vectors(const std::string & header, const std::vector<double> & x_array) { 
    std::cout << "        " << header << std::endl;
    int n = x_array.size();
    for (int i = 0; i < n; ++i) {
        std::cout << "Line " << i + 1 << ": " << x_array[i] << std::endl;
    }
    std:: cout << " " << std::endl;
}


/*----------------------------------------------------------------------------------------------------
--------------Function: vectorMag() calculates the magnitude of a set of x,y pairs, ------------------
--------------returning a vector of the magnitude of each pair.---------------------------------------
------------------------------------------------------------------------------------------------------*/
std::vector<double> vectorMag(const std::vector<double> & x_array, const std::vector<double> & y_array){
    std::vector<double> mag_array;
    int n = x_array.size();
    for (int i = 0; i < n; ++i) {
        mag_array.push_back(std::sqrt(x_array[i] * x_array[i] + y_array[i] * y_array[i]));
    }
    return mag_array;
}


/*----------------------------------------------------------------------------------------------------
--------------Function: leastsq_chisq() calculates the least squares fit of a set of x,y pairs, ------
--------------then calculating the reduced chi-squared value of the data on the fit.------------------
------------------------------------------------------------------------------------------------------*/
std::tuple<double, double, double, double> leastsq_chisq(std::vector<double> x, std::vector<double> y, std::vector<double> x_err, std::vector<double> y_err) {
    int N = x.size();
    double sum_x_i = 0, sum_y_i = 0, sum_xx_i = 0, sum_xy_i = 0, Chi_sq_sum = 0;
    for (int i = 0; i < N; ++i) {
        sum_x_i += x[i];
        sum_y_i += y[i];
        sum_xx_i += x[i]*x[i];
        sum_xy_i += x[i]*y[i];
    }
    double p = (N*sum_xy_i - sum_x_i*sum_y_i)/(N*sum_xx_i - sum_x_i*sum_x_i);
    double q = (sum_xx_i*sum_y_i - sum_xy_i*sum_x_i)/(N*sum_xx_i - sum_x_i*sum_x_i);

    for (int i = 0; i < N; ++i) {
        double expected_y = (x[i]*p + q); //Expected y values calculated from y = mx+c
        double num = (y[i] - expected_y)*(y[i] - expected_y); //Numerator of Chi-squared equation
        double den =  x_err[i]*p*x_err[i]*p + y_err[i]*y_err[i]; //Total squared error in y. [Y_expected_err = m*x_err + c_err = m*x_err]
        double Chi_sq = num/den;
        Chi_sq_sum += Chi_sq;
    }
    double red_chi_sq = Chi_sq_sum/(N-2);

    return std::make_tuple(p, q, Chi_sq_sum, red_chi_sq);
}

/*----------------------------------------------------------------------------------------------------
--------------Function: XpowY() calculates x^y of the x,y data pairs using a recursive function.------
------------------------------------------------------------------------------------------------------*/
void XpowY(const std::vector<double> & x_arr, const std::vector<double> & y_arr, std::vector<double> & xpowy_arr, std::size_t i) {
    if (i == x_arr.size()) {    //Will end the recursive function when the index is equal to the size of the array
        return;
    }
    if (i < 0) {    //Will end the recursive function if the index is less than 0
        return;
    }
    double y_arr_rnd = static_cast<int>(std::round(y_arr[i]));
    int y_arr_int = static_cast<int>(y_arr_rnd);
    double xpowy = std::exp(y_arr_int * std::log(x_arr[i]));
    xpowy_arr.push_back(xpowy);
    // Recursively call the function for the next index
    XpowY(x_arr, y_arr, xpowy_arr, i + 1);
}

/*----------------------------------------------------------------------------------------------------
--------------Function: print_vectors() contains overloads to print out the a-------------------------
--------------1-D vector and a header, or just a 1-D vector.------------------------------------------
----------------------------------------------------------------------------------------------------*/
//Writing one 1-D Vector to file
void writeToFile(const std::string & filename, const std::string & , const std::vector<double> &);
void writeToFile(const std::string & filename, const std::string & header, const std::vector<double> & vector_1){
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return;
    }
    outFile << header << std::endl;
    int n = vector_1.size();
      for (int i=0; i<n; i++) {
         outFile << vector_1[i] << std::endl;
      }
    std::cout << "File written to " << filename << std::endl;
    outFile.close();
}
//Writing two 1-D Vectors to file, with the number of lines specified by the user
void writeToFile(const std::string & filename, const std::string & , const std::vector<double> &, const std::vector<double> &, std::size_t);
void writeToFile(const std::string & filename, const std::string & header, const std::vector<double> & vector_1, const std::vector<double> & vector_2, std::size_t n){
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return;
    }
    else {
        outFile << header << std::endl;
        if (n > vector_1.size()) {
            std::cout << "Error: Number of lines to be printed is greater than the number of lines in the file. Printing the first 5 lines." << std::endl;
            for (int i=0; i<n; i++) {
                outFile << vector_1[i] << vector_2[i] << std::endl;
            }
            std::cout << " " << std::endl;
            std::cout << "File written to " << filename << std::endl;
        }
        else if (n < 1) {
            std::cout << "Error: Number of lines to be printed must be greater than 0. Printing the first 5 lines." << std::endl;
            for (int i=0; i<n; i++) {
            outFile << vector_1[i] << vector_2[i] << std::endl;
            }
            std::cout << " " << std::endl;
            std::cout << "File written to " << filename << std::endl;
        }
        else {
            for (int i=0; i<n; i++) {
            outFile << vector_1[i] << vector_2[i] << std::endl;
            }
            std::cout << " " << std::endl;
            std::cout << "File written to " << filename << std::endl;
        }
        std:: cout << " " << std::endl;
        outFile.close();
    }
}
//Write the best fit function, and chi-square values.
void writeToFile(const std::string & filename, const std::string & );
void writeToFile(const std::string & filename, const std::string & header){
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return;
    }
    outFile << header << std::endl;
    std::cout << "File written to " << filename << std::endl;
    outFile.close();
}