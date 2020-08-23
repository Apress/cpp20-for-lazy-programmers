//Program that quits when you move the mouse to the right side of the screen
//		-- from _C++ for Lazy Programmers_


#include "SSDL.h" 

int main (int argc, char** argv)
{
    const int WHERE_IT_IS = SSDL_GetWindowWidth() / 2;

    while (! SSDL_IsQuitMessage () && SSDL_GetMouseX() < WHERE_IT_IS)
    {
        SSDL_RenderClear ();
        SSDL_SetCursor (0, 0);
        sout << "Move mouse to right half of screen to end.";
    }

    return 0;
}
