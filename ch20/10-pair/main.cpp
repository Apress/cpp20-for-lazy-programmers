// A little program to use std::pair
//      -- from _C++20 for Lazy Programmers_

#include <iostream>
#include <utility> 
#include <string>

using namespace std;

int main ()
{
    pair p (1, "C++20 for Lazy Programmers");
    cout << "The number " << p.first << " C++ text EVER is " << p.second << "!\n";

    return 0;
}

