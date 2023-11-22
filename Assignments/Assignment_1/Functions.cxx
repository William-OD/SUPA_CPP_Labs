#include <iostream> //Compiler directive to include the iostream standard file
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <tuple>

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


   // Initialising the arrays
    std::vector<double> x_arr;
    std::vector<double> y_arr;

    // Iterating through the now read-in file to get the x and y values
    double x, y;
    for (int i = 0; i <= numLine; i++) {
        std::getline(myData, line);

        // Use an istringstream to parse the comma-separated values
        std::istringstream ss(line);
        std::string token;

        // Read the values separated by commas
        std::getline(ss, token, ','); 
        x = std::stod(token); // Convert the string to double

        std::getline(ss, token);
        y = std::stod(token); // Convert the string to double

        // Adding the values to the arrays
        x_arr.push_back(x);
        y_arr.push_back(y);


        std::cout << "Line "<< i << ": " << x << " " << y << std::endl;
    }

    myData.close();
}

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

std::tuple<std::vector<double>, std::vector<double>> read_data() {  //Initialising a tuple of vectors as the chosen data structure

     // Opening File
    std::ifstream myData;
    myData.open("input2D_float.txt");
    if(!myData.is_open())
    {
        std::cout << "Error opening file" << std::endl; // Error message if file cannot be opened
        exit(1);
    }

    // This Skips the Header line (in our case x,y) if its applicable
    std::string line;
    std::getline(myData, line); // Consume the header line if present


   // Initialising the arrays
    std::vector<double> x_arr;
    std::vector<double> y_arr;

    // Iterating through the now read-in file to get the x and y values
    double x, y;
    while (std::getline(myData, line)) {
        // Use an istringstream to parse the comma-separated values
        std::istringstream ss(line);
        std::string token;

        // Read the values separated by commas
        std::getline(ss, token, ','); 
        x = std::stod(token); // Convert the string to double

        std::getline(ss, token);
        y = std::stod(token); // Convert the string to double

        // Adding the values to the arrays
        x_arr.push_back(x);
        y_arr.push_back(y);

    }
    myData.close();

    return std::make_tuple(x_arr, y_arr); // Returning the tuple
}


// This is a shorter function to print out the vectors, but doesnt use the print_lines function. Confused as in wehich oen to sue as this seems to be simpler (fewer lines) and produce a more tailored output.
void print_vectors(const std::vector<double> & x_array, const std::vector<double> & y_array, std::size_t n, bool useFull_flag) { 
    if (useFull_flag == true) {
        int z = x_array.size();
        for (int i = 0; i < z; ++i) {
        std::cout << "Line " << i + 1 << ": " << x_array[i] << ", " << y_array[i]<< std::endl;
        }
    }
    else {
        if (n > x_array.size()) {
            std::cout << "Error: Number of lines to be printed is greater than the number of lines in the file. Printing the first 5 lines." << std::endl;
            for (int i = 0; i < 5; ++i) {
                std::cout << "Line " << i + 1 << ": " << x_array[i] << ", " << y_array[i]<< std::endl;
            }
        }
        else if (n < 1) {
            std::cout << "Error: Number of lines to be printed must be greater than 0. Printing the first 5 lines." << std::endl;
            for (int i = 0; i < 5; ++i) {
                std::cout << "Line " << i + 1 << ": " << x_array[i] << ", " << y_array[i]<< std::endl;
            }
        }
        else {
            for (int i = 0; i < n; ++i) {
                std::cout << "Line " << i + 1 << ": " << x_array[i] << ", " << y_array[i]<< std::endl;
            }
        }
    }
    std:: cout << " " << std::endl;
}


// void print_lines(const std::vector<double> & input_array, std::size_t n){
//     for (int i = 0; i < n; ++i) {
//         std::cout << input_array[i] << ", " ;
//     }
// }


// void print_vectors(const std::vector<double> & x_array, const std::vector<double> & y_array, std::size_t n, bool useFull_flag) {
//     if (useFull_flag == true) {
//         n = x_array.size();
//         std::cout << "X-Values : ";
//         print_lines(x_array, n);  
//         std::cout << std::endl;
//         std::cout << "Y-Values : ";
//         print_lines(y_array, n); 
//         std::cout << std::endl;
//     }
//     else {
//         if (n > x_array.size()) {
//             std::cout << "Error: Number of lines to be printed is greater than the number of lines in the file. Printing the first 5 lines." << std::endl;
//             std::cout << "X-Values : ";
//             print_lines(x_array, 5);  
//             std::cout << std::endl;
//             std::cout << "Y-Values : ";
//             print_lines(y_array, 5);
//             std::cout << std::endl;
//         }
//         else {
//             std::cout << "X-Values : ";
//             print_lines(x_array, n);  
//             std::cout << std::endl;
//             std::cout << "Y-Values : ";
//             print_lines(y_array, n);
//             std::cout << std::endl;
//         }
//     }
// }

std::tuple<std::vector<double>, std::vector<double>, std::vector<double>> vectorMag(const std::vector<double> & x_array, const std::vector<double> & y_array){
    std::vector<double> mag_array;
    int n = x_array.size();
    for (int i = 0; i < n; ++i) {
        mag_array.push_back(std::sqrt(x_array[i] * x_array[i] + y_array[i] * y_array[i]));
    }

    return std::make_tuple(x_array, y_array, mag_array);
}

std::tuple<double, double> leastsq_chisq(const std::vector<double> & x, const std::vector<double> & y) {
    double N = x.size();
    double sum_x_i = 0, sum_y_i = 0, sum_xx_i = 0, sum_xy_i = 0;
    for (int i = 0; i < N; ++i) {
        sum_x_i += x[i];
        sum_y_i += y[i];
        sum_xx_i += x[i]*x[i];
        sum_xy_i += x[i]*y[i];
    }
    
    double p = (N*sum_xy_i - sum_x_i*sum_y_i)/(N*sum_xx_i - sum_x_i*sum_x_i);
    double q = (sum_xx_i*sum_y_i - sum_xy_i*sum_x_i)/(N*sum_xx_i - sum_x_i*sum_x_i);

    return std::make_tuple(p, q);
}

void writeStringToFile(const std::string& content, const std::string& filename) {
    // Open a file for writing
    std::ofstream outFile(filename);

    // Check if the file is open
    if (!outFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return;
    }

    // Write the string to the file
    outFile << content;

    // Close the file
    outFile.close();

    //std::cout << "String has been written to the file: " << filename << std::endl;
}

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

    // std::cout << "Chi-Squared Sum: " << Chi_sq_sum << std::endl;
    // std::cout << "To calculate the reduced chi-squared value, we need to divide this by the number of data points (" << N << ") minus the number of degrees of freedom (2)." << std::endl;
    // std::cout << "Therefore the reduced chi-squared value is: "<< red_chi_sq << std::endl;

    return std::make_tuple(p, q, Chi_sq_sum, red_chi_sq);
}
