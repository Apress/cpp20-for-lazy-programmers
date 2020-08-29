// Program to play, pause, and resume a sound, based on mouse clicks.
// ...while an alien spaceship speeds by
//       -- from _C++20 for Lazy Programmers_

#include "SSDL.h"

// SSDL_SoundSystemInitializer initializer(88020, MIX_DEFAULT_FORMAT, AUDIO_U8, 4096);

struct Point2D { int x_, y_; };

void toggleSound            ();
void myEventHandler         (bool& mouseWasClicked);
void drawSignpost           ();

int main (int argc, char** argv)
{
    // Set up window
    SSDL_SetWindowTitle ("Program to play and pause sounds. Hit Esc to exit.");

    // Set up music
    const SSDL_Music BKGD_MUSIC
        = SSDL_LoadMUS ("media/178267__alqutis__hovercar-short.wav");
    SSDL_VolumeMusic (int (MIX_MAX_VOLUME * 0.25));
                          // play at quarter volume: full is too loud
    SSDL_PlayMusic (BKGD_MUSIC);

    // Set up font -- big font, just for the heck of it
    SSDL_Font bigFont = SSDL_OpenSystemFont ("verdana.ttf", 32);
    SSDL_SetFont (bigFont);

    // Set up sprite
    SSDL_Sprite spaceshipSprite
        = SSDL_LoadImage("media/ufo-2718088-small.png");

    constexpr int SPACESHIP_SPEED  =  3,
                  SPACESHIP_HEIGHT = 20;
    Point2D spaceship = {0, SPACESHIP_HEIGHT};
    SSDL_SetSpriteLocation
        (spaceshipSprite, spaceship.x_, spaceship.y_); 

    while (SSDL_IsNextFrame ())
    {
		// Events

        bool mouseWasClicked;
        myEventHandler (mouseWasClicked);        // handle events

        if (mouseWasClicked) toggleSound ();

        // Display 

        SSDL_SetRenderDrawColor (BLACK);
        SSDL_RenderClear ();

        drawSignpost();

        SSDL_SetCursor (0, 0);
        SSDL_SetRenderDrawColor (WHITE);

        if (SSDL_PausedMusic ())
            sout << "Sound off\n";
        else
            sout << "Sound on\n";
        
        sout << "To toggle, click the mouse\n";
        SSDL_RenderSprite (spaceshipSprite);

        // Update UFO position

        spaceship.x_ += SPACESHIP_SPEED;
        // if it's off screen to the right, start at left again
        if (spaceship.x_ > SSDL_GetWindowWidth())
            spaceship.x_ = 0; 
		SSDL_SetSpriteLocation(spaceshipSprite,
			spaceship.x_, spaceship.y_);
	}

    return 0;
}

void toggleSound ()
{
    if (! SSDL_PausedMusic ())  SSDL_PauseMusic  ();
    else                        SSDL_ResumeMusic ();
}

void myEventHandler (bool& mouseClicked)
{
    SDL_Event event;
    mouseClicked = false;   // We'll soon know if mouse was clicked

    while (SSDL_PollEvent (event))
        switch (event.type)
        {
        case SDL_QUIT:            SSDL_DeclareQuit(); 
            break;
        case SDL_KEYDOWN:         if (SSDL_IsKeyPressed (SDLK_ESCAPE))
                                      SSDL_DeclareQuit(); 
            break;
        case SDL_MOUSEBUTTONDOWN: mouseClicked = true; // It was!
            break;
        }
}

void drawSignpost()
{
    // Draw the post
	static const SSDL_Color BROWN(95, 75, 50);
	SSDL_SetRenderDrawColor(BROWN);
    SSDL_RenderFillRect(510, 300, 20, 160);

    // ...and the sign
    static const SSDL_Image SIGN =
        SSDL_LoadImage ("media/sign-2881876-small.png");
    SSDL_RenderImage(SIGN, 440, 180);
}
