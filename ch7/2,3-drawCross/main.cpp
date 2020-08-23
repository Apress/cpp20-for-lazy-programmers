//Program to draw a cross on the screen
//		-- from _C++20 for Lazy Programmers_

#include "SSDL.h"

void drawCross(int x, int y, int distToEnds);

int main(int argc, char** argv)
{
    //int crossX = 40, crossY = 25, size = 20;

    //drawCross (crossX, crossY, size); //draw a cross
  
    drawCross( 40, 40, 20); //draw three crosses
    drawCross( 80, 30, 15);
    drawCross(110, 50, 40);

    SSDL_WaitKey();

    return 0;
}

void drawCross(int x, int y, int distToEnds)
//draw a cross centered at x, y, with a distance to ends as given
{
    SSDL_RenderDrawLine(x - distToEnds, y, x + distToEnds, y);//draw horizontal
    SSDL_RenderDrawLine(x, y - distToEnds, x, y + distToEnds);//draw vertical
}

