// A struct Color and associated constants and functions
//       -- from _C++20 for Lazy Programmers_

#ifndef COLOR_H
#define COLOR_H

#include "SSDL.h"

namespace Palette
{
    struct Color
    {
        constexpr Color (double r = 0, double g = 0, double b = 0)
            : red_(r), green_(g), blue_(b), brightness_((r+g+b)/3)
        {
        }
        constexpr Color (const Color&)              = default;
        constexpr Color& operator= (const Color& c) = default;

        constexpr Color complement() const
        {
            return Color (1.0 - red_, 1.0 - green_, 1.0 - blue_);
        }
        
        double red_, green_, blue_; // Each ranges 0.0-1.0. More fine shades than
                                    //   if we used ints 0-255
        double brightness_;
    };

    // Function to convert a Color to an SSDL_Color
    constexpr SSDL_Color color2SSDL_Color(const Color& c)
    {
        return SSDL_Color(int(c.red_ * 255),
            int(c.green_ * 255),
            int(c.blue_ * 255));
    }

    inline constexpr Color BLACK (0.0,0.0,0.0), RED (1.0,0.0,0.0),
                           GREEN (0.0,1.0,0.0), BLUE(0.0, 0.0, 1.0),
                           FUSCHIA (1.0,0.0,1.0);

    inline constexpr
        Color COLORS[] = {Color (0.80,0.53,0.60), // puce
                          Color (1.00,0.99,0.82), // cream
                          Color (0.94,0.92,0.84)};// eggshell
}
#endif // COLOR_H
