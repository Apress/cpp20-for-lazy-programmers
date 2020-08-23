//Program to produce an ALL CAPS version of a file
//      -- from _C++20 for Lazy Programmers_

#include <iostream>
#include <cctype>             // for toupper

using namespace std;

int main ()
{
    while (cin)               // for each char in file
    {
        char ch = cin.get();  //   read in char
        ch = toupper (ch);    //   capitalize
        if (cin) cout << ch;  //   cin still OK? Then print
    }

    return 0;
}
