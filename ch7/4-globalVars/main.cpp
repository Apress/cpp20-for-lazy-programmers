//Program to draw a cross on the screen
//		-- from _C++20 for Lazy Programmers_

#include "SSDL.h"

//GLOBAL VARIABLES: THE EIGHTH DEADLY SIN
int       x = 40, y = 40;  
int       distanceToEnds = 20;

//Prototypes
void drawCross  ();

int main (int argc, char** argv)
{
    //draw three crosses
    drawCross(); 
    x =  80; y = 30; distanceToEnds = 15; drawCross();
    x = 110; y = 50; distanceToEnds = 40; drawCross();

    SSDL_WaitKey();

    return 0;
}

void drawCross ()
//draw a cross centered at x, y, with distance to ends, all global
{
    SSDL_RenderDrawLine (x-distanceToEnds, y, x+distanceToEnds, y); 
    SSDL_RenderDrawLine (x, y-distanceToEnds, x, y+distanceToEnds); 
}
