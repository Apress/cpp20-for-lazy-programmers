//Function for use w/ latitude, longitude
//       -- from _C++20 for Lazy Programmers_

#include <cmath>
#include "globalLoc.h"

#ifndef __cpp_inline_variables
const double PI = 3.14159;
#endif

// Function to square things should've been in cmath in my opinion
template <typename T> T sqr(const T& t) { return t * t; }

// Uses the Haversine formula to get distances
//  Alas, can't make this constexpr because of sin, cos, etc. Maybe in C++23
double distance(const GlobalLoc& x, const GlobalLoc& y) 
{
    constexpr double EARTH_RADIUS = 3958.8_mi;

    double a = sqr(sin((latitude(x) - latitude(y)) / 2.0)) // We're using first_ as latitude, second_ as longitude
        + cos(latitude(x)) * cos(latitude(y)) *
        sqr(sin((longitude(x) - longitude(y)) / 2.0));

    return EARTH_RADIUS * 2 * asin(sqrt(a));
}
