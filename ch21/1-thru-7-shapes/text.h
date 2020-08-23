// Text class, for use with the SSDL library
//      -- from _C++20 for Lazy Programmers_

#ifndef TEXT_H
#define TEXT_H

#include "shape.h"

class Text : public Shape
{
public:
    Text (const char* txt = "") { copy(txt); }
    Text (const Text& other) : Shape(other)
    {
        copy(other.contents_);
    }
    Text (Text&& other) noexcept;
    Text (int x, int y, const char* txt = "") : Shape(x, y)
    {
        copy(txt);
    }
    ~Text() override { if (contents_) delete contents_; }

    Text& operator= (const Text& other);
    Text& operator= (Text&&      other) noexcept;

    const char* contents () const { return contents_; }

    void drawAux () const override
    {
        SSDL_RenderText (contents_, location().x_, location().y_);
    }

private:
    char* contents_;
    void copy (const char* txt);//used for copying contents
};

#endif //TEXT_H
