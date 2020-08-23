// Program to show, and move, the Olympics symbol
// It uses Circle, and a subclass of Shape called Text
//      -- from _C++20 for Lazy Programmers_

#include "circle.h"
#include "text.h"

// Used to test move ctor/=
Text makeTextToTestMoveCtor     () { Text t ("t");        return t; }
Circle makeCircleToTestMoveCtor () { Circle c(1,1,5,"c"); return c; }

int main (int argc, char** argv) 
{
    Text   t; t = makeTextToTestMoveCtor  (); // Test move ctors, =
    Circle c; c = makeCircleToTestMoveCtor();

    sout << "Use breakpoints in this program to ensure move ctors, = are being called.\n";

    SSDL_WaitKey();
    return 0;
}
