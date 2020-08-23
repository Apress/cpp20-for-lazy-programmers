//Program that makes a splat wherever you click
//      -- from _C++20 for Lazy Programmers_

#include "SSDL.h"

void myEventHandler (bool& mouseClicked);
    
int main (int argc, char** argv)
{
    SSDL_SetWindowTitle ("Click the mouse to see and hear a splat; "
                         "hit Esc to end.");

    const SSDL_Sound SPLAT_SOUND =
        SSDL_LoadWAV ("media/445117__breviceps__cartoon-splat.wav");

    //Set up sprite with image and a size, and offset its reference
    // point so it'll be centered on our mouse clicks
    SSDL_Sprite splatSprite = SSDL_LoadImage("media/splat.png");
    
    constexpr int SPLAT_WIDTH=50, SPLAT_HEIGHT=50;
    SSDL_SetSpriteSize  (splatSprite, SPLAT_WIDTH,   SPLAT_HEIGHT);
    SSDL_SetSpriteOffset(splatSprite, SPLAT_WIDTH/2, SPLAT_HEIGHT/2);

    while (SSDL_IsNextFrame ())
    {
        static int framesLeftTillSplatDisappears =  0; 
        constexpr int SPLAT_LIFETIME             = 60; //It lasts one second

        //Handle events
        bool isMouseClick;      
        myEventHandler (isMouseClick);

       //Display things
        SSDL_RenderClear();
        if (framesLeftTillSplatDisappears > 0) 
            SSDL_RenderSprite(splatSprite);

         //Update things: process clicks and framesLeft
        if (framesLeftTillSplatDisappears > 0) //if splat is active
            --framesLeftTillSplatDisappears;   // keep counting down
        
        else if (isMouseClick)      //if not, and we have a click...
        {  
                                    //Reset that waiting time
            framesLeftTillSplatDisappears = SPLAT_LIFETIME;

                                    //Play splat sound
            SSDL_PlaySound (SPLAT_SOUND);

            SSDL_SetSpriteLocation  //move splat sprite to 
                (splatSprite,       // location of mouse click
                 SSDL_GetMouseX(), 
                 SSDL_GetMouseY()); 
        }
    }

    return 0;
}

void myEventHandler (bool& mouseClicked)
{
    SDL_Event event;
    mouseClicked = false;   //We'll soon know if mouse was clicked

    while (SSDL_PollEvent (event))
        switch (event.type)
        {
        case SDL_QUIT:            SSDL_DeclareQuit(); 
            break;
        case SDL_KEYDOWN:         if (SSDL_IsKeyPressed (SDLK_ESCAPE))
                                      SSDL_DeclareQuit(); 
            break;
        case SDL_MOUSEBUTTONDOWN: mouseClicked = true; //It was!
            break;
        }
}

