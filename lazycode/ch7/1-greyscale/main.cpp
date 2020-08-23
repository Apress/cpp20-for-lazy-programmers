// Program to change some colors to greyscale
// 		-- from _C++20 for Lazy Programmers_ [wsb: test]

#include "SSDL.h"

// Prototypes go here

int average(int, int, int);
// Averages 3 ints
SSDL_Color greyscale(int r, int g, int b);
// Gets a greyscale color for a given r, g, b

int main(int argc, char** argv)
{
    sout << "Some colors you know turned to black-and-white. "
	 << "Hit any key to end.\n";

                    // By now the compiler knows that greyscale
                    //  takes 3 ints and returns an SSDL_Color, but doesn't
                    // know how to do the greyscale...

    SSDL_SetRenderDrawColor(greyscale(255, 255, 255));
    sout << "WHITE\n";
    SSDL_SetRenderDrawColor(greyscale(255,   0,   0));
    sout << "RED\n";
    SSDL_SetRenderDrawColor(greyscale(  0, 255,   0));
    sout << "GREEN\n";
    SSDL_SetRenderDrawColor(greyscale(  0,   0, 255));
    sout << "BLUE\n";
    SSDL_SetRenderDrawColor(greyscale(181, 125,  41));
    sout << "MARIGOLD\n";
    SSDL_SetRenderDrawColor(greyscale( 50, 205,  50));
    sout << "LIME GREEN\n";

    SSDL_WaitKey();

    return 0;
}

// Function bodies come after main, by convention

int average(int a, int b, int c)
// Averages 3 ints
{
    return (a + b + c) / 3;
}

SSDL_Color greyscale(int r, int g, int b)
// Gets a greyscale color for a given r, g, b
{
    int rgbAverage = average(r, g, b);

    SSDL_Color result
        = SSDL_CreateColor(rgbAverage, rgbAverage, rgbAverage);

    return result;
}

                    // ...and now the compiler has all the information 
                    //  it needs about greyscale (and anything else)
