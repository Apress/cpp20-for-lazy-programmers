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

//This is SSDL_Sprite.  A Sprite is a Texture (derived from an image) that also has a location.

#ifndef SSDL_SPRITE_H
#define SSDL_SPRITE_H

#include "SSDL_display.h"
#include "SSDL_image.h"

class SSDL_Sprite: public SSDL_Image
{
public:
	//5-19-2016 //SSDL_Sprite (SDL_Texture* t = NULL) 	{	setImage (t);		}
	SSDL_Sprite() { setImage(NULL); } //5-19-2016
	SSDL_Sprite (const SSDL_Sprite& other)	{	*this = other;		}
	SSDL_Sprite (const SSDL_Image& other)   {   setImage(other);	}
	const SSDL_Sprite& operator= (const SSDL_Sprite& other);

	void setImage(const SSDL_Image& t); //and adjust other fields to their defaults

	SDL_Rect destination() const;	//rectangle that's where it'll go on the screen
	SDL_Rect source     () const;	//rectangle that's where it's coming from in the image

	int  x					() const { return x_;		}
	int  y					() const { return y_;		}
	int  width				() const { return width_;	}
	int  height				() const { return height_;	}
	int  clipX				() const { return clipX_;	}
	int  clipY				() const { return clipY_;	}
	int  clipWidth			() const { return clipWidth_; }
	int  clipHeight			() const { return clipHeight_; }
	int  offsetX			() const { return offsetX_; }
	int  offsetY			() const { return offsetY_; }
	bool flipHorizontal		() const { return flipHorizontal_; }
	bool flipVertical		() const { return flipVertical_; }
	double angleOfRotation	() const { return angleOfRotation_; }

	int&  x					()       { return x_;		}
	int&  y					()       { return y_;		}
	int&  width				()       { return width_;	}
	int&  height			()       { return height_;	}
	int&  clipX				()       { return clipX_;	}
	int&  clipY				()       { return clipY_;	}
	int&  clipWidth			()       { return clipWidth_; }
	int&  clipHeight		()       { return clipHeight_; }
	int&  offsetX			()       { return offsetX_; }
	int&  offsetY			()       { return offsetY_; }
	bool& flipHorizontal	()       { return flipHorizontal_; }
	bool& flipVertical		()       { return flipVertical_; }
	double& angleOfRotation	()       { return angleOfRotation_; }

private:
	void zeroFields(); //used by ctors.  Sets everything in sight to a default of 0.

	//x and y are the position of the sprite's reference point (by default, its top left corner) on the screen
	//w and h are its width and height, on the screen
	int x_, y_, width_, height_;

	//offset is how far the reference point is, down and right, from the top left corner; default is 0,0
	int offsetX_, offsetY_;

	//clipX_, etc., are the upper left corner, width, and height of the part of the original image
	// that we'll be displaying.  This is useful if you have several frames in one image file
	// -- you can advance clip* to go between frames, and thus animate the sprite
	int clipX_, clipY_, clipWidth_, clipHeight_;

	bool flipHorizontal_, flipVertical_;
	double angleOfRotation_;

	//SDL_Rect boundingRectangle_; //what's its offset; and how much of the original image will we use?
};

inline void SSDL_SetSpriteImage       (SSDL_Sprite& s,  const SSDL_Image& img){ s.setImage (img);									}
inline void SSDL_SetSpriteLocation    (SSDL_Sprite& sprite, int x, int y){ sprite.x ()			= x; sprite.y ()			= y;}
inline void SSDL_SetSpriteSize        (SSDL_Sprite& sprite, int w, int h){ sprite.width ()		= w; sprite.height ()		= h;}
inline void SSDL_SetSpriteOffset      (SSDL_Sprite& sprite, int x, int y){ sprite.offsetX ()	= x; sprite.offsetY ()	= y;	}
inline void SSDL_SetSpriteClipLocation(SSDL_Sprite& sprite, int w, int h){ sprite.clipX ()	= w; sprite.clipY ()		= h;	}
inline void SSDL_SetSpriteClipSize	  (SSDL_Sprite& sprite, int w, int h){ sprite.clipWidth ()	= w; sprite.clipHeight ()	= h;}
inline void SSDL_SetSpriteRotation	  (SSDL_Sprite& sprite, double angle){ sprite.angleOfRotation () = angle;					}
inline void SSDL_SpriteFlipHorizontal (SSDL_Sprite& sprite)				 { sprite.flipHorizontal () = ! sprite.flipHorizontal ();}
inline void SSDL_SpriteFlipVertical   (SSDL_Sprite& sprite)				 { sprite.flipVertical () = ! sprite.flipVertical ();	}

inline int  SSDL_GetSpriteX				(const SSDL_Sprite& s) { return s.x() ; }
inline int  SSDL_GetSpriteY				(const SSDL_Sprite& s) { return s.y() ; }
inline int  SSDL_GetSpriteWidth			(const SSDL_Sprite& s) { return s.width() ; }
inline int  SSDL_GetSpriteHeight		(const SSDL_Sprite& s) { return s.height() ; }
inline int  SSDL_GetSpriteOffsetX		(const SSDL_Sprite& s) { return s.offsetX() ; }
inline int  SSDL_GetSpriteOffsetY		(const SSDL_Sprite& s) { return s.offsetY() ; }
inline int  SSDL_GetSpriteClipX			(const SSDL_Sprite& s) { return s.clipX() ; }
inline int  SSDL_GetSpriteClipY			(const SSDL_Sprite& s) { return s.clipY() ; }
inline int  SSDL_GetSpriteClipWidth		(const SSDL_Sprite& s) { return s.clipWidth() ; }
inline int	SSDL_GetSpriteClipHeight	(const SSDL_Sprite& s) { return s.clipHeight() ; }
inline bool SSDL_GetSpriteFlipHorizontal(const SSDL_Sprite& s) { return s.flipHorizontal() ; }
inline bool SSDL_GetSpriteFlipVertical	(const SSDL_Sprite& s) { return s.flipVertical(); }
inline double SSDL_GetSpriteRotation	(const SSDL_Sprite& s) { return s.angleOfRotation() ; }

void SSDL_RenderSprite(const SSDL_Sprite& sprite);

bool SSDL_SpriteHasIntersection(const SSDL_Sprite& aIn, const SSDL_Sprite& bIn);

#endif //SSDL_SPRITE_H