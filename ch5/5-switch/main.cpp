// Program to identify planetary classification
//       -- from _C++20 for Lazy Programmers_

#include "SSDL.h"

int main(int argc, char** argv)
{
    char planetaryClassification;

    sout << "Enter the class of a planet: "; 
    ssin >> planetaryClassification;

    switch (planetaryClassification)
    {
    case 'J': sout << "Gas giant";       break;
    case 'M': sout << "Earthlike world"; break;
    case 'Y': sout << "'Demon' planet";  break;
    case 'D': sout << "Airless rock";    break;
    case 'L': sout << "Marginal";        break;
        // ...
    default:  sout << "That's not a valid planetary classification.\n";
    sout << "Better watch some more Star Trek!";
    }

    sout << "\n\nHit any key to continue.\n";
    SSDL_WaitKey();

    return 0;
}
