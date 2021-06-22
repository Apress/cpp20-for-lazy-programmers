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

//This is a collection of functions for drawing shapes.  I'm trying to make it look a lot like SDL
// for training-wheels purposes.  General rule shall be:

//SSDL_function (args)
//means
//if (SDL_function (Renderer*, args)) fails, throw SSDL_Exception ()
//Exception:  if we're passing in an argument by const *, I pass it in by const &

//Note that SDL doesn't have a built-in method for drawing a circle -- so I'm adding one

#ifndef SSDL_DRAW_H
#define SSDL_DRAW_H

#include "SSDL_display.h"

inline
void SSDL_RenderDrawPoint (int x, int y)
{
	if (SDL_RenderDrawPoint (SSDL_Display::Instance (), x, y) < 0) throw SSDL_Exception ();
}

inline
void SSDL_RenderDrawPoints (const SDL_Point* points, int count)
{
	if (SDL_RenderDrawPoints (SSDL_Display::Instance (), points, count) < 0) throw SSDL_Exception ();
}

inline
void SSDL_RenderDrawLine (int x1, int y1, int x2, int y2)
{
	if (SDL_RenderDrawLine (SSDL_Display::Instance (), x1, y1, x2, y2) < 0) throw SSDL_Exception ();
}

inline
void SSDL_RenderDrawLines (const SDL_Point* points, int count)
{
	if (SDL_RenderDrawLines (SSDL_Display::Instance (), points, count) < 0) throw SSDL_Exception ();
}

inline
void SSDL_RenderDrawRect (int x, int y, int w, int h)
{
	SDL_Rect rect = {x, y, w, h};
	if (SDL_RenderDrawRect (SSDL_Display::Instance (), &rect) < 0) throw SSDL_Exception ();
}

inline
void SSDL_RenderDrawRect (const SDL_Rect& rect)
{
	if (SDL_RenderDrawRect (SSDL_Display::Instance (), &rect) < 0) throw SSDL_Exception ();
}

inline
void SSDL_RenderDrawRects (const SDL_Rect* rects, int count)
{
	if (SDL_RenderDrawRects (SSDL_Display::Instance (), rects, count) < 0) throw SSDL_Exception ();
}

inline
void SSDL_RenderFillRect (int x, int y, int w, int h)
{
	SDL_Rect rect = {x, y, w, h};
	if (SDL_RenderFillRect (SSDL_Display::Instance (), &rect) < 0) throw SSDL_Exception ();
}

inline
void SSDL_RenderFillRect (const SDL_Rect& rect)
{
	if (SDL_RenderFillRect (SSDL_Display::Instance (), &rect) < 0) throw SSDL_Exception ();
}

inline
void SSDL_RenderFillRects (const SDL_Rect* rects, int count)
{
	if (SDL_RenderFillRects (SSDL_Display::Instance (), rects, count) < 0) throw SSDL_Exception ();
}

struct SSDL_Circle
{
	int x, y, radius;
};

void SSDL_RenderDrawCircle  (int x, int y, int radius);
void SSDL_RenderFillCircle (int x, int y, int radius);
void SSDL_RenderDrawCircles (SSDL_Circle* circles, int count);
void SSDL_RenderFillCircles (SSDL_Circle* circles, int count);

#endif //SSDL_DRAW_H