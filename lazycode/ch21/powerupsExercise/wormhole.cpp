//Wormhole class: a Powerup for an arcade game
//	-- from _C++20 for Lazy Programmers_

#include "wormhole.h"

void Wormhole::animate ()
{
	if (!isAnimated ()) { draw (); return; }

	//If we're doing animation, set the color; 
	//  then draw a circle.  The size changes with 
	//  framesLeftInAnimation
	SSDL_SetRenderDrawColor (color ());
	SSDL_RenderDrawCircle (location ().x_, location ().y_, (int)
		std::fmax(0, radius () - framesLeftInAnimation_));

	--framesLeftInAnimation_;
}
