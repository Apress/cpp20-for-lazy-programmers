//Program to play around with some colors using constexpr functions
//       -- from _C++20 for Lazy Programmers_

#include "SSDL.h" 
#include "color.h"

using namespace Palette;

int main (int argc, char** argv)
{
     // Declare some SSDL_Colors, constexpr and not
    constexpr Color CREAM = COLORS[1];                   
    constexpr
    SSDL_Color SSDL_CREAM = color2SSDL_Color(CREAM);     // done at compile time

    const Color PUCE      = COLORS[0];
    SSDL_Color  SSDL_PUCE = color2SSDL_Color(PUCE);     
            // color2SSDL_Color is called at runtime because PUCE isn't constexpr

    // Call a constexpr function, and test static_assert
    constexpr Palette::Color ONYX = CREAM.complement(); // CREAM's opposite

    static_assert (ONYX.brightness_ < 0.10);            // onyx isn't bright
    static_assert (CREAM.brightness_ > 0.90,            // but cream is
                       "Isn't cream supposed to be bright?");

    // Display something
    SSDL_SetRenderDrawColor(SSDL_CREAM);
    SSDL_RenderClear       (SSDL_PUCE);
    sout << "Cream writing on a puce background.\n";

    SSDL_WaitKey ();    // Wait for user to hit any key

    return 0;
}
