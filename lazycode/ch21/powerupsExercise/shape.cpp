//Shape class, for use with the SSDL library
//  -- from _C++20 for Lazy Programmers_

#ifdef _MSC_VER
#pragma warning (disable:4996) //Disable a warning about strcpy, etc.,
                               //  in Visual Studio
#endif

#include "shape.h"

//ctors
Shape::Shape (int x, int y, const char* text) 
{
    location_.x_ = x; location_.y_ = y; 
    copy (text);
}

Shape::Shape (const Shape& s) :
    location_ (s.location()),
    color_    (s.color   ())
{
    copy(s.description_);
}

Shape::Shape (Shape&& other)
{
    color_ = other.color(); location_ = other.location();
    description_ = other.description_; other.description_ = nullptr;
}

//operator=
Shape& Shape::operator= (const Shape& s)
{
    location_ = s.location(); 
    color_    = s.color   ();
    delete [] description_;   copy (s.description_);
    return *this;
}

Shape& Shape::operator= (Shape&&      s)
{
    location_    = s.location();
    color_       = s.color   ();
    delete[] description_;    
    description_ = s.description_; s.description_ = nullptr;
    return *this;
}

//copy, used by = and copy ctor
void Shape::copy (const char* text)
{
    description_ = new char [strlen (text) + 1];
    strcpy (description_, text);
}
