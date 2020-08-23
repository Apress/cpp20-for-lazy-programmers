// Program to tell if two letters are in alphabetical order
// 		-- from _C++ for Lazy Programmers_

#include "SSDL.h"

int main(int argc, char** argv)
{
    char char1, char2;

    sout << "Give me a letter: "; ssin >> char1;
    sout << "Give me another: ";  ssin >> char2;

    if (char1 < char2)
        sout << "You gave me two characters in order.\n";
    else if (char1 > char2)
        sout << "They are in reverse order.\n";
    else
        sout << "They are identical.\n";

    SSDL_WaitKey();

    return 0;
}
