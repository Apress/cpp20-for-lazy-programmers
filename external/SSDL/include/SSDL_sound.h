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

#ifndef SSDL_SOUND_H
#define SSDL_SOUND_H

#include <vector>
#include <memory> //for shared_ptr
#include "SDL.h" //for Uint32?
#include "SDL_mixer.h"
#include "SSDL_exception.h"

//An SSDL_SoundSystem is the thing which calls Mix_OpenAudio on startup and Mix_CloseAudio on closing
//It's there so we can remember to declare it once, rather than remembering to call Mix_OpenAudio w/
// all its paramemters and remember to call Mix_CloseAudio.

//It's OK to alter the default arguments to the ctor and recompile.

//  Discussion of best arguments:  It seems conventional for the first argument to be some multiple of
//  220005 Hz.  I found 44010 to introduce static.
//  Changing chunkSize up or down by a factor of 2 showed no noticeable effect

//  Changing the format to AUDIO_U8 or AUDIO_S8 didn't sound good
//  Changing it to AUDIO_U16LSB, AUDIO_S16LSB, AUDIO_U16MSB, and AUDIO_S16MSB showed no change I could tell

//WSB: if I use pointer rather than static local var, I can initialize it inline (I think)
class SSDL_SoundSystem
{
public:
	static SSDL_SoundSystem& Instance (int freq = 88020, Uint16 format = MIX_DEFAULT_FORMAT,
		int channels = MIX_DEFAULT_CHANNELS, int    chunkSize = 4096)
		//This function's defaults are mentioned in C++/C++20 for Lazy Programmers, Appendix A,
		//   so don't dump them
	{
		static SSDL_SoundSystem myInstance(freq, format, channels, chunkSize); 
		return myInstance;
	}
	bool initialized() const { return initializedOK_;  }

	SSDL_SoundSystem                  (const SSDL_SoundSystem&) = delete;//don't allow use of copy ctor
	const SSDL_SoundSystem& operator= (const SSDL_SoundSystem&) = delete;//or operator=
private:
	SSDL_SoundSystem (int freq    =MIX_DEFAULT_FREQUENCY, Uint16 format   =AUDIO_U8,
					int channels=MIX_DEFAULT_CHANNELS,  int    chunkSize=4096);
	//MIX_DEFAULT_CHANNELS == 2 == stereo.  1 is mono.  
	//http://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_11.html says it's got nothing to do w channels

	//Special thanks to whoever wrote http://sdl.beuc.net/sdl.wiki/Mix_OpenAudio ,
	//which said that setting format to AUDIO_S16, AUDIO_U16, AUDIO_S16LSB, or AUDIO_U16LSB
	// causes the horrible staticky sound I was hearing.  And the usual default format,
	// MIX_DEFAULT_FORMAT, equalled one of these!  I tried AUDIO_U8 and it worked.

	//Here's a decent discussion of how to choose freq; you can also play with chunk size
	//It's a little old, so I went with a bigger freq (tech will have improved) -- 6-10-2019
	//http://osdl.sourceforge.net/main/documentation/rendering/SDL-audio.html#size

	~SSDL_SoundSystem()
	{ 
		//if (initializedOK_) 
		//{ 
		//	Mix_AllocateChannels(0); Mix_CloseAudio(); 
		//}  
		//Mix_Quit();
	} //deallocate channels, close audio

	bool initializedOK_ = false; //8-7-2017
};

//An SSDL_SoundSystemInitializer is there to make it easy  to change the paramters to SDL_Mixer's
//  Mix_OpenAudio, without messing with SSDL code.  
//  It is completely optional -- just there if the programmer wants to tweak Mix_OpenAudio's arguments.

//  You call it thus, after includes in the main program, but before ANYTHING else gets done.  
//  SSDL_SoundSystemInitialize initializer(88020, MIX_DEFAULT_FORMAT,2, 4096); -- alter args as you like
//  If you call it twice, it should ignore the second call. Best call it once, in the file w/ main program.

//  Discussion of best arguments:  It seems conventional for the first argument to be some multiple of
//  220005 Hz.  I found 44010 to introduce static.
//  Changing chunkSize up or down by a factor of 2 showed no noticeable effect

//  Changing the format to AUDIO_U8 or AUDIO_S8 didn't sound good
//  Changing it to AUDIO_U16LSB, AUDIO_S16LSB, AUDIO_U16MSB, and AUDIO_S16MSB showed no change I could tell

