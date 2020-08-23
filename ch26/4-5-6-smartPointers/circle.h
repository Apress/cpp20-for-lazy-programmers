//Circle class, for use with the SSDL library
//    -- from _C++20 for Lazy Programmers_

#ifndef CIRCLE_H
#define CIRCLE_H

#include <utility> //  for std::move
#include "shape.h"

class Circle: public Shape
{
 public:
    Circle () : radius_ (0)  {}
    Circle (const Circle& c) : Shape(c), radius_ (c.radius()) {}
    Circle (Circle&&      c) noexcept: Shape (std::move (c))
    { 
        radius_ = c.radius(); 
    }
    Circle (int x, int y, int theRadius, const char* txt="") : 
        Shape (x, y, txt), radius_ (theRadius) 
    {
    } 

    Circle& operator= (const Circle& c) 
    {
        Shape::operator=(c); radius_ = c.radius(); return *this;
    }
    const Circle& operator= (Circle&& c) noexcept
    {
        Shape::operator=(std::move(c)); radius_ = c.radius(); 
        return *this;
    }

    int radius () const { return radius_; }

    void drawAux() const override
    { 
        SSDL_RenderDrawCircle (location().x_, location().y_, radius()); 
    }

 private:
    int radius_; 
};

#endif // CIRCLE_H
