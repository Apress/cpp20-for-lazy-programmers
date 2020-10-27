// Program to draw a cross on the screen
//     -- from _C++20 for Lazy Programmers_

#include "SSDL.h"

void drawCross(int x, int y, int distToEnds);

int main(int argc, char** argv)
{
	int crossX = 40, crossY = 25, size = 20;
	drawCross(crossX, crossY, size); //draw a cross
	SSDL_WaitKey();
	return 0;
}

// draw a cross centered at x, y, with a distance to ends as given
void drawCross(int x, int y, int distToEnds)
{
	SSDL_RenderDrawLine(x - distToEnds, y, x + distToEnds, y); // draw horizontal
	SSDL_RenderDrawLine(x, y - distToEnds, x, y + distToEnds); // draw vertical
}