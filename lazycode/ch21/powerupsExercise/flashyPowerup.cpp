//FlashyPowerup class: a Powerup for an arcade game
//	 -- from _C++20 for Lazy Programmers_

#include "flashyPowerup.h"

void FlashyPowerup::animate()
{
    if (!isAnimated ()) { draw (); return; }

    static int lastColor = 6;
    int whichColor = framesLeftInAnimation_ / FRAMES_PER_COLOR;
    if (whichColor != lastColor)
    {
        lastColor = whichColor;
    }
    SSDL_SetRenderDrawColor(colors_[whichColor]);
    drawAux();
    --framesLeftInAnimation_;
    if (framesLeftInAnimation_ == 0)
        lastColor = 6;
}
