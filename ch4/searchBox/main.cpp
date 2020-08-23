//Program to draw a box around a fossil, to find its coordinates
//		-- from _C++ for Lazy Programmers_

#include "SSDL.h"

int main (int argc, char** argv)
{
    //Resize window to fit the background image.
    SSDL_SetWindowSize (500, 375);              //image is 500x375
    SSDL_SetWindowTitle("A box to enclose the fossil -- hit a key to end");

    //Load up the world to find fossil in
    const SSDL_Image BACKGROUND = SSDL_LoadImage ("media/ammonitePuzzle.jpg");
    SSDL_RenderImage (BACKGROUND, 0, 0);

    //Draw a box where we think he is.  Is it right?
    SSDL_SetRenderDrawColor (WHITE);          //a *white* box, for visibility
    
    //arguments below mean: left x, top y, width, height
    //SSDL_RenderDrawRect (375, 175, 80, 50); //first guess
    SSDL_RenderDrawRect (335, 180, 45, 35);   //corrected numbers

    //End program
    SSDL_WaitKey ();

    return 0;
}

