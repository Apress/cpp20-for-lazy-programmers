// Text class, for use with the SSDL library
//       -- from _C++20 for Lazy Programmers_

#ifndef TEXT_H
#define TEXT_H

#include "shape.h"

class Text : public Shape
{
public:
    Text (const char* txt = "") { contents_.reset(copy(txt)); }
    Text (const Text& other) : Shape(other)
    {
        contents_.reset (copy (to_address (other.contents_))); 
    }
	Text (Text&&) = default;
    Text (int x, int y, const char* txt = "") : Shape(x, y)
    {
        contents_.reset(copy(txt));
    }
	~Text() override {}

    Text& operator= (const Text& other);
	Text& operator= (Text&&) = default; // returning Text& because that's the default

    const char* contents() const { return to_address (contents_); }

    void drawAux () const override
    {
        SSDL_RenderText(to_address (contents_), location().x_, location().y_);
    }

private:
	std::unique_ptr<char> contents_; 
    char* copy (const char* txt);// used for copying contents
};

#endif // TEXT_H
