//Text class, for use with the SSDL library
//      -- from _C++ for Lazy Programmers_

#ifndef TEXT_H
#define TEXT_H

#include "shape.h"

class Text : public Shape
{
public:
    Text(const char* txt = "") { copy(txt); }
    Text(const Text& other) : Shape(other)
    {
        copy(other.contents_);
    }
    Text(Text&&      other) : Shape(std::move(other))
    {
        contents_ = other.contents_; other.contents_ = nullptr;
    }
    Text(int x, int y, const char* txt = "") : Shape(x, y)
    {
        copy(txt);
    }
    ~Text() override { if (contents_) delete contents_; }

    const Text& operator=(const Text& other);
    const Text& operator=(Text&&      other);

    const char* contents() const { return contents_; }

    void drawAux() const override
    {
        SSDL_RenderText(contents_, location().x_, location().y_);
    }

private:
    char* contents_;
    void copy(const char* txt);//used for copying contents
};

#endif
