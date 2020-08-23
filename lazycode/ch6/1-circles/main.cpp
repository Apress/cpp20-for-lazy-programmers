// Program to draw concentric circles
//   Each circle is half the area of the one outside it
//		-- from _C++20 for Lazy Programmers_

#include <cmath>   // for sqrt
#include "SSDL.h" 

int main (int argc, char** argv)
{
    SSDL_SetWindowTitle ("Hit any key to exit.");

    const int CENTER_X = SSDL_GetWindowWidth ();
    const int CENTER_Y = SSDL_GetWindowHeight();

    double radius = 200.0;  // start radius at 200
    do
    {
        // draw a circle at center of screen, with this radius
        SSDL_RenderDrawCircle (CENTER_X/2, CENTER_Y/2, int (radius)); 
	
        radius /= sqrt (2);	// divide radius by √2
    }
    while (radius > 1.0);   // quit when circle's too small to see

    SSDL_WaitKey();

    return 0;
}
