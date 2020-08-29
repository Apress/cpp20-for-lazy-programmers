//MegaPowerup class: a Powerup for an arcade game
//	 -- from _C++20 for Lazy Programmers_

#pragma once

#include "powerup.h"

class MegaPowerup: public Powerup
{
public:
	enum {FRAMES_PER_COLOR = 10, MAX_COLORS=6};
	//should multiply to get Powerup::MAX_FRAMES_IN_ANIMATION = 60

	MegaPowerup () : Powerup () 
	{
		colors_[0] = colors_[2] = colors_[4] = BLACK;
		colors_[1] = colors_[3] = colors_[5] = WHITE;
	}
	MegaPowerup (const MegaPowerup& c) = delete;
	MegaPowerup (int x, int y, int theRadius, const char* txt="") : 
		Powerup (x, y, theRadius, txt) 
	{
		colors_[0] = colors_[2] = colors_[4] = BLACK;
		colors_[1] = colors_[3] = colors_[5] = WHITE;
	} 

	MegaPowerup& operator= (const MegaPowerup& c) = delete;
	void animate();
	int value () const { return 25; } //This powerup is worth 25 points!
private:
	SSDL_Color colors_[MAX_COLORS]; 
};
