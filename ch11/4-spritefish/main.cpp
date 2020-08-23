//Program to place a fish sprite on the screen
//              -- from _C++20 for Lazy Programmers_

#include "SSDL.h"

using namespace std;

int main (int argc, char** argv)
{
    //Set up window characteristics
    constexpr int WINDOW_WIDTH = 600, WINDOW_HEIGHT = 300;
    SSDL_SetWindowSize  (WINDOW_WIDTH, WINDOW_HEIGHT);
    SSDL_SetWindowTitle ("Sprite example 1.  Hit Esc to exit.");

    //initialize colors
    const SSDL_Color AQUAMARINE(100, 255, 150); //the water

    //initialize the sprite's image and location 
    SSDL_Sprite fishSprite = SSDL_LoadImage("media/discus-fish.png");
    SSDL_SetSpriteLocation (fishSprite, 
                            SSDL_GetWindowWidth()/2, 
                            SSDL_GetWindowHeight()/2); 

    //*** Main loop ***
    while (SSDL_IsNextFrame ())
    {
        //Look for quit messages
        SSDL_DefaultEventHandler ();
        
        //Clear the screen for a new frame in our "movie"
        SSDL_RenderClear (AQUAMARINE);
        
        //Draw crosshairs in the center
        SSDL_SetRenderDrawColor (BLACK);
        SSDL_RenderDrawLine (0, SSDL_GetWindowHeight()/2, 
                             SSDL_GetWindowWidth()  , 
                             SSDL_GetWindowHeight()/2);
        SSDL_RenderDrawLine (SSDL_GetWindowWidth()/2,  0, 
                             SSDL_GetWindowWidth()/2, 
                             SSDL_GetWindowHeight());
        
        //and print the statistics on the fish
        SSDL_SetCursor (0, 0);  //reset cursor each time or 
        // the messages will run off the screen!
        sout << "Sprite info\n";
        sout << "X:\t"      
             << SSDL_GetSpriteX     (fishSprite) << endl;
        sout << "Y:\t"      
             << SSDL_GetSpriteY     (fishSprite) << endl;
        sout << "Width:\t"  
             << SSDL_GetSpriteWidth (fishSprite) << endl;
        sout << "Height:\t" 
             << SSDL_GetSpriteHeight(fishSprite) << endl;
        
        //Show that fish
        SSDL_RenderSprite (fishSprite);
    }

    return 0;
}
