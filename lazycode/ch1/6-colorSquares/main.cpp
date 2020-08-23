// Displays boxes of colors
//       -- from _C++20 for Lazy Programmers_

#include "SSDL.h"

int main (int argc, char** argv)
{
    SSDL_SetWindowTitle ("Two squares in different colors");

    // We'll use 2 new colors, plus GREEN and WHITE...
    const SSDL_Color MAHOGANY   = SSDL_CreateColor (192,  64,   0);
    const SSDL_Color DARK_GREY  = SSDL_CreateColor (100, 100, 100);

    // Make a dark grey background
    SSDL_RenderClear(DARK_GREY);

    // We'll have two squares
    SSDL_SetRenderDrawColor     (GREEN);    //  First square
    SSDL_RenderFillRect         (  0,   0, 100, 100);
    SSDL_SetRenderDrawColor     (MAHOGANY); //  Second
    SSDL_RenderFillRect         (100,   0, 100, 100);

    // Program's end.
    // Must restore color to white, or we'll get mahogany text!
    SSDL_SetRenderDrawColor (WHITE);
    sout << "Hit any key to end.\n";

    SSDL_WaitKey();

    return 0;
}
