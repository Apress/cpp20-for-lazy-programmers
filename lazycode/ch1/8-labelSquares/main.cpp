// Displays boxes of colors, labeled
//       -- from _C++20 for Lazy Programmers_

#include "SSDL.h"

int main(int argc, char** argv)
{
    SSDL_SetWindowTitle("Two colored squares, with labels");

    // New colors
    const SSDL_Color MAHOGANY  = SSDL_CreateColor(192,  64,   0);
    const SSDL_Color DARK_GREY = SSDL_CreateColor(100, 100, 100);

    // Make a dark grey background
    SSDL_RenderClear(DARK_GREY);

    // First square:
    SSDL_SetRenderDrawColor(GREEN);    
    SSDL_RenderFillRect    (0, 0, 100, 100);
    SSDL_SetRenderDrawColor(WHITE);
    SSDL_RenderTextCentered("GREEN", 50, 50);     // dead center of 
                                                  //   green square

    // Second square:
    SSDL_SetRenderDrawColor(MAHOGANY); 
    SSDL_RenderFillRect    (100, 0, 100, 100);
    SSDL_SetRenderDrawColor(WHITE);
    SSDL_RenderTextCentered("MAHOGANY", 150, 50); // dead center of 
                                                  //  mahogany square

    // Report number of colors, thus demonstrating non-centered text
    SSDL_RenderText         ("Number of colors:  ", 0, 100);
    SSDL_RenderText         (2, 150, 100);       // two colors

    // Note sout still has its cursor up at the top:
    //   SSDL_RenderText* doesn't use or alter the cursor
    // Therefore "Hit any key to end" still shows at top of screen

    sout << "Hit any key to end.\n";

    SSDL_WaitKey();

    return 0;
}
