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

//This is SSDL_Image.h.  Since it's a wrapper, it can handle whatever image formats
//  SDL2_Image supports.

//Essentially it's SDL_Texture* except that it has a destructor.  

#ifndef SSDL_IMAGE_H
#define SSDL_IMAGE_H

#include <memory>
#include <SDL_image.h>

inline
void SSDL_DestroyTexture(SDL_Texture*& p) //A workaround, because you need to call SDL_DestroyTexture on SDL_Textures,
                                          // not just delete
{
	if (p) 
	{ 
		SDL_DestroyTexture(p); 
		p = nullptr; 
	}
}

class SSDL_Image
{
public:
	SSDL_Image() : sdlTexture_(NULL)  {  }
	SSDL_Image (SDL_Texture* sdlTexture) : sdlTexture_ (NULL) 
	{ 
		sdlTexture_.reset(sdlTexture, SSDL_DestroyTexture);
	}
	SSDL_Image(const SSDL_Image& other) { *this = other;  }

	operator       SDL_Texture* ()		 { return sdlTexture_.get (); }
	operator       SDL_Texture* () const { return sdlTexture_.get (); }
	
	const SSDL_Image& operator= (const SSDL_Image& other)
	{
		sdlTexture_ = other.sdlTexture_; return *this;
	}
private:
	std::shared_ptr<SDL_Texture> sdlTexture_;	//yes, I do need to use SDL_Texture not SDL_Surface.  
								//Efficiency.  Wd be less efficient if we manipulate the
								// bits... but we won't.
};

SSDL_Image SSDL_LoadImage(const char* filename);

#endif