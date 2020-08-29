//Text class, for use with the SSDL library
//     -- from _C++ for Lazy Programmers_

#ifdef _MSC_VER
#pragma warning (disable:4996) //Disable a warning about strcpy, etc.,
                               //  in Visual Studio
#endif

#include "text.h"

const Text& Text::operator= (const Text& other)
{
    Shape::operator= (other);
    delete [] contents_; copy (other.contents ());
    return *this;
}

const Text& Text::operator= (Text&&      other)
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
