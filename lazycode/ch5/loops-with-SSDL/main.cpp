// Program that quits when you move the mouse to the right side of the screen
//      -- from _C++20 for Lazy Programmers_

#include "SSDL.h" 

int main (int argc, char** argv)
{
    const int WHERE_IT_IS = SSDL_GetWindowWidth() / 2;
	char answer; // for the "Ready to rumble (Y/N)?" question below

    while (! SSDL_IsQuitMessage () && SSDL_GetMouseX() < WHERE_IT_IS)
    {
        SSDL_RenderClear ();
        SSDL_SetCursor (0, 0);
        sout << "Move mouse to right half of screen to continue.";
    }

	do
	{
		sout << "Ready to rumble (Y/N)? "; ssin >> answer;
	}
	while (!SSDL_IsQuitMessage () && answer != 'n' && answer != 'y');
	
	sout << "*** Rumble ***! Program complete.\n";
	
	SSDL_WaitKey();

    return 0;
}
