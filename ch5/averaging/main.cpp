//Program to average numbers
//		-- from _C++ for Lazy Programmers_

#include "SSDL.h"

int main (int argc, char** argv)
{
    constexpr int MAX_NUMBERS = 10;

    sout << "Enter " << MAX_NUMBERS << " numbers to get an average.\n";

    double total = 0.0;

    //Get the numbers
    for (int i = 0; i < MAX_NUMBERS; ++i)
    {
        double number;

        sout << "Enter the next number:  ";
        ssin >> number;

        total += number;
    }

    //Print the average
    double average = total / MAX_NUMBERS;
    sout << "The average is " << average << ".\n";

    sout << "Hit any key to end.\n";
    SSDL_WaitKey ();

    return 0;
}
