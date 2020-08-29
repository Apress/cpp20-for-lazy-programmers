// Useful functions, plus GlobalLoc struct, for use w/ latitude, longitude
//       -- from _C++20 for Lazy Programmers_

#ifndef GLOBALLOC_H
#define GLOBALLOC_H

#include <utility> // for pair

#ifdef __cpp_inline_variables
inline constexpr double PI = 3.14159; // declare it inline if supported
#else
extern const double PI;               // else old style
#endif
               // Or you can get it from #include <numbers>
               //  but that's imperfectly supported too at time of writing

// User-defined literal operators
constexpr
long double operator"" _deg (unsigned long long deg) 
{
    return deg * PI / 180;
}
constexpr
long double operator"" _mi (long double  mi)
{
    return mi * 1609.344;    // 1 mi = 1609.344 m
}

// GlobalLocation

using GlobalLoc = std::pair<long double, long double>;
       // First_ is latitude, second_ is longitude. So I'll make
       //  a couple of inline functions to help with clarity
       // Easier than creating my own class
inline long double latitude (const GlobalLoc& foo) { return foo.first; }
inline long double longitude(const GlobalLoc& foo) { return foo.second; }

double distance(const GlobalLoc& x, const GlobalLoc& y);
#endif //GLOBALLOC_H
