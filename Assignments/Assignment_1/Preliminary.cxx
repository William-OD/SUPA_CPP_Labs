/* William O'Donnell 
15/11/23
C++ SUPA Course
Assignment 1 - Preliminary Tasks
*/

#include <iostream> //Compiler directive to include the iostream standard file
#include <cmath> //Compiler directive to include the cmath standard file

//'using namespace std;' is often used to avoid having to type std:: before every command. However it is considered bad practice as it can cause naming conflicts in complex projects using different namespaces.

//TASK 3
double vectorMag2D(double x, double y){
  return std::sqrt(x * x + y * y);
}


int main() //Main function
{
//TASK 1
  std::cout << "Hello World!" << std::endl; 

  //std is the standard namespace, from the iostream header file
  //cout is the standard output stream, << is the insertion operator, endl is the end line manipulator These commands are pulled from the iostream header file
  
//TASK 2
  double x = 2.3;
  double y = 4.5;
  double mag= std::sqrt(x * x + y * y);
  std::cout << "The magnitude of the vector calculated manually is: " << mag << " ." << std::endl;

//TASK 3
  double a;
  double b;
  std::cout << "Please enter a value for x: " << std::endl;
  std::cin >> a;
  std::cout << "Please enter a value for y: " << std::endl;
  std::cin >> b;

  double funcmag = vectorMag2D(a, b);
  std::cout << "The magnitude of the vector calculated by the function is: " << funcmag << " ." << std::endl;

  return 0; //Return 0 to the operating system (standard for main files)
}