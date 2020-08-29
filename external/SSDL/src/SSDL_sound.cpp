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

//This is the Sound System.  It provides. all access to sounds.

#include "SSDL_exception.h"
#include "SSDL_sound.h"

//SSDL SoundSystem
SSDL_SoundSystem::SSDL_SoundSystem (int freq, Uint16 format, int channels, int chunkSize)
{
    //Start SDL2_Mixer. Apparently you don't really need to...
    //int soundsSupported = Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
    //if (!soundsSupported) throw SSDL_Exception();

	initializedOK_ = (Mix_OpenAudio(freq, format, channels, chunkSize) != -1); //8-7-2017
	if (!initializedOK_) SDL_ClearError(); //or we'll get this complaint later, when it makes no sense
	//I commented out all refs to throwing SSDL_Exception in SSDL_sound.*, so we could get by with this
	//It may not be the best solution.
	//Fix later.  8-7-2017

	//if (Mix_OpenAudio(freq, format, channels, chunkSize) == -1)
	//		throw SSDL_Exception (); 
}

Mix_Music* SSDL_Music::music_ = NULL;

void SSDL_PlaySound(const SSDL_Sound& sound, int repeats)
{
	int result = Mix_PlayChannel(sound, sound, repeats);
	if (SSDL_SoundSystem::Instance().initialized()) if (result == -1) throw SSDL_Exception();
	sound.setChannel(result);
}

void SSDL_FadeInSound(SSDL_Sound& sound, int repeats, int ms)
{
	int result = Mix_FadeInChannel(sound, sound, repeats, ms);
	if (SSDL_SoundSystem::Instance().initialized()) if (result == -1) throw SSDL_Exception();
	sound.setChannel(result);
}

void SSDL_PlaySoundTimed(SSDL_Sound& sound, int repeats, int ticks)
{
	int result = Mix_PlayChannelTimed(sound, sound, repeats, ticks);
	if (SSDL_SoundSystem::Instance().initialized()) if (result == -1) throw SSDL_Exception();
	sound.setChannel(result);
}

void SSDL_FadeInSoundTimed(SSDL_Sound& sound, int repeats, int ms, int ticks)
{
	int result = Mix_FadeInChannelTimed(sound, sound, repeats, ms, ticks);
	if (SSDL_SoundSystem::Instance().initialized()) if (result == -1) throw SSDL_Exception();
	sound.setChannel(result);
}
