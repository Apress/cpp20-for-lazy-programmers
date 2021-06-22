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

#ifndef SSDL_IO_H
#define SSDL_IO_H 

typedef SDL_Event SSDL_Event; //simple renaming -- now you can use either

bool SSDL_IsKeyPressed (SDL_Keycode whichKey);

inline int SSDL_GetMouseClick (){ return SDL_GetMouseState (NULL, NULL);		  }
inline int SSDL_GetMouseX()		{ int x, y; SDL_GetMouseState (&x, &y); return x; }
inline int SSDL_GetMouseY()		{ int x, y; SDL_GetMouseState (&x, &y); return y; }

void SSDL_WaitEvent (Uint32 eventType, SDL_Event& event);
//Note that these wait functions also stop waiting if you get a SDL_QUIT event.
//Should I also stop waiting if someone hits Esc?  I could do that, but make it
// conditional (you can turn it off)
//Note:  You CANNOT OR events together -- they are not distinct bits!

int         SSDL_WaitMouse();
SDL_Keycode SSDL_WaitKey  (); //SDL_Keycode is SDL's virtual key rep. *Sometimes* casting to char gets you what you hit

void SSDL_ToggleEscapeIsQuit ();

inline int SSDL_PollEvent (SDL_Event& event) { return SDL_PollEvent (&event); }

void SSDL_DefaultEventHandler ();

void SSDL_CheckForQuitMessages(const SDL_Event& sdlEvent);

#endif