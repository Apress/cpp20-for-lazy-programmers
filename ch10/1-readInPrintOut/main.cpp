//Program to read in and print back out numbers 
//              -- from _C++20 for Lazy Programmers_

#include "SSDL.h"

int main (int argc, char** argv)
{
    constexpr int MAX_NUMBERS = 10;

    sout << "Enter " << MAX_NUMBERS
         << " temperatures to make your report.\n\n"; 

    double temperatures [MAX_NUMBERS];

    //Get the numbers
    for (int i = 0; i < MAX_NUMBERS; ++i)
    {
        sout << "Enter the next temperature:  ";; 
        ssin >> temperatures[i];
    }

    //Print the numbers
    sout << "You entered ";
    for (int i = 0; i < MAX_NUMBERS; ++i)
        sout << temperatures[i] << ' ';

    sout << "\nHit any key to end.\n";

    SSDL_WaitKey ();

    return 0;
} 
