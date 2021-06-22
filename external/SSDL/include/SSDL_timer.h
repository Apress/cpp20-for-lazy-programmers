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

//Timer-related functions.  I also need delay; wait for mouse; wait for key

#ifndef SSDL_TIMER_H
#define SSDL_TIMER_H

void SSDL_SetFramesPerSecond (Uint32 FPS);

bool SSDL_IsNextFrame  (); //updates screen, verifies there's no quit message found earlier
bool SSDL_IsQuitMessage(); //updates screen, polls events, verifies there's no (possibly new) quit message

inline void SSDL_Delay (Uint32 milliseconds) 
{ 
	if (SSDL_IsQuitMessage ()) return; //Hitting Esc or killing window will
	                                   // skip the delay to come.  Won't interrupt
					   // the delay if it's already going.  Fixable?
	SSDL_RenderPresent ();   //Be sure SSDL_IsQuitMessage doesn't call RenderPresent:
	                         //redundant calls invalidate the screen buffer
	SDL_Delay (milliseconds); 
} 


#endif
