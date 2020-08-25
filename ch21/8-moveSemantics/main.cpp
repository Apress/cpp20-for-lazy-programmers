// Program to show, and move, the Olympics symbol
// It uses Circle, and a subclass of Shape called Text
//      -- from _C++20 for Lazy Programmers_

#include "circle.h"
#include "text.h"

// Used to test move ctor/=
Text   makeTextToTestMove   () { Text t ("t");        return t; }
Circle makeCircleToTestMove () { Circle c(1,1,5,"c"); return c; }

int main (int argc, char** argv) 
{
    Text   t; t = makeTextToTestMove  (); // Test move ctors, =
    Circle c; c = makeCircleToTestMove();

    sout << "Use breakpoints in this program to ensure move ctors, = are being called.\n";
    sout << "Hit a key to end.\n";

    SSDL_WaitKey();
    return 0;
}
