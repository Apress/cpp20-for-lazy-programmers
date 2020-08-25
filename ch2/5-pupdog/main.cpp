// Program that pastes two images onto a background
//         -- from _C++20 for Lazy Programmers_

#include "SSDL.h"

int main(int argc, char **argv)
{
    // Set window parameters
    SSDL_SetWindowSize(400, 300);       // make a 400x300 window
    SSDL_SetWindowTitle("Pup dog and flamingo at the beach");

    // Load images
    const SSDL_Image BEACH     = SSDL_LoadImage("media/beach.jpg");
    const SSDL_Image FLAMINGO  = SSDL_LoadImage("media/flamingo.png");
    const SSDL_Image PUPDOG    = SSDL_LoadImage("media/pupdog.png");

    // Locations and dimensions for .png images
    constexpr int FLAMINGO_X   =   0, FLAMINGO_Y    = 175;
                                    // Flamingo's on left, down screen
    constexpr int PUPDOG_X     = 320, PUPDOG_Y      = 225;
                                    // Pupdog's on right down screen
    constexpr int PUPDOG_WIDTH =  50, PUPDOG_HEIGHT =  75;
                                    // Pup dog is bigger than I want, so I
                                    //  make her 50x75. It's better to 
                                    //  resize when making the image, but
                                    //  this works too

    // Paste in the background image, plus flamingo and pupdog
    SSDL_RenderImage (BEACH,    0,          0);
    SSDL_RenderImage (FLAMINGO, FLAMINGO_X, FLAMINGO_Y);
    SSDL_RenderImage (PUPDOG,   PUPDOG_X,   PUPDOG_Y, 
                      PUPDOG_WIDTH, PUPDOG_HEIGHT);

    SSDL_WaitKey();

    return 0;
}

