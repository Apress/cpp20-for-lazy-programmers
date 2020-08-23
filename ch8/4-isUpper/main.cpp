//Is a character upper case, or lower?
//		-- from _C++20 for Lazy Programmers_

#include <ctime>    //for time function
#include <cstdlib>  //for srand, rand
#include "SSDL.h"

constexpr int SIDES_PER_DIE = 6;

bool isupper (char ch); //returns whether ch is an upper-case letter

int main (int argc, char** argv)
{
    char letter = 'A';
	if (isupper(letter)) sout << letter << " is upper case.\n";
	else                 sout << letter << " is lower case.\n";
	
	letter = 'a';
	if (isupper(letter)) sout << letter << " is upper case.\n";
	else                 sout << letter << " is lower case.\n";
	
    sout << "Hit a key to end.\n";
    SSDL_WaitKey();
    
    return 0;
}

bool isupper (char ch) //returns whether ch is an upper-case letter
{
    bool result;

    if (ch >= 'A' && ch <= 'Z')
        result = true;
    else
        result = false;

    return result;
}

