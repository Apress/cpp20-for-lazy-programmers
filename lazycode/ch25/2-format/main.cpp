// Program to print temp, pressure for some familiar planets
//      -- from _C++ for Lazy Programmers_

#define FMT_HEADER_ONLY // Use this for now; when compiler supports
                        //  format, should be able to skip this

#include <iostream>
#include <fmt/format.h> // For now, we're using an imported format
                        //   library, {fmt}, stored in external/ .
                        // When our compilers support format strings, 
                        //   this line should say just #include <format>

using namespace fmt::v6;// Use this for now; when compiler supports
                        //   format, format should be in namespace std
                        //   so omit this line
using namespace std;

int main()
{
    // planetary temperature and pressure
    constexpr double     VENUS_TEMP =   464;    // celsius
    constexpr double     EARTH_TEMP =    15;
    constexpr double      MARS_TEMP =   -62;

    constexpr double VENUS_PRESSURE = 92000;    // millibars
    constexpr double EARTH_PRESSURE =  1000;
    constexpr double  MARS_PRESSURE =     1;

    // Print a 3-column table
    // Left column is 7 chars wide; char* -> left-justified by default
    // Other columns are 11 chars wide, right-justified
	
    // Headers
    cout << format("{:7} {:>11}  {:>11}\n",
                   "Planet", "Temperature", "Pressure");
    cout << format("{:7} {:>11}  {:>11}\n\n",
                   "", "(celsius)", "(millibars)");

    // Data
    cout << format("{:7} {:11.1f}  {:11.0}\n",
                   "Venus", VENUS_TEMP, VENUS_PRESSURE);
    cout << format("{:7} {:11.1f}  {:11.0}\n",
                   "Earth", EARTH_TEMP, EARTH_PRESSURE);
    cout << format("{:7} {:11.1f}  {:11.0}\n",
                   "Mars",  MARS_TEMP,  MARS_PRESSURE);

    cout << "\n...I think I'll just stay home.\n\n";

    return 0;
}