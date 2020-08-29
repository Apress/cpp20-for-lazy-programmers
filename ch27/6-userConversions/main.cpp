// Driver program to test user-defined cast to const char*
//     -- from _C++20 for Lazy Programmers_

#include <iostream>
#include <fstream> //for ifstream
#include "string.h"

using namespace std;

int main ()
{
    // Testing that cast operator
    const String filename = "input.txt";

    ifstream myInputFile;

    //myInputFile.open(filename); //no -- no implicit cast
    myInputFile.open ((const char*) (filename));           //old-style explicit cast -- OK
    myInputFile.close();

    myInputFile.open (static_cast<const char*>(filename)); //modern explicit cast -- OK
    myInputFile.close();

    return 0;
}

