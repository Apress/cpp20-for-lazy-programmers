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

//This is a collection of functions for drawing shapes.

#include <cmath> 
#include "SSDL_draw.h"

#define PI 3.14159

//http://content.gpwiki.org/index.php/SDL:Tutorials:Drawing_and_Filling_Circles has another method
//it may look better but it's incomprehensible

void SSDL_RenderFillCircle (int xc, int yc, int radius)
{
	for (int dy = -radius; dy <= radius; ++dy)
	{
		//x^2 + y^2 = r^2, so x = sqrt (r^2 - y^2)
		int dx = int (sqrt (radius*radius - dy * dy) + 0.5);
		SSDL_RenderDrawLine (xc-dx, yc+dy, xc+dx, yc+dy);
	}
}

void SSDL_RenderDrawCircle (int xc, int yc, int radius)
{
	//What angleIncrement should we use?  one that subtends about a pixel
	//sin(angleIncrement) = 1 / radius
	double angleIncrement = asin (1.0/radius);

	for (double angle = 0; angle <= 2*PI; angle+= angleIncrement)
	{
		int y = int (radius * sin (angle) + 0.5);
		int x = int (radius * cos (angle) + 0.5);
		SSDL_RenderDrawPoint (xc+x, yc+y);
	}
}

void SSDL_RenderDrawCircles (SSDL_Circle* circles, int count)
{
	for (int i = 0; i < count; ++i)
		SSDL_RenderDrawCircle (circles[i].x, circles[i].y, circles[i].radius);
}

void SSDL_RenderFillCircles (SSDL_Circle* circles, int count)
{
	for (int i = 0; i < count; ++i)
		SSDL_RenderFillCircle (circles[i].x, circles[i].y, circles[i].radius);
}
