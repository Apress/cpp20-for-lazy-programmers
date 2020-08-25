// Program to play sounds 
//      -- from _C++20 for Lazy Programmers_

#include "SSDL.h"

int main(int argc, char** argv)
{
    // Initial window setup
    SSDL_SetWindowTitle("Simple sound example");

    // Load our media
    SSDL_Music music = SSDL_LoadMUS ("Media/457729__razor5__boss-battle-2-0.wav");
    SSDL_Sound bell  = SSDL_LoadWAV ("Media/321530__robbo799__church-bell.wav");

    // Start the music
    SSDL_VolumeMusic (MIX_MAX_VOLUME/2);  // play music at half volume, 
                                          //   because...that was LOUD.
    SSDL_PlayMusic (music, SSDL_FOREVER); // ...looping continuously
                                          // SSDL_FOREVER means -1

    sout << "Hit a key to hear the bell.\n";
    SSDL_WaitKey();
    SSDL_PlaySound(bell);

    sout << "Hit another key to end.\n";
    SSDL_WaitKey();

    return 0;
}

