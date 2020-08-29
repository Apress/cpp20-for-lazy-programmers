// Program to show an image on the screen
//      -- from _C++20 for Lazy Programmers_

#include "SSDL.h"

int main (int argc, char **argv)
{
	// Show image
	SSDL_Image BEACH = SSDL_LoadImage ("media/beach.jpg"); 
	SSDL_RenderImage (BEACH, 0, 0);

	SSDL_WaitKey();

	return 0;
}
