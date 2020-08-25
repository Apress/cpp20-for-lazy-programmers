// Program to draw a staircase
//               -- from _C++20 for Lazy Programmers_

#include "SSDL.h"

struct Point2D  // A struct to hold a 2-D point
{
    int x_, y_;
};

int main (int argc, char** argv)
{
    SSDL_SetWindowSize  (400, 200);
    SSDL_SetWindowTitle ("Stairway example:  Hit a key to end");

    constexpr int MAX_POINTS        = 25;
    constexpr int STAIR_STEP_LENGTH = 15;

    Point2D myPoints [MAX_POINTS];

    int x = 0;                          // Start at lower left corner
    int y = SSDL_GetWindowHeight()-1;   //  of screen

    for (int i = 0; i < MAX_POINTS; ++i) // Fill an array with points
    {
        myPoints[i] = { x, y };

        // On iteration 0, go up (change Y)
        // On iteration 1, go right
        //  then up, then right, then up...
        
        if (i%2 == 0)                  // If i is even...
            y -= STAIR_STEP_LENGTH;
        else
            x += STAIR_STEP_LENGTH;
    }

    for (int i = 0; i < MAX_POINTS-1; ++i) // Display the staircase
        // The last iteration draws a line from point
        //  i to point i+1... which is why we stop a
        //  little short.  We don't want to refer to
        //  the (nonexistent) point # MAX_POINTS.
        SSDL_RenderDrawLine (   myPoints[i  ].x_, myPoints[i  ].y_, 
                                myPoints[i+1].x_, myPoints[i+1].y_);

    SSDL_WaitKey();

    return 0;
}
