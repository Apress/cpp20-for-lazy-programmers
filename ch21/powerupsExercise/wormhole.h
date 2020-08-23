//Wormhole class: a Powerup for an arcade game
//	 -- from _C++20 for Lazy Programmers_

#ifndef WORMHOLE_H
#define WORMHOLE_H

#include "powerup.h"

class Wormhole: public Powerup
{
public:
	Wormhole () : Powerup () {}
	Wormhole (const Wormhole& c) = delete;
	Wormhole (int x, int y, int theRadius, const char* txt="") : 
		Powerup (x, y, theRadius, txt) 
	{
	} 

	Wormhole& operator= (const Wormhole& c) = delete;

	void animate();

	int value () const { return 10; } //This powerup is worth 10 points!
};

#endif //WORMHOLE_H