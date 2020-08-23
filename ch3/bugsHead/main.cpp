//Program to draw a cartoonish bug's head on the screen
//      using calculations and constexprs
//      -- from _C++ for Lazy Programmers_

#include "SSDL.h"

int main (int argc, char** argv)
{
    constexpr int HEAD_X     = 430, HEAD_Y     = 260, HEAD_RADIUS = 200,
                  EYE_RADIUS =  50, 
                  EYE_OFFSET =  80; //How far lt/rt an eye is from center

    //draw the bug's head              
    SSDL_RenderDrawCircle (HEAD_X,            HEAD_Y, HEAD_RADIUS);  

    //left eye, and right
    SSDL_RenderDrawCircle (HEAD_X-EYE_OFFSET, HEAD_Y, EYE_RADIUS);
    SSDL_RenderDrawCircle (HEAD_X+EYE_OFFSET, HEAD_Y, EYE_RADIUS);

    SSDL_RenderDrawLine   (360, 140, 280,  40);//left antenna
    SSDL_RenderDrawLine   (280,  40, 210,  90);

    SSDL_RenderDrawLine   (520, 140, 560,  40);//right antenna
    SSDL_RenderDrawLine   (560,  40, 620,  80);

    SSDL_RenderDrawLine   (290, 350, 372, 410);//the smile
    SSDL_RenderDrawLine   (372, 410, 490, 400);

    SSDL_WaitKey ();             //Wait for user to hit a key

    return 0;
}
