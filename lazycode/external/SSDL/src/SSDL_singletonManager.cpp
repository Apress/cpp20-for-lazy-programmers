/*Simple SDL, a wrapper library for SDL.
  
  Copyright (C) 2020 Will Briggs.

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution. */

//This is the SingletonManager: it's used to be sure that these singleton objects
// are created before main starts and destructed after it ends. OK, we may go
// easy on the destructor stuff -- it's not crucial

#include <string>
#include <SDL_image.h>
#include "SSDL_display.h"
#include "SSDL_sound.h"
#include "SSDL_singletonManager.h"

void atexitHandler();

class SSDL_SingletonManager
{
public:
    SSDL_SingletonManager ()
    {
        atexit(atexitHandler);
        SSDL_Display::Instance();
        SSDL_SoundSystem::Instance();
    }
    std::string crashMessage;
};

static SSDL_SingletonManager singletonManagerInstance; 

void setCrashMessage(const std::string& msg) { singletonManagerInstance.crashMessage = msg; }

void atexitHandler()
{
    if (singletonManagerInstance.crashMessage.length()) //if there was a crash message...display it
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error", singletonManagerInstance.crashMessage.c_str(), NULL);

    //I comment out what's below because g++ on Unix has this freeze up on cleanup, and cleanup doesn't
    // matter as we're about to leave anyway. Maybe fix this someday.
 /*   if (SSDL_SoundSystem::Instance().initialized()) 
	{ 
		Mix_AllocateChannels(0); Mix_CloseAudio(); 
	}  
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_DestroyRenderer (SSDL_Display::Instance().sdlRenderer_); 
    SDL_DestroyWindow   (SSDL_Display::Instance().sdlWindow_); 
    SDL_Quit();*/
}


