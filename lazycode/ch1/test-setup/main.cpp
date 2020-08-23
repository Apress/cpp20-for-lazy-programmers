// Program to test compiler, SDL, and SSDL 
//         -- from _C++20 for Lazy Programmers_

#include "SSDL.h"

int main(int argc, char** argv)
{
    // Initial window setup
    SSDL_SetWindowTitle ("Simple tester program");
    SSDL_SetWindowSize  (500, 375);

    // Load and play music
    SSDL_Music music = SSDL_LoadMUS ("Media/457729__razor5__boss-battle-2-0.wav");
    SSDL_VolumeMusic    (int (MIX_MAX_VOLUME*0.50)); 
    SSDL_PlayMusic      (music, SSDL_FOREVER);        

    // Show image
    const SSDL_Image BULLSEYE = SSDL_LoadImage ("media/bullseye.jpg"); 
    SSDL_RenderImage    (BULLSEYE, 0, 0);

	// Set font and color
	const SSDL_Font FONT = SSDL_OpenSystemFont ("georgiab.ttf",28);
	SSDL_SetFont           (FONT);
    SSDL_SetRenderDrawColor(BLACK);
	
    // Make a label in the middle, centered
    sout << " Success! You should see\n  the bullseye,\n";
    sout << "  read this message,\n";
	sout << "  and hear music.\n\n\n\n";
    sout << " Hit any key to end.\n";
	
	// End program
    SSDL_WaitKey();
    return 0;
}

