// Text class, for use with the SSDL library
//      -- from _C++20 for Lazy Programmers_

#ifdef _MSC_VER
#pragma warning (disable:4996) // Disable a warning about strcpy, etc.,
                               //   in Visual Studio
#endif

#include "text.h"

Text& Text::operator= (const Text& other)
{
    Shape::operator= (other);
	contents_.reset(copy(other.contents()));
    return *this;
}

char* Text::copy (const char* txt)
{
	char* result = new char[strlen(txt) + 1]; 
	strcpy(result, txt); 
	return result;
}
