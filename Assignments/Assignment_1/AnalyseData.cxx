/* William O'Donnell 
24/11/23
C++ SUPA Course
Assignment 1 - Main file
*/

#include "AnalyseData.h"

int main() 
{   
    int i;
    bool go = true;
    auto data = read_data("input2D_float.txt");
    std::vector<double> x_arr = std::get<0>(data);
    std::vector<double> y_arr = std::get<1>(data);
    
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "Welcome to the data analysis program!" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    std::cout << " "<< std::endl;
    std::cout << "The x, y data has been read in from the file input2D_float.txt" << std::endl;
    std::cout << " "<< std::endl;
    std::cout << "Please choose an option to what program you would like to run." << std::endl;
    std::cout << " "<< std::endl;
    std::cout << "1. Save and display a specified number of lines of data." << std::endl;
    std::cout << "2. Calculate the magnitude of each set of data points assuming the coordinates make a vector with (0, 0), saving to a text file and displaying to the terminal." << std::endl;
    std::cout << "3. Fit a straight line to the data using the least squares method and asess the goodness of this fit with a chi-squared test, saving to a text file and displaying to the terminal." << std::endl;
    std::cout << "4. Calculate x to the power of y, saving to a text file and displaying to the terminal." << std::endl;
    std::cout << "5. Exit program." << std::endl;
    std::cout << " "<< std::endl;
  

        while(go){
            std::cout << "--------------------------------------------------------------" << std::endl;
            std::cout << "Which task would you like to run? (1, 2, 3, 4)    [5 to exit]." << std::endl;
            std::cout << "You chose option: ";

            // Check if the input is an integer
            if (!(std::cin >> i)) {//if not an integer:
                std::cin.clear(); // Clear the error state
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
                std::cout << "Invalid input. Please enter a valid option (1, 2, 3, 4, or 5)." << std::endl;
                continue; // Continue to the next iteration of the loop
            }
            switch (i) {
                case 1:{
                        /* Task 2: Ask user to either print a specified number of lines of data, displaying the result to the terminal.
                    Additional Instructions: */
                    bool print_all = false; //Print all lines if true, else print num_lines
                    std::cout << "How many lines of data would you like to print? (Maximum "<< x_arr.size() <<")" << std::endl;
                    int num_lines;
                    std::cin >> num_lines;
                    std::cout << " " << std::endl;
                    std::string header_data = "(x, y)";
                    print_vectors(header_data, x_arr, y_arr, num_lines);
                    writeToFile("output_Data.txt", header_data, x_arr, y_arr, num_lines);
                    break;
                }

                case 2:{
                    /* Task 2:  calculate the magnitude of each set of data points assuming the coordinates make a vector with (0, 0), displaying the result to the terminal.
                    Additional Instructions: */
                    std::vector<double> mag_arr = vectorMag(x_arr, y_arr);
                    int c = mag_arr.size();
                    std::string fname_mag = "output_magnitudes.txt";
                    std::string header_mag = "Magnitudes";
                    print_vectors(header_mag, mag_arr);
                    writeToFile("output_Magnitudes.txt", header_mag, mag_arr);
                    break;
                }

                case 3:{
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
                    break;
                }

                case 4:{
                    /* Task 4: Calculate x to the power of y*/
                    std::vector<double> xpowy_arr;
                    XpowY(x_arr, y_arr, xpowy_arr);
                    std::string header_xpowy = "x^y";
                    print_vectors(header_xpowy, xpowy_arr);
                    writeToFile("output_XpowY.txt", header_xpowy, xpowy_arr);
                    break;
                }

                case 5:{
                    std::cout << "Exiting program....." << std::endl;
                    go = false;
                    break;
                }

                default:{
                    std::cout << "Invalid input, please enter an option 1, 2, 3, or 4. Press 5 to exit." << std::endl;
                    break;
                }
            }
        }
    return 0;
}