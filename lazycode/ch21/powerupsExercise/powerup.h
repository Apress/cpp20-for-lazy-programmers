//Powerup class, for use with the DarkGDK library
//	A Powerup is something you click on to get points
//      It also has an animation it plays when you do this
//	 -- from _C++20 for Lazy Programmers_

#ifndef POWERUP_H
#define POWERUP_H

#include "circle.h"

class Powerup: public Circle
{
 public:
    enum {MAX_FRAMES_IN_ANIMATION = 60};

    Powerup () : framesLeftInAnimation_ (0) {}
    Powerup (const Powerup& c) : Circle (c),
	framesLeftInAnimation_ (c.framesLeftInAnimation_)
    {
	}

    Powerup (int x, int y, int theRadius, const char* txt="") : 
    Circle (x, y, theRadius, txt), framesLeftInAnimation_ (0)
    {
    } 

    Powerup& operator= (const Powerup& c) = delete;

    bool isAnimated     () const { return framesLeftInAnimation_ > 0; }
    void startAnimation () { framesLeftInAnimation_ = MAX_FRAMES_IN_ANIMATION; }

    void animate ();
    int  value   () const { return -1;  } //No, that's not right...
 protected:
    int framesLeftInAnimation_;	   //How many frames till animation is over?
};

#endif //POWERUP_H
