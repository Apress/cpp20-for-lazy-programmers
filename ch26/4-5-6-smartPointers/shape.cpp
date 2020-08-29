// Shape class, for use with the SSDL library
//   -- from _C++20 for Lazy Programmers_

#ifdef _MSC_VER
#pragma warning (disable:4996) // Disable a warning about strcpy, etc.,
                               //   in Visual Studio
#endif

#include "shape.h"

// constructors
Shape::Shape (int x, int y, const char* text)
    : description_ (copy (text)) 
{
    location_.x_ = x; location_.y_ = y; 
}

Shape::Shape (const Shape& s) :
    location_    (s.location()),
    color_       (s.color   ()),
    description_ (copy (s.description_.get()))
{
}

// I no longer have to write the move constructor

//  ...or the move = operator

// operator=
Shape& Shape::operator= (const Shape& s)
{
    location_ = s.location(); 
    color_    = s.color   ();
    description_.reset (copy (s.description_.get()));
    return *this;
}

// copy, used by = and copy constructor
char* Shape::copy (const char* text)
{
    char* result = new char [strlen (text) + 1];
    strcpy (result, text);
    return result;
}
