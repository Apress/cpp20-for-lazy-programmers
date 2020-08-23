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

//This is SSDL_Color.h, which provides SSDL_Color:  just like SDL_Color, except that it has constructors

#ifndef SSDL_COLOR_H
#define SSDL_COLOR_H

#include "SDL.h"

struct SSDL_Color : public SDL_Color
{
public:
    constexpr SSDL_Color (SDL_Color& other) : SDL_Color(other) {}
	//The : SDL_Color() below is for backward compatibility: C++20 doesn't require it, but
	// 6-7-2020 VS gave a warning
	constexpr SSDL_Color (int rIn = 0, int gIn = 0, int bIn = 0, int alpha = 255) : SDL_Color()
	{
		r = rIn; g = gIn; b = bIn; a = alpha;
	}
	constexpr SSDL_Color            (const SSDL_Color& other) = default;
	constexpr SSDL_Color& operator= (const SSDL_Color& other) = default;
	
	constexpr bool operator== (const SSDL_Color& other) const
	{
		return r == other.r && g == other.g&& b == other.b && a == other.a;
	}
};

//6-8-2020: I could replace this with inline constexpr, but for backward compatibility
// I won't just yet
extern const SSDL_Color BLACK, WHITE, RED, GREEN, BLUE;

inline constexpr SSDL_Color SSDL_CreateColor (int r, int g, int b, int a=255) { return SSDL_Color (r, g, b, a); }
#endif

