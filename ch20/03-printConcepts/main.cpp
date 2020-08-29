// Printing concepts
//      -- from _C++20 for Lazy Programmers_

#ifndef __cpp_concepts
#warning "This compiler does not support concepts."
#endif

#include <iostream>
#include <concepts>

using namespace std;

class A {};
class B : public A {};

int main ()
{
    cout << "Is int same as double?   " << same_as<int, double>
         << "\nIs B derived from A?   " << derived_from<B, A>
         << "\nIs char8_t integral?   " << integral<char8_t>
         << "\nIs double floating-pt? " << floating_point<double> 
         << '\n';

    return 0;
}