//Displays boxes of colors, labeled
//      -- from _C++ for Lazy Programmers_

#include "SSDL.h"

int main(int argc, char** argv)
{
    SSDL_SetWindowTitle("Two colored squares, with labels");

    //Make a dark grey background -- another way to do it (see Ex. 1-6)
    const SSDL_Color DARK_GREY = SSDL_CreateColor(100, 100, 100);
    SSDL_RenderClear(DARK_GREY);

    //We'll have two boxes across
    //First box:
    SSDL_SetRenderDrawColor(RED);
    SSDL_RenderFillRect    (0, 0, 100, 100);
    SSDL_SetRenderDrawColor(WHITE);
    SSDL_RenderTextCentered("RED", 50, 50);    //dead center of 
                                               //  red square

    //Second box:
    SSDL_SetRenderDrawColor(GREEN);
    SSDL_RenderFillRect    (100, 0, 100, 100);
    SSDL_SetRenderDrawColor(WHITE);
    SSDL_RenderTextCentered("GREEN", 150, 50); //dead center of 
                                               //  green square

    //Report number of colors, thus demonstrating non-centered text
    SSDL_RenderText         ("Number of colors:  ", 0, 100);
    SSDL_RenderText         (2, 150, 100);     //We showed 2 colors,
                                               //  so we print 2

        //Note sout still has its cursor up at the top:
        //  SSDL_RenderText* doesn't use or alter the cursor
        //Therefore "Hit any key to end" still shows at top of screen

    sout << "Hit any key to end.\n";

    SSDL_WaitKey();

    return 0;
}
