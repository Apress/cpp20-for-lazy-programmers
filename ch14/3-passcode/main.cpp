//Program to generate a random passcode of digits
//		-- from _C++20 for Lazy Programmers_

#include <iostream>
#include <cstdlib> //for srand, rand
#include <ctime>   //for time

using namespace std;

int main ()
{
    srand ((unsigned int) time(nullptr));// start random # generator

 
    int codeLength;                      // get code length
    cout << "I'll make your secret passcode. How long should it be? ";
    cin  >> codeLength;

    int* passcode = new int[codeLength]; // allocate array
    
    for (int i = 0; i <codeLength; ++i)  // generate passcode
        passcode[i] = rand () % 10;      // each entry is a digit

    cout << "Here it is:\n";             // print passcode
    for (int i = 0; i < codeLength; ++i)
        cout << passcode[i];
    cout << '\n';
    cout << "But I guess it's not secret any more!\n";
    
    delete [] passcode;                  // deallocate array

    return 0;
}
