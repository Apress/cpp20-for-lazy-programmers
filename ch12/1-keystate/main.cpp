// Program to identify some keys, and mouse buttons, being pressed
//       -- from _C++20 for Lazy Programmers_

#include "SSDL.h"

int main (int argc, char** argv)
{
    // Pressing many keys at once may confuse the keyboard.
    // Also, on some keyboards, hold down Fn key to
    //   use a Function key

    while (SSDL_IsNextFrame ())
    {
        SSDL_DefaultEventHandler ();

        // Display
        SSDL_RenderClear ();    // Clear the screen
        SSDL_SetCursor (0, 0);  // And start printing at the top

        sout << "What key are you pressing? ";
        sout << "Control, Shift, Caps lock, space, F1?\n";

        if (SSDL_IsKeyPressed (SDLK_LCTRL))   sout << "Left ctrl ";
        if (SSDL_IsKeyPressed (SDLK_RCTRL))   sout << "Right ctrl ";
        if (SSDL_IsKeyPressed (SDLK_LSHIFT))  sout << "Left shift ";
        if (SSDL_IsKeyPressed (SDLK_RSHIFT))  sout << "Right shift ";
        if (SSDL_IsKeyPressed (SDLK_CAPSLOCK))sout << "Caps lock ";
        if (SSDL_IsKeyPressed (SDLK_SPACE))   sout << "Space bar ";
        if (SSDL_IsKeyPressed (SDLK_F1))      sout << "F1 ";
        if (SSDL_IsKeyPressed (SDLK_ESCAPE))  break;
        sout << "\n";

        if (SSDL_GetMouseClick () == SDL_BUTTON_LMASK)
            sout << "Left mouse button down\n";
        if (SSDL_GetMouseClick () == SDL_BUTTON_RMASK)
            sout << "Right mouse button down\n";

        sout << "(Hit Esc to exit.)";
    }

    return 0;
}
