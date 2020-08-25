// Program to show an image on the screen
// 		-- from _C++20 for Lazy Programmers_

#include "SSDL.h"

int main(int argc, char **argv)
{
    // Set window parameters
    SSDL_SetWindowSize  (400, 300);		// make a 400x300 window
    SSDL_SetWindowTitle ("My trip to the beach");

    // Show image
    const SSDL_Image BEACH = SSDL_LoadImage("media/beach.jpg"); 
    SSDL_RenderImage(BEACH, 0, 0);

    // Make a label in the middle, centered
    SSDL_RenderTextCentered("BALI? BORA BORA? BEAUTIFUL, WHEREVER!",
                            SSDL_GetWindowWidth () / 2,
                            SSDL_GetWindowHeight() / 2);

    SSDL_WaitKey();

    return 0;
}
