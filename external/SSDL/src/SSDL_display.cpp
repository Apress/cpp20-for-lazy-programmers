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

//This is the SSDL_Display -- the screen you see when the program runs.  

#include <exception>
#include <cstring>  
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "SSDL_display.h"
#include "SSDL_image.h"
#include "SSDL_font.h"

#ifdef _MSC_VER					//If it's Visual Studio
#pragma warning(disable : 4996)	//Disable the "feature" that makes strcpy an error!
#endif

//What's this crazy stuff here?  I need to ensure that SSDL_Display::Instance()
// is called (thus initializing SDL among other things) before main starts.
//This will do it.  Why do I care?  In case someone does something in main
// with an SDL feature like mouse cursor that I am not supporting.  It won't
// work till SDL is initialized.  Now it is.

//Weakness:  what if they do this SDL feature globally?  Then order of initialization
// is not guaranteed by C++.  But if they know enough to use an SDL feature, they
// should know enough not to do things with it before SDL is initialized.  So there.

//Will Briggs, 11-12-2015

SSDL_Display::SSDL_Display() : //background_ (0, 0, 0, 255), foreground_ (255, 255, 255, 255),
	isTimeToQuit_ (false)
{
    std::set_terminate (SSDL_terminate);

    if (SDL_Init (SDL_INIT_EVERYTHING) < 0)
		throw SSDL_Exception ();


	sdlWindow_ = SDL_CreateWindow ("",		//no title by default
											  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
											  DEFAULT_WIDTH, DEFAULT_HEIGHT,
											  0);		//flags are 0 by default
	if (! sdlWindow_) throw SSDL_Exception ();

	//defaults below:  index shd be -1 (pick the first renderer that works best)
	//rendererFlags should be 0
	int rendererIndex = -1;
	int rendererFlags = 0;
	sdlRenderer_ = SDL_CreateRenderer (sdlWindow_, rendererIndex, rendererFlags);

	if (! sdlRenderer_) throw SSDL_Exception ();

	//sdlSurface_ = SDL_GetWindowSurface(sdlWindow_); //WSB: It would be polite to free this later

	//if (! sdlSurface_ ) throw SSDL_Exception ();

	SDL_ClearError(); //Why? SDL2_Image documentation warns that IMG_Init does not necessarily
	                  // set the Error, so I figure I'd better clear it.  I hope it sets it if there's an error!
	static const int IMG_FLAGS = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF; //all available types
	if (! (IMG_Init (IMG_FLAGS) & IMG_FLAGS)) throw SSDL_Exception ();

	if (TTF_Init () == -1) throw SSDL_Exception ();

		//Had to avoid calling SSDL_SetRenderDrawColor because it calls SSDL_Display::Instance
		//which calls this ctor, and a thread-safe mechanism got this thing stuck waiting forever
	SDL_SetRenderDrawColor(sdlRenderer_, 255, 255, 255, 255);//the default color for drawing is WHITE.  I don't use the constant
														     //because I don't _know_ that it's been initialized yet.

	int point = 14;
	std::string filename = "arial.ttf"; //This default is recorded in C++20 for Lazy Programmers, so DON'T CHANGE
	std::string finalFilename;

#ifdef _WIN32
	finalFilename = SSDL_SystemFontPath(FONT_PATH, filename.c_str());
	currentFont_ = TTF_OpenFont(finalFilename.c_str(), point);
#else //Unix
	finalFilename = SSDL_SystemFontPath(FONT_PATH, filename.c_str());
	currentFont_ = TTF_OpenFont(finalFilename.c_str(), point);
	if (!currentFont_)
	{
		finalFilename = SSDL_SystemFontPath(FEDORA_FONT_PATH, filename.c_str());
		currentFont_ = TTF_OpenFont(finalFilename.c_str(), point);
	}
#endif

	if (!currentFont_)//Note: VS doesn't thereby do a popup window. Other systems do
	{
		std::string errorMsg = std::string("Missing ") + filename + "; are fonts installed?";
		setCrashMessage(errorMsg); //Redundant? Maybe. But the 3 compilers seem inconsistent in their handling of exceptions
									//VS in debugger crashes (good) and shows you where (good) but doesn't 
									// call the function specified in set_terminate (bad)
									//VS MinGW and Unix, w/o debugging, show the crash message and abort -- good.
		throw SSDL_Exception(errorMsg.c_str());
	}
	
	TTF_SetFontStyle(currentFont_, TTF_STYLE_BOLD);
}

