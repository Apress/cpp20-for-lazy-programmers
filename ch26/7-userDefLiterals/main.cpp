//Program to use user-defined literals
//       -- from _C++20 for Lazy Programmers_

#include <iostream>
#include <cmath>

using namespace std;

constexpr double PI = 3.14159;

// "Literal" operators

constexpr 
long double operator"" _deg (long double degrees)        
{ 
    return degrees * PI/180; 
}
constexpr 
long double operator"" _deg (unsigned long long degrees) 
{ 
    return degrees * PI/180; 
}

constexpr 
long double operator"" _m   (long double   m) { return m;            }
                                                   // 1 m = 1 m (duh)
constexpr 
long double operator"" _mi  (long double  mi) { return mi * 1609.344;}
                                                   // 1 mi = 1609.344 m
int main ()
{
    cout << "The speed of light is 186,000 miles per second.\n";
    cout << "In metric, that's ";
    cout <<     186'000.0_mi    << " meters per second --\n"
         << "   should be about " << 300'000'000.0_m  << ".\n";
    
    cout << "Oh, and sin (30 deg) is about 0.5: " 
         << sin (30_deg) << endl;

    return 0;
}
