// Program to show an image on the screen
// 		-- from _C++20 for Lazy Programmers_

#include "SSDL.h"

int main(int argc, char **argv)
{
	// Set window parameters
	SSDL_SetWindowSize  (400, 300);		// make a 400x300 window
	SSDL_SetWindowTitle ("My trip to the beach");

	// Show image
	SSDL_Image BEACH = SSDL_LoadImage ("media/beach.jpg"); 
	SSDL_RenderImage (BEACH, 0, 0);

	SSDL_WaitKey();

	return 0;
}

