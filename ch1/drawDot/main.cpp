//Draw a dot at the center of the screen
//		-- from _C++ for Lazy Programmers_

#include "SSDL.h" 

int main (int argc, char** argv)
{
	//draws a dot at the center position (320, 240)
	SSDL_RenderDrawPoint (320, 240); 

	SSDL_WaitKey ();

	return 0;
}
