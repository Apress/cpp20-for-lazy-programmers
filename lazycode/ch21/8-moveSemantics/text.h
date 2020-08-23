// Text class, for use with the SSDL library
//      -- from _C++20 for Lazy Programmers_

#ifndef TEXT_H
#define TEXT_H

#include "shape.h"

class Text : public Shape
{
public:
    Text (const char* txt = "") : contents_(txt) {}  
    Text (const Text& other) : Shape(other), contents_ (other.contents_)
    {
    }
    Text (Text&& other) noexcept;
    Text (int x, int y, const char* txt = "") : Shape(x, y), contents_(txt)
    {
    }
    ~Text() override {  }

    Text& operator= (const Text& other);
    Text& operator= (Text&&      other) noexcept;

    const String& contents () const { return contents_; }

    void drawAux () const override
    {
        SSDL_RenderText(contents_, location().x_, location().y_);
    }

private:
    String contents_;
};

#endif //TEXT_H
