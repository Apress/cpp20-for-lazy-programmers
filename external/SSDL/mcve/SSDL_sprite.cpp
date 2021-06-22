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


#include "SSDL_sprite.h"

const SSDL_Sprite& SSDL_Sprite::operator= (const SSDL_Sprite& other)
{
	x_ = other.x_;				y_ = other.y_;
	width_ = other.width_;		height_ = other.height_;
	clipX_ = other.clipX_;		clipY_ = other.clipY_;
	clipWidth_ = other.clipWidth_; clipHeight_ = other.clipHeight_;
	offsetX_ = other.offsetX_;	offsetY_ = other.offsetY_;

	angleOfRotation_= other.angleOfRotation_;
	flipVertical_	= other.flipVertical_;
	flipHorizontal_ = other.flipHorizontal_;

	SSDL_Image::operator= (other);

	return *this;
}

void SSDL_Sprite::zeroFields()
{
	x_ = y_ = 0;
	clipX_ = clipY_ = 0;
	offsetX_ = offsetY_ = 0;

	clipWidth_ = clipHeight_ = 0;

	width_ = clipWidth_;
	height_ = clipHeight_;

	angleOfRotation_ = 0.0;
	flipHorizontal_ = flipVertical_ = false;
}

void SSDL_Sprite::setImage(const SSDL_Image& t)  
{
	SSDL_Image::operator= (t);

	zeroFields();

	if (t)
		SSDL_QueryImage(t, clipWidth_, clipHeight_);

	width_ = clipWidth_;
	height_ = clipHeight_;
}

SDL_Rect SSDL_Sprite::destination()	const	//rectangle that's where it'll go on the screen
{
	SDL_Rect result = { x_, y_, width_, height_ };
	result.x -= offsetX();		//apply offset
	result.y -= offsetY();
	return result;
}

SDL_Rect SSDL_Sprite::source() const		//rectangle that's where it's coming from in the image
{
	SDL_Rect result = { clipX_, clipY_, clipWidth_, clipHeight_ };
	return result;
}

void SSDL_RenderSprite(const SSDL_Sprite& sprite)
{
	SDL_Rect destination = sprite.destination();
	SSDL_RenderImageEx(sprite, sprite.source(), destination, sprite.angleOfRotation(),
		(SDL_RendererFlip)((int(sprite.flipHorizontal()) * SDL_FLIP_HORIZONTAL) | (int(sprite.flipVertical()) * SDL_FLIP_VERTICAL)));
}

bool SSDL_SpriteHasIntersection(const SSDL_Sprite& aIn, const SSDL_Sprite& bIn)
{
	SDL_Rect aDest = aIn.destination(), bDest = bIn.destination();
	return (SDL_HasIntersection(&aDest, &bDest) != SDL_FALSE);
}
