//String class
//      -- from _C++20 for Lazy Programmers_

#ifndef STRING_H
#define STRING_H

#include <cstring> // uses cstring functions all over
#include <iostream>

#ifdef _MSC_VER
#pragma warning (disable:4996) // Disable a warning about strcpy, etc.,
#endif                         //   in Visual Studio

class String 
{
public:
    static constexpr int BIGGEST_READABLE_STRING_PLUS_ONE   = 257; 
                      // biggest string we can read, incl '\0'
    static int biggestReadableString()
    { 
        return BIGGEST_READABLE_STRING_PLUS_ONE - 1; 
    }

    String (const char* other="") { copy(other);             }
    String (const String &other) : String (other.c_str())   {}
                      // a "delegated" ctor
    String (String&& other) noexcept   // move ctor
    {
        contents_ = other.contents_; 
        other.contents_ = nullptr;
    }
    ~String()         { if (contents_) delete [] contents_;  }

    // user-defined conversion functions
    const char* c_str() const { return contents_; }
    explicit operator const char* () const { return c_str(); }

    // other functions, not operators
    
    int       size () const { return (int) strlen (c_str()); }
                      //Inefficient! Is there a better way?
    bool operator! () const { return ! size();               } 

    // comparisons
    bool operator== (const String& other) const
    {
        return strcmp(c_str(), other.c_str()) == 0;
    }

#ifdef __cpp_impl_three_way_comparison   
    int operator<=> (const String& other) const
    {
        return strcmp(c_str(), other.c_str());
    }
#else // If the compiler isn't C++20 compliant, make our own compare ops
    bool operator< (const String& other) const
    {
        return strcmp(c_str(), other.c_str()) < 0;
    }
    bool operator> (const String& other) const
    {
        return strcmp(c_str(), other.c_str()) > 0;
    }
    bool operator<=(const String& other) const
    {
        return !(*this > other);
    }
    bool operator>=(const String& other) const
    {
        return !(*this < other);
    }
    bool operator!= (const String& other) const
    {
        return !(*this == other);
    }
#endif

    // assignment and concatenation

    String& operator=  (const String& other);
    String& operator=  (String&&      other) noexcept; //move =
    String& operator+= (const String& other);
    String  operator+  (const String& other) const
    {
        String result = *this; result += other; return result;
    }

    // [] and substring
    
    char  operator[] (int index) const { return contents_[index]; }
    char& operator[] (int index)       { return contents_[index]; }

    String operator () (int start, int finish) const;

    //I/O functions
    void  read  (std::istream& in ); 
    void  print (std::ostream& out) const{ out << c_str();        }
private:
    char* contents_;
    void  copy(const char* str);
};

inline
std::istream& operator>> (std::istream& in, String& foo)
{
    foo.read (in); return in;
}

inline
std::ostream& operator<< (std::ostream& out, const String& foo)
{
    foo.print(out); return out;
}
#endif //STRING_H
