/*Simple SDL, a wrapper library for SDL.
  
  Copyright (C) 2020 Will Briggs.

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution. */
  
//Various functions related to I/O (mouse or keyboard)

#include <SDL.h>
#include "SSDL.h" //for refreshDisplay

static bool isEscapeMeansQuit = true; //make this something that starts with "SSDL_"
//static bool isVisible = true;        
void SSDL_ToggleEscapeMeansQuit () { isEscapeMeansQuit = ! isEscapeMeansQuit; }

bool SSDL_IsKeyPressed (SDL_Keycode whichKey)
{	//The !=0 at the end is to suppress a coercion from Uint8 to bool warning
	//SDL_GetScancodeFromKey:  SDL_GetKeyboardState returns an array that'll tell you
	// what scancodes are currently pressed.  We want to know which keys.  So we must
	// convert
	return SDL_GetKeyboardState (NULL)[SDL_GetScancodeFromKey(whichKey)]!=0;
}

void SSDL_CheckForQuitMessages (const SDL_Event& sdlEvent)
{
	if (sdlEvent.type == SDL_QUIT) SSDL_Display::Instance().declareTimeToQuit ();
	if (isEscapeMeansQuit && sdlEvent.type == SDL_KEYDOWN 
		&& sdlEvent.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		SSDL_Display::Instance().declareTimeToQuit ();
}

void SSDL_WaitEvent (Uint32 eventType, SDL_Event& sdlEvent) 
{ 
	//if (isVisible) 
		SSDL_RenderPresent ();	
		//Why this?  because it's annoying to have the screen not update while you're
		//waiting for an event!

	while (! SSDL_Display::Instance().isTimeToQuit ())
	{
		if (SDL_WaitEvent (&sdlEvent) == 0) throw SSDL_Exception();
		SSDL_CheckForQuitMessages (sdlEvent);
		if (sdlEvent.type == eventType) return ;
	}
}

void SSDL_ToggleEscapeIsQuit () { isEscapeMeansQuit = ! isEscapeMeansQuit; }

void SSDL_DefaultEventHandler ()
{
	SSDL_Event event;

	while (SSDL_PollEvent (event))
		switch (event.type)
		{
		case SDL_QUIT:    SSDL_DeclareQuit(); break;
		case SDL_KEYDOWN: if (SSDL_IsKeyPressed (SDLK_ESCAPE)) SSDL_DeclareQuit(); 

		//The rest of these you should probably leave alone.
			//First: if the window is minimized, make a note we don't need to draw it until it isn't
		//case SDL_WINDOWEVENT_MINIMIZED:    isVisible = false; break;

			//Second: if it stopped being minimized, make a note we DO need to draw it
		case SDL_WINDOWEVENT_MAXIMIZED:
		case SDL_WINDOWEVENT_RESTORED:     //isVisible = true; 

			//...and if it was just made visible, or was obscured and is now less so, or
			//  was resized, do an immediate update
		case SDL_WINDOWEVENT_SIZE_CHANGED: 
		case SDL_WINDOWEVENT_EXPOSED:      SDL_RenderPresent(SSDL_Display::Instance());
			                               break;
		}
}

int  SSDL_WaitMouse()
{
	SDL_Event event;
	SSDL_WaitEvent(SDL_MOUSEBUTTONDOWN, event);
	return event.button.button;
}

SDL_Keycode SSDL_WaitKey()
{
	SDL_Event event;
	SSDL_WaitEvent(SDL_KEYDOWN, event);
	return event.key.keysym.sym;
}
