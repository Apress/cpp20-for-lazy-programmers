// Program to find a fossil in a field of stones
//               -- from _C++20 for Lazy Programmers_

#include "SSDL.h"

int main (int argc, char** argv)
{
    // Set up window
    constexpr int PICTURE_WIDTH=500, PICTURE_HEIGHT=375; 
                                          // size of the picture
    constexpr int WINDOW_WIDTH =500, WINDOW_HEIGHT =430; 
                                          // size of entire window
                                          // (has extra room for messages)
    SSDL_SetWindowTitle ("My fossil hunt: a hidden-object game");
    SSDL_SetWindowSize  (WINDOW_WIDTH, WINDOW_HEIGHT);

    // Load up the world to find the fossil in
    const SSDL_Image BACKGROUND
                           = SSDL_LoadImage("media/ammonitePuzzle.jpg");
    SSDL_RenderImage (BACKGROUND, 0, 0);

    // Print instructions to the user
    SSDL_SetCursor (0, PICTURE_HEIGHT);
    sout << "Where's the ammonite?  Click it to win.\n";

    // Get that mouse click  
    SSDL_WaitMouse ();

    // See where we clicked, and report if the fossil was found
    // I got these numbers by running the 2-searchBox program
    constexpr int BOX_LEFT = 335, BOX_TOP   = 180; 
    constexpr int BOX_WIDTH=  45, BOX_HEIGHT=  35;


    int x= SSDL_GetMouseX(), y = SSDL_GetMouseY();

    // Is X between left side of box and right? Is Y also within bounds?
    bool isXInRange = (BOX_LEFT < x && x < BOX_LEFT+BOX_WIDTH );
    bool isYInRange = (BOX_TOP  < y && y < BOX_TOP +BOX_HEIGHT);

    if (isXInRange && isYInRange)
    {
        sout << "You found the ammonite! Here's your Ph.D.\n";
 
        // Now we'll flash where the fossil was
        SSDL_SetRenderDrawColor(RED);
        SSDL_RenderDrawRect(BOX_LEFT, BOX_TOP, BOX_WIDTH, BOX_HEIGHT);
        SSDL_Delay(250); // 250 msec, or 1/4 sec

        SSDL_SetRenderDrawColor(WHITE);
        SSDL_RenderDrawRect(BOX_LEFT, BOX_TOP, BOX_WIDTH, BOX_HEIGHT);
        SSDL_Delay(250); // 250 msec, or 1/4 sec

        SSDL_SetRenderDrawColor(RED);
        SSDL_RenderDrawRect(BOX_LEFT, BOX_TOP, BOX_WIDTH, BOX_HEIGHT);
        SSDL_Delay(250); // 250 msec, or 1/4 sec

        SSDL_SetRenderDrawColor(WHITE);
        SSDL_RenderDrawRect(BOX_LEFT, BOX_TOP, BOX_WIDTH, BOX_HEIGHT);
        SSDL_Delay(250); // 250 msec, or 1/4 sec
    }
    else
        sout << "You lose.\n";    

    // End program
    sout << "Hit a key to end.";

    SSDL_WaitKey ();

    return 0;
}