class SSDL_SoundSystemInitializer
{
public:
	SSDL_SoundSystemInitializer(int freq = 88020, Uint16 format = MIX_DEFAULT_FORMAT,
		int channels = MIX_DEFAULT_CHANNELS, int    chunkSize = 4096)
	{
		SSDL_SoundSystem::Instance(freq, format, channels, chunkSize);
	}
};

//An SSDL_Sound is essentially a wrapper for SDL_Mixer's Chunk struct
//It's used for sound effects.
//Warning:  memory problems, including crashing, will occur if more than one SSDL_Sound shares its chunk
//This is possible but unlikely
//Making ptr unique would not be sufficient protection as you could get copy it to a regular pointer
//I will leave this up to the programmer

class SSDL_Sound
{
public:
	enum {NO_CHANNEL = -1};
	SSDL_Sound (Mix_Chunk* soundChunk = NULL) : channel_ (NO_CHANNEL), chunk_ (NULL)
	{
		SSDL_SoundSystem::Instance (); //so that it's created before I try to do anything with it
		chunk_.reset(soundChunk, Mix_FreeChunk);
	}
	SSDL_Sound(const SSDL_Sound& s) { *this = s; }

	const SSDL_Sound& operator= (const SSDL_Sound& s)
	{
		chunk_ = s.chunk_; return *this;
	}
	~SSDL_Sound() 
	{	
		//if (soundInitialized) { Mix_AllocateChannels(0); Mix_CloseAudio(); }
		//Mix_Quit();
	}

	operator int        () const	{ return channel_;	    }
	operator Mix_Chunk* () const	{ return chunk_.get();	}

	void setChannel (int c)const    { channel_ = c;			}

private:
		//SDL_Mixer uses "channels" for its sound effects.  Each sound has its own channel, which is an int
	mutable int					channel_;	//the channel the sound will play on

	std::shared_ptr<Mix_Chunk>	chunk_;
};

inline Mix_Chunk* SSDL_LoadWAV (const char* file)
{
	if (!SSDL_SoundSystem::Instance().initialized()) return NULL;
	SSDL_SoundSystem::Instance();				//start the sound system BEFORE any calls to the mixer
	Mix_Chunk* result = Mix_LoadWAV (file);
	if (!result)
		throw SSDL_Exception(); 

	return result;
}

inline int SSDL_VolumeSound (int channel, int volume=MIX_MAX_VOLUME) { return Mix_Volume (channel, volume); }
inline int SSDL_VolumeAllSounds (int volume=MIX_MAX_VOLUME) { return Mix_Volume (-1, volume); }

void SSDL_PlaySound       (const SSDL_Sound& sound, int repeats = 0);
void SSDL_FadeInSound     (      SSDL_Sound& sound, int repeats, int ms);
void SSDL_PlaySoundTimed  (      SSDL_Sound& sound, int repeats, int ticks);
void SSDL_FadeInSoundTimed(      SSDL_Sound& sound, int repeats, int ms, int ticks);

inline void		SSDL_PauseSound (int channel)	{ Mix_Pause (channel); }
inline void		SSDL_PauseAllSounds ()		    { Mix_Pause (-1); }
inline void		SSDL_ResumeSound (int channel)	{ Mix_Resume (channel); }
inline void		SSDL_ResumeAllSounds ()		    { Mix_Resume (-1); }
inline void		SSDL_HaltSound (int channel)	{ Mix_HaltChannel (channel); }
inline void		SSDL_HaltAllSounds ()		    { Mix_HaltChannel (-1); }

inline bool		SSDL_SoundPlaying (int channel)	{ return Mix_Playing (channel) != 0; }
inline bool		SSDL_SoundPaused (int channel)	{ return Mix_Paused  (channel) != 0; }
inline Mix_Fading SSDL_SoundFadingChannel (int channel) { return Mix_FadingChannel (channel); }

inline int		SSDL_ExpireSound (int channel, int ms)		{ return Mix_ExpireChannel (channel, ms); }
inline int		SSDL_ExpireAllSounds (int ms)				{ return Mix_ExpireChannel (-1, ms); }
inline int		SSDL_FadeOutSound (int channel, int ms)		{ return Mix_FadeOutChannel (channel, ms); }
inline int		SSDL_FadeOutAllSounds (int ms)				{ return Mix_FadeOutChannel (-1, ms); }

