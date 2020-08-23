//PowerupSet class: a Shape that is a vector of Powerup
//	-- from _C++20 for Lazy Programmers_

#ifndef POWERUPSET_H
#define POWERUPSET_H

#include <vector>
#include "powerup.h"

class PowerupSet //inheritance?
{
 public:
    PowerupSet (const char* text = "") : Shape (0, 0, text) {}
    PowerupSet (const PowerupSet&);

    void animate();
};

#endif
