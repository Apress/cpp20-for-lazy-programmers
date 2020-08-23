//Program to read in and print back out numbers 
//              -- from _C++20 for Lazy Programmers_

#include "SSDL.h"

constexpr int MAX_NUMBERS = 10;
double lowestTemp(      double temperatures[MAX_NUMBERS]);

int main (int argc, char** argv)
{
    double temperatures[] = { 32.6, 32.6, 32.7, 32.7, 32.7,
                              32.7, 32.7, 32.7, 32.7, 32.7 };

    //Print the numbers
    sout << "The lowest temp in the initializer list is " 
         << lowestTemp(temperatures) << ".\n";

    sout << "\nHit any key to end.\n";

    SSDL_WaitKey ();

    return 0;
} 

double lowestTemp(double temperatures[MAX_NUMBERS])
//returns lowest entry in temperatures
{
    double result = temperatures[0];

    for (int i = 0; i < MAX_NUMBERS; ++i)
        if (temperatures[i] < result)
            result = temperatures[i];

    return result;
}
