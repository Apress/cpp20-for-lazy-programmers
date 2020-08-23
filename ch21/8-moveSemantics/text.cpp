// Text class, for use with the SSDL library
//     -- from _C++20 for Lazy Programmers_

#ifdef _MSC_VER
#pragma warning (disable:4996) // Disable a warning about strcpy, etc.,
                               //   in Visual Studio
#endif

#include "text.h"

Text& Text::operator= (const Text& other)
{
    Shape::operator= (other); contents_ = other.contents_;
    return *this;
}

Text::Text (Text&& other) noexcept :
    Shape (std::move(other)), contents_(std::move(other.contents_)) // need that std::move to call String's move ctor
{
}

Text& Text::operator= (Text&&      other) noexcept
{
    Shape::operator= (std::move(other));
    //contents_ = other.contents_; // doesn't call String's move=
    contents_ = std::move(other.contents_); // but this does
    return *this;
}

