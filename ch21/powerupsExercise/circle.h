//Circle class, for use with the SSDL library
//   -- from _C++20 for Lazy Programmers_

#ifndef CIRCLE_H
#define CIRCLE_H

#include <cmath>   //for sqrt
#include "shape.h"

//These are needed by Circle::contains, below
template <typename T> inline T sqr(const T& thing) { return thing * thing; }

inline
float distance(float x1, float y1, float x2, float y2)
{
    return sqrt(sqr(x2 - x1) + sqr(y2 - y1));
}

class Circle: public Shape
{
 public:
    Circle () : radius_ (0)  {}
    Circle (const Circle& c) : Shape(c), radius_ (c.radius()) {}
    Circle (Circle&&      c) : Shape (std::move (c))
    { 
        radius_ = c.radius(); 
    }
    Circle (int x, int y, int theRadius, const char* txt="") : 
        Shape (x, y, txt), radius_ (theRadius) 
    {
    } 

    Circle& operator= (const Circle& c) 
    {
        Shape::operator=(c);            radius_ = c.radius(); 
        return *this;
    }
    Circle& operator= (Circle&&       c)
    {
        Shape::operator=(std::move(c)); radius_ = c.radius(); 
        return *this;
    }

    int radius () const { return radius_; }

    void drawAux() const override
    { 
        SSDL_RenderDrawCircle (location().x_, location().y_, radius()); 
    }

    bool contains(int x, int y) const
    {
        return distance((float)x, (float)y,
                        (float)location().x_, (float)location().y_) < radius_;
    }

private:
    int radius_; 
};

#endif
