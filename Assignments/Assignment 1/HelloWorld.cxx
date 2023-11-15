/* William O'Donnell 
15/11/23
C++ SUPA Course
*/

#include <iostream> //Compiler directive to include the iostream standard file

//'using namespace std;' is often used to avoid having to type std:: before every command. However it is considered bad practice as it can cause naming conflicts in complex projects using different namespaces.

int main() //Main function
{
  std::cout << "Hello World!" << std::endl; 
  //std is the standard namespace, from the iostream header file
  //cout is the standard output stream, << is the insertion operator, endl is the end line manipulator These commands are pulled from the iostream header file
  return 0; //Return 0 to the operating system (standard for main files)
}