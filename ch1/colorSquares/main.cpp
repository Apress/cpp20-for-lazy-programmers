//Displays boxes of colors
//      -- from _C++ for Lazy Programmers_

#include "SSDL.h"

int main (int argc, char** argv)
{
    SSDL_SetWindowTitle ("Four squares in different colors");

    //We'll use 3 built-in colors, and 3 new ones
    const SSDL_Color PUCE       = SSDL_CreateColor (127,  90,  88);
    const SSDL_Color MAHOGANY   = SSDL_CreateColor (192,  64,   0);
    const SSDL_Color DARK_GREY  = SSDL_CreateColor (100, 100, 100);

    //Make a dark grey background
    SSDL_SetRenderEraseColor    (DARK_GREY);
    SSDL_RenderClear            ();

    //We'll have two boxes across, and two down

    //The top row. These colors are already defined in SSDL.h.
    SSDL_SetRenderDrawColor     (RED);
    SSDL_RenderFillRect         (  0,   0, 100, 100);
    SSDL_SetRenderDrawColor     (GREEN);
    SSDL_RenderFillRect         (100,   0, 100, 100);

    //The next row, using new colors
    SSDL_SetRenderDrawColor     (PUCE);
    SSDL_RenderFillRect         (  0, 100, 100, 100);
    SSDL_SetRenderDrawColor     (MAHOGANY);
    SSDL_RenderFillRect         (100, 100, 100, 100);

    //Program's end.
    //Must restore color to white, or we'll get mahogany text!
    SSDL_SetRenderDrawColor (WHITE);
    sout << "Hit any key to end.\n";

    SSDL_WaitKey();

    return 0;
}
