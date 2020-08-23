//Shape class, for use with the SSDL library
//  -- from _C++20 for Lazy Programmers_

#ifdef _MSC_VER
#pragma warning (disable:4996) // Disable a warning about strcpy, etc.,
                               //   in Visual Studio
#endif

#include "shape.h"

// ctors
Shape::Shape (int x, int y, const char* text) : description_(text)
{
    location_.x_ = x; location_.y_ = y; 
}

Shape::Shape (const Shape& s) :
    location_ (s.location_), color_ (s.color_), description_ (s.description_)
{
}

Shape::Shape (Shape&& other) noexcept :
    color_ (other.color_), location_ (other.location_),
    description_ (std::move(other.description_)) // need that std::move to call String's move ctor
{
}

// operator=
Shape& Shape::operator= (const Shape& s)
{
    location_ = s.location_; 
    color_    = s.color_;
    description_ = s.description_;
    return *this;
}

Shape& Shape::operator= (Shape&&      s) noexcept
{
    location_    = s.location_;
    color_       = s.color_;
    //description_ = s.description_; // doesn't call String's move ctor
    description_ = std::move (s.description_); // but this does
    return *this;
}
