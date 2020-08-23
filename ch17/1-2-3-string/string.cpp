//class String, for char arrays
//      -- from _C++20 for Lazy Programmers_

#include <cstring>
#include "string.h"

using namespace std;

String& String::operator=  (const String& other)
{
    if (this == &other) return *this;      // never assign *this to itself
    if (contents_) delete[] contents_; copy(other.c_str()); 
    return *this;
}

void String::copy (const char* str)
{
    contents_ = new char[strlen(str) + 1]; // get new memory
	                                       // The +1 is room for final '\0'
    strcpy(contents_, str);                // copy contents over
}

String& String::operator+= (const String& other)
{
    char* oldContents = contents_;

    contents_ = new char [size() + other.size() + 1]; 
                                      // 1 extra space at the end for the null char

    strcpy (contents_, oldContents);  // copy old into new
    strcat (contents_, other.c_str());// append other contents

    delete [] oldContents;

    return *this;
}

String String::operator () (int start, int finish) const
{
    //This constructs the substring
    String result = *this;
    strcpy (result.contents_, contents_+start);
                // contents_+start is the char array that is
                //  "start" characters after contents_ begins
    result.contents_[finish-start+1] = '\0'; 
                // the number of chars in this sequence 
                //  is the difference plus 1

    return result;
}

void String::read  (std::istream& in)
{
    static char buffer [BIGGEST_READABLE_STRING_PLUS_ONE];
    in >> buffer;
    *this = buffer;
}
