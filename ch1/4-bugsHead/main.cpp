// Program to draw a cartoonish bug's head on the screen
//       -- from _C++20 for Lazy Programmers_

#include "SSDL.h"

int main (int argc, char** argv)
{
    SSDL_RenderDrawCircle (430, 250, 200);     // draw the bug's head
    
    SSDL_RenderDrawCircle (320, 250,  45);     // the left eye
    SSDL_RenderDrawCircle (470, 270,  45);     // the right eye

    SSDL_RenderDrawLine   (360, 140, 280,  40);// left antenna
    SSDL_RenderDrawLine   (280,  40, 210,  90);

    SSDL_RenderDrawLine   (520, 140, 560,  40);// right antenna
    SSDL_RenderDrawLine   (560,  40, 620,  80);

    SSDL_RenderDrawLine   (290, 350, 372, 410);// the smile
    SSDL_RenderDrawLine   (372, 410, 490, 400);

    SSDL_WaitKey ();                           // Wait for user to hit a key

    return 0;
}