//An SSDL_Music is essentially a wrapper for SDL_Mixer's Mix_Music.
//Note that music (Mix_Music) and sound effects (Mix_Chunk) are different things
// done differetnly in SDL_Mixer.

//You can only have one of it.  But I don't want it to be a conventional singleton
// class, because it makes sense for a user to declare it (so we need the ctor available)
//So I'll just make the only data member static.  This way you can declare as many
// SSDL_Musics as you like...but they're all the same one.

class SSDL_Music
{
public:
	SSDL_Music (Mix_Music* m = NULL)
	{
		SSDL_SoundSystem::Instance (); //so that it's created before I try to do anything with it
		setTo (m);
	}
	SSDL_Music(SSDL_Music&& other) { music_ = other.music_; other.music_ = nullptr; }

	const SSDL_Music& operator= (const SSDL_Music&) = delete;

	const SSDL_Music& operator= (Mix_Music* m)
	{
		setTo (m);
		return *this;
	}
	~SSDL_Music () { if (music_) Mix_FreeMusic (music_); music_ = NULL; }

	operator       Mix_Music* () const { return music_; }
	operator       Mix_Music* ()       { return music_; }

	void setTo (Mix_Music* m)
	{
		if (music_) Mix_FreeMusic (music_);		//throw back the old music; get new one
		music_ = m;
	}
private:
	static Mix_Music* music_;

	SSDL_Music(const SSDL_Music&) 
	{ 
		throw SSDL_Exception("SSDL_Music copy ctor should never be called.");
		//Why  this?  With g++, some implementations, if I delete the copy ctor, it complains that this is needed.  
	    // In gdb, it never calls it.  For now, I'll throw this exception.  
	}
};

enum {SSDL_FOREVER=-1};

inline Mix_Music* SSDL_LoadMUS (const char* filename)
{
	if (!SSDL_SoundSystem::Instance().initialized()) return NULL;
	SSDL_SoundSystem::Instance();				//start the sound system BEFORE any calls to the mixer
	Mix_Music* result = Mix_LoadMUS (filename);
	if (! result) throw SSDL_Exception ();	//8-7-2017
	return result;
}


inline void SSDL_PlayMusic (Mix_Music* m, int loops=SSDL_FOREVER) 
{ 
	if (!SSDL_SoundSystem::Instance().initialized()) return;
	if (Mix_PlayMusic (m, loops) < 0) throw SSDL_Exception (); 
}
inline void SSDL_FadeInMusic (Mix_Music* m, int loops, int ms) 
{
	if (!SSDL_SoundSystem::Instance().initialized()) return;
	if (Mix_FadeInMusic (m, loops, ms) < 0) throw SSDL_Exception (); 
}
inline void SSDL_FadeInMusicPos (Mix_Music* m, int loops, int ms, double pos) 
{ 
	if (!SSDL_SoundSystem::Instance().initialized()) return;
	if (Mix_FadeInMusicPos (m, loops, ms, pos) < 0) throw SSDL_Exception ();
}
inline int  SSDL_VolumeMusic (int volume=-1) { return Mix_VolumeMusic (volume); }

inline void SSDL_PauseMusic () { Mix_PauseMusic (); }
inline void SSDL_ResumeMusic() { Mix_ResumeMusic(); }
inline void SSDL_RewindMusic() { Mix_RewindMusic(); }
inline void SSDL_HaltMusic  () { Mix_HaltMusic ();  }

inline void SSDL_SetMusicPosition(double pos) 
{ 
	if (!SSDL_SoundSystem::Instance().initialized()) return;
	if (Mix_SetMusicPosition(pos) < 0) throw SSDL_Exception();
}
inline void SSDL_FadeOutMusic(int ms) 
{ 
	if (!SSDL_SoundSystem::Instance().initialized()) return;
	if (!Mix_FadeOutMusic(ms)) throw SSDL_Exception();
}

inline Mix_MusicType SSDL_GetMusicType (const Mix_Music* music) { return Mix_GetMusicType (music); }

inline bool SSDL_PlayingMusic ()	{ return Mix_PlayingMusic () != 0; }
inline bool SSDL_PausedMusic ()		{ return Mix_PausedMusic  () != 0; }
inline Mix_Fading SSDL_FadingMusic(){ return Mix_FadingMusic  (); }

#endif