SSDL_Display::~SSDL_Display ()
{
	//This should be done as soon as the error condition arises.  Can we make this happen?  I think so -- by
	// rigorously checking return values, from (for example) SDL_DestroyTexture.  But this would require extra code after
	// any particular call, and that seems costly.

	//const char* errorString = SDL_GetError ();
	//8-17-2017
	//In Windows 10, if there is no speaker connected, you get a new sound system error every time
	// you try to do something iwth a sound -- it won't just let it go
	//So for now, I won't let errors get reported.  This is not optimal. 
	//if (errorString[0] != '\0') //if there's an error
	//			SDL_ShowSimpleMessageBox (SDL_MESSAGEBOX_ERROR, "SDL Error", SDL_GetError (), NULL);

	/*
	5-20-2020 MinGW never returns to the command prompt because of SDL_Quit, which undoubtedly relates
	  to the unspecified order of constructing/destructing globals between files. Ergo: for now
	  just don't do it. Fix later.
	TTF_Quit();
	IMG_Quit();
	//SDL_DestroyRenderer (sdlRenderer_); //not needed, but OK //It was noticeably causing delay, so I commented it out
	SDL_DestroyWindow(sdlWindow_); //not needed, but OK
	SDL_Quit ();
	*/
}

TTF_Font* SSDL_GetCurrentFont()
{
	return SSDL_Display::Instance().currentFont();
}
void SSDL_SetFont(TTF_Font* newFont)
{
	SSDL_Display::Instance().setCurrentFont(newFont);
}


void SSDL_RenderImage (SDL_Texture* image, int x, int y, int stretchWidth, int stretchHeight)
{
	SDL_Rect dst; //src is dimensions of image; dst is where it's goin on screen
	dst.x = x; dst.y = y;

	if (stretchWidth == 0 || stretchHeight == 0) //what if they put in 0 for either?  then dont' stretch
		SDL_QueryTexture(image, NULL, NULL, &dst.w, &dst.h); //get width and height of image
	else
	{
		dst.w = stretchWidth; dst.h = stretchHeight;
	}

	SDL_RenderCopy (SSDL_Display::Instance(), image, NULL, &dst);
}

void SSDL_Display::RenderText (const char* str, int x, int y, const TTF_Font* font, bool isCentered)
	//It's possible that the str may contain \n or \r.  If so, it should be broken into lines
	// and printed.  If centered, we need to remember the center point.  If not, we need to remember the starting point
{
	//This is all about splitting str by using strtok
	// Because std::string doesn't support this, I must do my own dynamic memory

	char* temp = new char [strlen(str)+1]; //strtok destroys its string, so I must make a copy
	strcpy (temp, str);

	char* nextLine = strtok (temp, "\n\r");
	while (nextLine)
	{
		RenderTextLine (nextLine, x, y, font, isCentered);
		y += fontLineSkip ();
		nextLine = strtok (NULL, "\n\r");
	}
	delete [] temp;
}

