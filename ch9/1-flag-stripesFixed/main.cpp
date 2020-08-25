// Program to draw Old Glory on the screen
//       -- from _C++20 for Lazy Programmers_

#include <cmath> // for sin, cos
#include "SSDL.h"

constexpr double PI = 3.14159;

// Dimensions
constexpr int HOIST                   = 390; // My pick for flag width
                                             // Called "A" in Fig. 9-1
constexpr int FLY                     = int (HOIST * 1.9),    // B
              UNION_HOIST             = int (HOIST * 0.5385), // C
              UNION_FLY               = int (HOIST * 0.76);   // D                  

constexpr int UNION_VERTICAL_MARGIN   = int (HOIST * 0.054),  // E & F
              UNION_HORIZONTAL_MARGIN = int (HOIST * 0.063);  // G & H

constexpr int STAR_DIAMETER           = int (HOIST * 0.0616); // K

constexpr int STRIPE_WIDTH            = HOIST/13;             // L

// Colors
const SSDL_Color RED_FOR_US_FLAG    = SSDL_CreateColor (179, 25, 66);
const SSDL_Color BLUE_FOR_US_FLAG   = SSDL_CreateColor ( 10, 49, 97);

void drawStripes    ();             // the white and red stripes
void drawUnion      ();             // the blue square
void drawStar       (int x, int y); // draw a star centered at x, y

// draw a row of howMany stars, starting with the x, y position,
//  using UNION_HORIZONTAL_MARGIN to go to the right as you draw
void drawRowOfStars (int howMany, int x, int y);

int main (int argc, char** argv)
{
    SSDL_SetWindowTitle ("Old Glory");
    SSDL_SetWindowSize (FLY, HOIST);

    drawStripes ();
    drawUnion   (); // draw the union (blue square)

    SSDL_WaitKey();

    return 0;
}

void drawStripes ()
{
    SSDL_SetRenderDrawColor (RED_FOR_US_FLAG);
    SSDL_RenderFillRect (0, 0, FLY, HOIST); // first, a big red square

    // Starting with stripe 1, draw every other stripe WHITE
    SSDL_SetRenderDrawColor (WHITE);
    for (int stripe = 1; stripe < 13; stripe += 2)
        SSDL_RenderFillRect (0, stripe*STRIPE_WIDTH, 
                             FLY, STRIPE_WIDTH);
}

// draw a row of howMany stars, starting with the x, y position,
//  using UNION_HORIZONTAL_MARGIN to go to the right as you draw
void drawRowOfStars (int howMany, int x, int y)
{
    for (int i = 0; i < howMany; ++i)
    {
        drawStar (x, y); x += 2*UNION_HORIZONTAL_MARGIN;
    }
}

void drawUnion ()
{
    SSDL_SetRenderDrawColor (BLUE_FOR_US_FLAG);
    SSDL_RenderFillRect (0, 0, UNION_FLY, UNION_HOIST); 
    // draw the blue box

    SSDL_SetRenderDrawColor (WHITE);
    int row = 1;  // What's the y position of the current row of stars?
    for (int i = 0; i < 4; ++i) // Need 4 pairs of 6- and 7-star rows
    {
        drawRowOfStars (6, 
                        UNION_HORIZONTAL_MARGIN, 
                        row*UNION_VERTICAL_MARGIN); 

        ++row;

        // The 2nd row is staggered right slightly
        drawRowOfStars (5, 
                        2*UNION_HORIZONTAL_MARGIN,
                        row*UNION_VERTICAL_MARGIN); 
        ++row;
    }
    // ...and one final 6-star row
    drawRowOfStars (6, UNION_HORIZONTAL_MARGIN,
                    row*UNION_VERTICAL_MARGIN); 
}

void drawStar (int centerX, int centerY)
{
    constexpr int RADIUS         = STAR_DIAMETER/2,
                  POINTS_ON_STAR = 5;

    int x1, y1, x2, y2;
    double angle = PI/2;    // 90 degrees: straight up vertically
                            // 90 degrees is PI/2 radians

    x1 = int (RADIUS * cos (angle));  // Find x, y point at this angle
    y1 = int (RADIUS * sin (angle));  //  relative to center

    for (int i = 0; i < POINTS_ON_STAR; ++i)
    {
       angle += (2 * PI / 360) / POINTS_ON_STAR;
                                        // go to next point on star

        x2 = int (RADIUS * cos (angle));// Calculate its x,y point
        y2 = int (RADIUS * sin (angle));//  relative to center 

        SSDL_RenderDrawLine (centerX+x1, centerY+y1, 
                             centerX+x2, centerY+y2);  
 
        x1 = x2;                        // Remember the new point 
        y1 = y2;                        //   for the next line
    }
}   
