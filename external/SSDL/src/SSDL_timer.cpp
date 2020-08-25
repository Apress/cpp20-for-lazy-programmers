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

//Timer-related functions.

#include "SSDL_color.h"
#include "SSDL_display.h"
#include "SSDL_timer.h"
#include "SSDL.h"

class SSDL_Timer 
{
public:
	static SSDL_Timer& Instance ()
	{
		static SSDL_Timer myInstance;
		return myInstance;
	}

	SSDL_Timer                  (const SSDL_Timer&) = delete;
	const SSDL_Timer& operator= (const SSDL_Timer&) = delete;

	void setFramesPerSecond (Uint32 fps) { frameDuration_ = 1000/fps; }
		//maybe I shd just do frame duration as 1/60 of a second?
	bool sync () ;
private:
	SSDL_Timer () : timeAtNextFrame_ (0)
	{
		setFramesPerSecond (60);	//default to 60 frames per second.
	}

	Uint32 frameDuration_;		//in milliseconds
	Uint32 timeAtNextFrame_;	//in milliseconds, counting from time we started SDL
};

// Frame Per Second Function  , put this in a loop
bool SSDL_Timer::sync()
{
	if (SSDL_Display::Instance().isTimeToQuit()) return false;

	SSDL_RenderPresent();

	//SDL_GetTicks returns current time (since SDL was initialized)
	//if the time at the next frame is later than that, wait.  How long?  The difference
	Uint32 currentTime = SDL_GetTicks();
	if (timeAtNextFrame_ > currentTime)
		SDL_Delay(timeAtNextFrame_ - currentTime);

	//Now set the time at the next frame to the current time, plus the duration of one frame
	timeAtNextFrame_ = currentTime + frameDuration_;

	return true;
}

bool SSDL_IsQuitMessage ()
{
	SSDL_DefaultEventHandler ();
	return ! SSDL_IsNextFrame ();
}

void SSDL_SetFramesPerSecond (Uint32 FPS){	SSDL_Timer::Instance().setFramesPerSecond (FPS); }
bool SSDL_IsNextFrame ()				 {	return SSDL_Timer::Instance().sync (); }