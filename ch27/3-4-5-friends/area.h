//Class Area
// Each Area is read in as 
//   <north bound> <south bound> <west bound> <east bound> <name>
//   as in
//   8 2 1 4 Blovinia
// ...and that's what an Area contains

//       -- from _C++20 for Lazy Programmers_

#ifndef AREA_H
#define AREA_H

#include <iostream>
#include <string>

class Area
{
    friend bool furtherNorthThan (const Area& a, const Area& b);
    // friend bool furtherSouthThan . . .

public:
    static constexpr int NORTH = 0,
                         SOUTH = 1,
                         EAST  = 2,
                         WEST  = 3;
    static constexpr int DIRECTIONS = 4 ; //there are 4 directions

    Area () {}
    Area (const Area& other) : name_ (other.name_) { copyBoundingBox (other); }

    Area& operator= (const Area& other)
    {
        name_ = other.name_; copyBoundingBox (other); return *this;
    }

    void read  (std::istream& in)
    {
        in  >> boundingBox_ [NORTH]
            >> boundingBox_ [SOUTH]
            >> boundingBox_ [EAST ]
            >> boundingBox_ [WEST ]
            >> name_;
    }

    void print (std::ostream& out) const { out << name_; }

private:
    void copyBoundingBox (const Area& other); // called by copy ctor and =

    double boundingBox_[DIRECTIONS];
        // the northernmost, southernmost, etc., extent of our Area
        // bigger numbers are further north
        // bigger numbers are further east

    std::string name_;
};

inline
bool furtherNorthThan (const Area& a, const Area& b)
{
    return a.boundingBox_[Area::NORTH] > b.boundingBox_[Area::NORTH];
}

inline std::ostream& operator<< (std::ostream& out, const Area& foo)
{
    foo.print(out); return out;
}

inline std::istream& operator>> (std::istream& in, Area& foo)
{
    foo.read(in); return in;
}

#endif //AREA_H
