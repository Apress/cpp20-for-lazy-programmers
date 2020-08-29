//MegaPowerup class: a Powerup for an arcade game
//	-- from _C++20 for Lazy Programmers_

#include "megaPowerup.h"

void MegaPowerup::animate ()
{
	if (!isAnimated ()) { draw (); return; }

	int whichColor = framesLeftInAnimation_ / FRAMES_PER_COLOR;
	SSDL_RenderClear(colors_[whichColor]);
	--framesLeftInAnimation_;
}