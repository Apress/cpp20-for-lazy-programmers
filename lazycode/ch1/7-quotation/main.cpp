// Prints an excerpt from Sir Walter Scott's _The Lady of the Lake_
// 	-- from _C++20 for Lazy Programmers_

#include "SSDL.h" 

int main (int argc, char** argv)
{
    // Window setup
    SSDL_SetWindowTitle ("Hit any key to end"); 
    // Always tell user what's expected...

    // We'll be using Times New Roman font, bold... 
    //   so load it, and tell SSDL to use it
    const SSDL_Font FONT = SSDL_OpenSystemFont ("timesbd", 24);
    SSDL_SetFont (FONT);

    SSDL_SetCursor (0, 50);	// Start 50 pixels down

    // And now, the poem (or part of it)
    sout << "from The Lady of the Lake\n";
    sout << "\tby Sir Walter Scott\n\n";		
    // Tab over for author's name, then
    //  double space at the end of the line

    sout << "\"Tis merry, 'tis merry, in Fairy-land,\n";
    sout << "\tWhen fairy birds are singing,\n"; 
    sout << "When the court cloth ride by their monarch's side,\n";
    sout << "\tWith bit and bridle ringing...\"\n";

    // End when user hits a key
    SSDL_WaitKey ();

    return 0;
}

