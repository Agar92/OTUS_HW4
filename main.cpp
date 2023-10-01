/*! \file main.cpp*/

/*! \mainpage My first C++ project using Doxygen for documenting code
 *
 * \section intro_sec my 1st cpp project utilizing Doxygen
 */
#include <iostream>
#include <version.h>

int var;/*!< Detailed description after the member */


using std::cout, std::endl;/*!< using declarations */



/*!
* main function
*/
int main()/*!< Detailed description after the member */
{
    cout<<PROJECT_NAME<<endl;
    cout<<PROJECT_VERSION<<endl;
    cout<<PROJECT_VERSION_MAJOR<<endl;
    cout<<PROJECT_VERSION_MINOR<<endl;
    cout<<PROJECT_VERSION_PATCH<<endl;

    return 0;
}
