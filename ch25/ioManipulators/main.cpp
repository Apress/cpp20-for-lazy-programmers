//Program to print temp, pressure for Venus and Earth
//      -- from _C++ for Lazy Programmers_

#include <iostream>
#include <iomanip>  // for setw and setprecision

using namespace std;

int main ()
{
    // constexprants related to spacing on the page
    constexpr int      PLANET_SPACE =     7;
    constexpr int        TEMP_SPACE =    12;
    constexpr int    PRESSURE_SPACE =    13;

    // planetary temperature and pressure
    constexpr double     VENUS_TEMP =   464;
    constexpr double VENUS_PRESSURE = 90000;
    constexpr double     EARTH_TEMP =    15;
    constexpr double EARTH_PRESSURE =  1000;
    constexpr double      MARS_TEMP =   -62;
    constexpr double  MARS_PRESSURE =     1;

    // Use fixed format for floats -- no scientific
    cout << fixed;

    //Print the headers
    //  First column is justified left, others right
    cout    << left
            << setw (PLANET_SPACE)  << "Planet" 
            << right
            << setw (TEMP_SPACE  )  << "Temperature"
            << setw (PRESSURE_SPACE)<< "Pressure"   << endl;
    cout    << left
            << setw (PLANET_SPACE)  << " " 
            << right 
            << setw (TEMP_SPACE  )  << "(celsius)"
            << setw (PRESSURE_SPACE)<< "(millibars)" << endl;
    cout    << endl;

    // Print the data
    //  Column 1 has 1 decimal place precision; Col 2 has none
    cout    << left
            << setw (PLANET_SPACE)  << "Venus" 
            << right << setprecision (1)
            << setw (TEMP_SPACE  )  << VENUS_TEMP
            << setprecision (0)
            << setw (PRESSURE_SPACE)<< VENUS_PRESSURE << endl;
    cout    << left
            << setw (PLANET_SPACE)  << "Earth" 
            << right << setprecision (1)
            << setw (TEMP_SPACE  )  << EARTH_TEMP
            << setprecision (0)
            << setw (PRESSURE_SPACE)<< EARTH_PRESSURE << endl;
    cout    << left
            << setw (PLANET_SPACE)  << "Mars"
            << right << setprecision (1)
            << setw (TEMP_SPACE)    << MARS_TEMP
            << setprecision (0)
            << setw (PRESSURE_SPACE)<< MARS_PRESSURE  << endl;

    cout    << "\n...I think I'll just stay home.\n\n";

    return 0;
}
