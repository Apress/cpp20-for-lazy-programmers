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

//This is SSDL_Font.
//Since it's a wrapper, it is essentially TTF_Font*, only it has memory management.

#ifndef SSDL_FONT_H
#define SSDL_FONT_H

#include <memory>
#include <SDL_ttf.h>
#include <string>

//Because TTF_Font* must be destructed by TTF_CloseFont... and because shared_ptr
// instead calls a dtor... and TTF_Font won't allow inheritance from it...
// I am intentionally ignoring a possible memory leak.  May address this later. 10/10/19

class SSDL_Font
{
public:
        SSDL_Font(TTF_Font* font = NULL) : ttfFont_(NULL)
        {
                ttfFont_.reset(font, TTF_CloseFont);
        }
        SSDL_Font(const SSDL_Font& f) { *this = f; }

        const SSDL_Font& operator= (const SSDL_Font& f) { ttfFont_ = f.ttfFont_; return *this; }
        operator       TTF_Font* ()       { return ttfFont_.get(); }
        operator       TTF_Font* () const { return ttfFont_.get(); }

private:
        std::shared_ptr<TTF_Font> ttfFont_;
};

TTF_Font* SSDL_OpenFont           (const char* filename, int point);
        //This bit all relates to where to get fonts found on the system

//All this does is set up the full path for a font -- used in
// SSDL_display.*, SSDL_font.*

std::string SSDL_SystemFontPath(const char* fontPath, const char* filename);

TTF_Font* SSDL_OpenSystemFont  (const char* filename, int point);

        //What font is current?
TTF_Font* SSDL_GetCurrentFont();
void      SSDL_SetFont(TTF_Font* newFont);

        //Useful for adding (or not) ".ttf" to the end of filenames
bool matchFromEnd(const char* str, const char* substr);

#endif
