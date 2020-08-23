// Shape class, for use with the SSDL library
//      -- from _C++20 for Lazy Programmers_

#ifndef SHAPE_H
#define SHAPE_H

#include "SSDL.h"
#include "string.h"

struct Point2D  // Life would be easier if this were a full-fledged class
{               //   with operators +, =, etc. . . . but that
    int x_, y_; //   was left as an exercise.
};

class Shape
{
 public:
    Shape (int x = 0, int y = 0, const char* text = "");
    Shape (const Shape& other); 
    Shape (Shape&&      other) noexcept;
    virtual ~Shape() { }

    Shape& operator= (const Shape& s);
    Shape& operator= (Shape&&      s) noexcept;

    // color
    void  setColor(const SSDL_Color& c) { color_ = c;          }
    const SSDL_Color&  color   () const { return color_;       }

    // access functions
    const Point2D&  location   () const { return location_;    }
    const String&   description() const { return description_; }

    // drawing
    virtual void   drawAux() const = 0;
    void   draw   () const
    {
        SSDL_SetRenderDrawColor(color()); drawAux();
    }

    // moving
    void moveBy (int deltaX, int deltaY)
    {
        moveTo (location_.x_ + deltaX, location_.y_ + deltaY);
    }

    void moveTo (int x, int y)
    {
        location_.x_ = x;   // Point2D::operator= would help here!
        location_.y_ = y;
    }

 private:
    Point2D    location_;
    SSDL_Color color_;
    String     description_;  
};

#endif //SHAPE_H
