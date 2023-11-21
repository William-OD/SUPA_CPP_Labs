/* William O'Donnell 
15/11/23
C++ SUPA Course
Assignment 1 -Main Tasks
*/

#include "AnalyseData.h"

int main() 
{
    //task1();

    auto data = read_data();
    std::vector<double> x_arr = std::get<0>(data);
    std::vector<double> y_arr = std::get<1>(data);
    
    bool print_all = true; //Print all lines if true, else print num_lines
    int num_lines = 29; //Number of lines to be printed if print_all = false
    print_vectors(x_arr, y_arr, num_lines, print_all);

    auto data_mag = vectorMag(x_arr, y_arr);
    std::vector<double> mag_arr = std::get<2>(data_mag);
    int c = mag_arr.size();
    std::cout << "Magnitudes: " ;
    for (int i = 0; i < c; ++i) {
        std::cout << mag_arr[i] << ", ";
    }
    std::cout << std::endl;

    return 0;
}