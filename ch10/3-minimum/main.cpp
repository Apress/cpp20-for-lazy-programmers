//Program to read in and print back out numbers 
//              -- from _C++20 for Lazy Programmers_

#include "SSDL.h"

double minimum   (const double elements[], int arraySize);

int main (int argc, char** argv)
{
    constexpr int MAX_NUMBERS = 10;
    double temperatures[] = { 32.6, 32.6, 32.7, 32.7, 32.7,
                              32.7, 32.7, 32.7, 32.7, 32.7 };

    //Print the numbers
    sout << "The lowest temp in the initializer list is " 
         << minimum   (temperatures, MAX_NUMBERS) << ".\n";
         //minimum: more versatile than lowestTemp; see Chapter 10

    sout << "\nHit any key to end.\n";

    SSDL_WaitKey ();

    return 0;
} 

double minimum(const double elements[], int arraySize)
//returns lowest entry in elements
{
    double result = elements[0];

    for (int i = 0; i < arraySize; ++i)
        if (elements[i] < result)
            result = elements[i];

    return result;
}
