// Program to show, and move, the Olympics symbol
// It uses Circle, and a subclass of Shape called Text
//        -- from _C++20 for Lazy Programmers_

#include <vector>
#include "circle.h"
#include "text.h"

int main (int argc, char** argv) 
{
    SSDL_SetWindowSize (500, 300); // make smaller window

    // Create Olympics symbol
    std::vector<Shape*> olympicSymbol; 
    constexpr int RADIUS = 50;

    // consisting of five circles
    olympicSymbol.push_back (new Circle ( 50,  50, RADIUS));
    olympicSymbol.push_back (new Circle (150,  50, RADIUS));
    olympicSymbol.push_back (new Circle (250,  50, RADIUS));
    olympicSymbol.push_back (new Circle (100, 100, RADIUS));
    olympicSymbol.push_back (new Circle (200, 100, RADIUS));

    // plus a label
    olympicSymbol.push_back (new Text (150,150,"Games of the Olympiad"));

    // color those circles (and the label)
    SSDL_Color olympicColors[] = { BLUE,
                                   SSDL_CreateColor (0, 255, 255), // yellow
                                   BLACK, GREEN, RED, BLACK };
    for (unsigned int i = 0; i < olympicSymbol.size(); ++i)
        (*olympicSymbol[i]).setColor (olympicColors [i]);

    // do a game loop
    while (SSDL_IsNextFrame ())
    {
        SSDL_DefaultEventHandler ();

        SSDL_RenderClear (WHITE);   // clear the screen

        // draw all those shapes
        for (unsigned int i = 0; i < olympicSymbol.size(); ++i)
            (*olympicSymbol[i]).draw ();

        // move all those shapes
        for (unsigned int i = 0; i < olympicSymbol.size(); ++i)
            (*olympicSymbol[i]).moveBy (1, 1);
    }

    // done with our dynamic memory -- throw it back!
    for (unsigned int i = 0; i < olympicSymbol.size(); ++i)
        delete olympicSymbol [i];

    return 0;
}