void SSDL_Display::RenderTextLine (const char* str, int x, int y, const TTF_Font* font, bool isCentered)
{
	SDL_Surface* surfaceToPrintOn;
	surfaceToPrintOn = TTF_RenderText_Solid ((TTF_Font*) font, str, SSDL_GetRenderDrawColor ());
	//arg -- having to cast away that const again.  Why should I have to?
	//I'll assume this is carelessness on the part of SDL2_TTF's creator(s)
	//I can fix this with my own calls
	if (! surfaceToPrintOn) throw SSDL_Exception ();


	SDL_Texture* textureToPrint;
	textureToPrint = SDL_CreateTextureFromSurface (sdlRenderer_, surfaceToPrintOn);

	if (! textureToPrint) throw SSDL_Exception ();

	int centerAdjustment = isCentered ? surfaceToPrintOn->w/2 : 0;
	SDL_Rect whereToPutIt = { x - centerAdjustment, y, surfaceToPrintOn->w, surfaceToPrintOn->h };

	if (SDL_RenderCopy (sdlRenderer_, textureToPrint, NULL, &whereToPutIt) < 0)
		throw SSDL_Exception ();
	//If we used RenderCopyEx, we could also rotate the text, or mirror it vertically or horizontally
	//Another time perhaps
    SDL_DestroyTexture (textureToPrint);  
	SDL_FreeSurface (surfaceToPrintOn);
}

inline
SDL_Surface* SSDL_CopySurface(SDL_Surface* sdlSurface)
{
    return SDL_ConvertSurface(sdlSurface, sdlSurface->format, 0);
}


/*void SSDL_Display::scrollVertically (unsigned int pixels) //Not currently done; maybe nice in next version
{
	SDL_Rect srcRect, destRec;
	srcRect.x = destRec.x = 0;
	srcRect.y = pixels;
	destRec.y= 0;
	srcRect.w = destRec.w = sdlSurface_->w; //If I need sdlSurface_, get it at last minute with SDL_GetWindowSurface
	srcRect.h = destRec.h = sdlSurface_->h - pixels;

	SDL_Surface* temp = SSDL_CopySurface (sdlSurface_);
	//SDL_FillRect (temp, &srcRect, SDL_MapRGB (sdlSurface_->format, 255, 255, 255));
	//I don't know if you can copy a surface onto itself...
	SDL_BlitSurface (temp, NULL, sdlSurface_, NULL);
	//SDL_BlitSurface (temp, &srcRect, sdlSurface_, &destRec); //I think it's not blitting -- I think the
	//then a bkgd-color rectangle at the bottom
}
*/
void SSDL_RenderClear(const SSDL_Color& c)
{
	SSDL_Color old = SSDL_GetRenderDrawColor();
	SSDL_SetRenderDrawColor(c);
	SSDL_RenderClearAux();
	SSDL_SetRenderDrawColor(old);
}

void SSDL_Display::setWindowSize(int w, int h)
{
#ifdef __unix__
	SDL_Event e; while (SDL_PollEvent(&e));
#endif
									//In Unix (Ubuntu 4.18.0-5.0.0 --
									//I don't think other distributions of Linux
									//have this problem) if I don't to this, the
									//next call to SDL_GetWindowSize will get the old
									//dimensions, not the new. Go figure.

	SDL_SetWindowSize(SSDL_Display::Instance(), w, h);

    //SSDL_RenderPresent ();	//In Unix, if I don't do these, the next things
    //SDL_PollEvent(nullptr); //drawn will be offset from 0,0. SSDL_WaitKey etc.
                            //also do these things (OK, SDL_WaitEvent(ptr)
                            //not SDL_PollEvent(nullptr)). IDK yet why this
                            //is needed. -- WB 6-5-2019
							//...actually, that's no longer sufficient. I seem
							// to need a delay. Have filed a bug report with SDL
							// on bugzilla 7-20-2019.
							
#ifdef __unix__
    SDL_RenderPresent(SSDL_Display::Instance());
    for (int i = 0; i < 20; ++i) //Must be 6 or more to be reliable
        SDL_Delay(10);          //10 works; 1 doesn't
                                //A single SDL_Delay(60); usually works
                                //but sometimes does not
#endif

//Programs in the repository that fail on some unix installations unless I do this
// are Ch2/[any but sound], ch4/search*, ch9/*, ch10/ticTacToeBoard, ch11/staircase

//The earlier SDL_Event e;... line is also needed for ch11/spritefish* and possibly
// for other programs with game loops
//#elif __unix__
//...
//#endif
}
