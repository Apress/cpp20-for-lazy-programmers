// Driver program to test move constructor and move =
//      -- from _C++20 for Lazy Programmers_

#include <iostream>
#include "string.h"

using namespace std;

int main ()
{
    String str1 = "after", str2 = "noon";
    String newString;
    newString = str1 + str2;
        // Use debugger to verify it goes through && functions
		//  and copies correctly

    return 0;
}

