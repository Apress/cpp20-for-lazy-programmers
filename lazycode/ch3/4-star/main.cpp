// Program to make a 5-point star in center of screen
//               -- from _C++20 for Lazy Programmers_

#include <cmath>
#include "SSDL.h"

int main(int argc, char** argv)
{
    constexpr double PI = 3.14159;

    // Starting out with some generally useful numbers...

    // center of screen
    const     int CENTER_X         = SSDL_GetWindowWidth()  / 2, 
                  CENTER_Y         = SSDL_GetWindowHeight() / 2;  
    constexpr int RADIUS           = 200,
                  NUMBER_OF_POINTS =   5;

    // angle information...
    double        angle            = 0;     // angle starts at 0
    
    constexpr double ANGLE_INCREMENT
	          = (2 / double(NUMBER_OF_POINTS)) * PI; // right
                            // increases by whole circle/5 each time

    // ...now we make the successive lines
    int x, y;               // endpt of line (other endpt is center)

    x = CENTER_X + int(RADIUS * cos(angle));       // calc endpoint
    y = CENTER_Y + int(RADIUS * sin(angle));
    SSDL_RenderDrawLine(CENTER_X, CENTER_Y, x, y); // draw line
    angle += ANGLE_INCREMENT;                      // go on to next

    x = CENTER_X + int(RADIUS * cos(angle));       // calc endpoint
    y = CENTER_Y + int(RADIUS * sin(angle));
    SSDL_RenderDrawLine(CENTER_X, CENTER_Y, x, y); // draw line
    angle += ANGLE_INCREMENT;                      // go on to next

    x = CENTER_X + int(RADIUS * cos(angle));       // calc endpoint
    y = CENTER_Y + int(RADIUS * sin(angle));
    SSDL_RenderDrawLine(CENTER_X, CENTER_Y, x, y); // draw line
    angle += ANGLE_INCREMENT;                      // go on to next

    x = CENTER_X + int(RADIUS * cos(angle));       // calc endpoint
    y = CENTER_Y + int(RADIUS * sin(angle));
    SSDL_RenderDrawLine(CENTER_X, CENTER_Y, x, y); // draw line
    angle += ANGLE_INCREMENT;                      // go on to next

    x = CENTER_X + int(RADIUS * cos(angle));       // calc endpoint
    y = CENTER_Y + int(RADIUS * sin(angle));
    SSDL_RenderDrawLine(CENTER_X, CENTER_Y, x, y); // draw line
    angle += ANGLE_INCREMENT;                      // go on to next

    // end program
    SSDL_WaitKey();
    return 0;
}
