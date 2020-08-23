// Text class, for use with the SSDL library
//     -- from _C++20 for Lazy Programmers_

#ifdef _MSC_VER
#pragma warning (disable:4996) // Disable a warning about strcpy, etc.,
                               //   in Visual Studio
#endif

#include "text.h"

Text& Text::operator= (const Text& other)
{
    Shape::operator= (other);
    delete [] contents_; copy (other.contents ());
    return *this;
}

Text::Text(Text&& other) noexcept : Shape (std::move(other))
{
    contents_ = other.contents_; other.contents_ = nullptr;
}

Text& Text::operator= (Text&&      other) noexcept
{
    Shape::operator= (std::move(other));
    delete [] contents_;
    contents_ = other.contents_; other.contents_ = nullptr;
    return *this;
}

void Text::copy (const char* txt)
{
    contents_ = new char[strlen (txt)+1]; strcpy (contents_, txt); 
}
