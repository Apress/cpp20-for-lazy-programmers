// Program that pastes an image onto a background
//               -- from _C++20 for Lazy Programmers_

#include "SSDL.h"

int main (int argc, char **argv)
{
    // Set window parameters
    SSDL_SetWindowSize(400, 300);               // make a 400x300 window
    SSDL_SetWindowTitle("The flamingo decided to come too!");

    // Load images
    const SSDL_Image BEACH    = SSDL_LoadImage("media/beach.jpg");
    const SSDL_Image FLAMINGO = SSDL_LoadImage("media/flamingo.png");
        
    // Paste in the background image, and the flamingo
    constexpr int    FLAMINGO_X = 0, FLAMINGO_Y = 175; // Flamingo's on left, down screen

    SSDL_RenderImage(BEACH,    0,                   0);
    SSDL_RenderImage(FLAMINGO, FLAMINGO_X, FLAMINGO_Y);

    SSDL_WaitKey ();

    return 0;
}
