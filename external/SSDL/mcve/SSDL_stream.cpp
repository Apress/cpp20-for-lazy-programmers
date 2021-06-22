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

//This is SSDL stream I/O, culminating in sin (which reads from kbd, prints chars to output, and reads in text)
// and sout (which prints to screen)

#include "SSDL_display.h"
#include "SSDL_stream.h"
#include "SSDL_io.h"

using namespace std;

static SSDL_BufferOut <char> ssdlBufferOut;
std::ostream sout (&ssdlBufferOut);

static SSDL_BufferIn <char> ssdlBufferIn;
istream ssin (&ssdlBufferIn);

void SSDL_StreamIOSystem::eraseCharAtCursor (char c) //should not be called after changing font... odd things'll happen
{
	SDL_Surface* result = SDL_CreateRGBSurface (0, 1, 1, 4, 0, 0, 0, 1);
//	SDL_Rect rect = {0, 0, 1, 1};

	//erase that last char by replacing with background color
	SDL_Rect newRect;
	newRect.x = cursorX(); newRect.y = cursorY(); 
	newRect.w = SSDL_Display::Instance().advance(c); 
	newRect.h = SSDL_Display::Instance().fontLineSkip();
	Uint8 r, g, b, a;
	SDL_GetRenderDrawColor (SSDL_Display::Instance(), &r, &g, &b, &a); //save current draw 
	SSDL_Color background_ = SSDL_Display::Instance().background ();
	SDL_SetRenderDrawColor (SSDL_Display::Instance(), background_.r, background_.g, background_.b, background_.a); 
	SDL_RenderFillRect (SSDL_Display::Instance(), &newRect);
	SDL_SetRenderDrawColor (SSDL_Display::Instance(), r, g, b, a); //Restore prev draw color

	SDL_FreeSurface (result);
}

/*
This code is not currently used, but I'll leave it in, in case it turns up useful later.

bool isPrintable(SDL_Scancode scancode, SDL_Keymod mod) 
{
	if (SDL_SCANCODE_A <= scancode && scancode <= SDL_SCANCODE_0) //if it's alphanumeric...
		return true;
	if (SDL_SCANCODE_SPACE <= scancode && scancode <= SDL_SCANCODE_SLASH) //or from a bunch of punctuation keys...
		return true;
	if (isNumLockOn(mod) && isNumLockKey(scancode))
		return true;
	return false;
}

char myToupper(char c) 
{
	if (isalpha(c)) return toupper(c);
	switch (c)
	{
	case '1': return '!';
	case '`': return '~';
	case '2': return '@';
	case '3': return '#';
	case '4': return '$';
	case '5': return '%';
	case '6': return '^';
	case '7': return '&';
	case '8': return '*';
	case '9': return '(';
	case '0': return ')';
	case '-': return '_';
	case '=': return '+';
	case '[': return '{';
	case ']': return '}';
	case '\\': return '|';
	case ';': return ':';
	case '\'': return '\"';
	case ',': return '<';
	case '.': return '>';
	case '/': return '?';
	default: return c;
	}
}
*/
