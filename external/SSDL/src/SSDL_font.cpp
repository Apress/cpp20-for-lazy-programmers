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

//This is SSDL_Font, a wrapper for TTF_Font

#include <string>
#include <cstring>
#include <sstream>
#include "SSDL_font.h"
#include "SSDL_exception.h"
#include "SSDL_display.h"

using namespace std;

//All this does is set up the full path for a font
std::string SSDL_SystemFontPath(const char* fontPath, const char* filename)
{
	std::string newPath(fontPath); newPath += filename; 
	if (!matchFromEnd(filename, ".ttf")) newPath += ".ttf";
	return newPath;
}

TTF_Font* SSDL_OpenSystemFont(const char* filename, int point)
{
	string finalFilename;
	TTF_Font* currentFont_; //WSB: change to "result"

#ifdef _WIN32
	finalFilename = SSDL_SystemFontPath(FONT_PATH, filename);
	currentFont_ = TTF_OpenFont(finalFilename.c_str(), point);
#else //Unix
	finalFilename = SSDL_SystemFontPath(FONT_PATH, filename);
	currentFont_ = TTF_OpenFont(finalFilename.c_str(), point);
	if (!currentFont_)
	{
		finalFilename = SSDL_SystemFontPath(FEDORA_FONT_PATH, filename);
		currentFont_ = TTF_OpenFont(finalFilename.c_str(), point);
	}
#endif
	if (!currentFont_) //Note: VS doesn't thereby do a popup window. Other systems do
	{
		std::string errorMsg = std::string("Can't open font ") + filename + ".";
		setCrashMessage(errorMsg); //Redundant? Maybe. But the 3 compilers seem inconsistent in their handling of exceptions
								//VS in debugger crashes (good) and shows you where (good) but doesn't 
								// call the function specified in set_terminate (bad)
								//VS MinGW and Unix, w/o debugging, show the crash message and abort -- good.
		throw SSDL_Exception();
	}
	return currentFont_;
}

bool matchFromEnd (const char* str, const char* substr) 
{
    char* strEnd    = (char*) str+strlen(str)-1;
    char* substrEnd = (char*) substr+strlen(substr)-1;

    for (;;--strEnd, --substrEnd)
    {
        if (toupper(*substrEnd) != toupper(*strEnd))  return false;

        if (substrEnd <= substr)    return true;
        else if (strEnd <= str)     return false;
    }
}

TTF_Font* SSDL_OpenFont(const char* filename, int point)
{
	SSDL_Display::Instance(); //be sure SSDL is initialized...

	//We hope the filename ends in .ttf.  If not, and there's no extension, append it.
	//If not, and there is an (incorrect) extension, go ahead and append it, and watch it fail.

	string finalFilename = filename;
	if (!matchFromEnd(filename, ".ttf")) finalFilename += ".ttf";

	TTF_Font* result = TTF_OpenFont(finalFilename.c_str(), point);
	if (!result) //Note: VS doesn't thereby do a popup window. Other systems do
	{
		std::string errorMsg = std::string("Can't open font ") + filename + ".";
		setCrashMessage(errorMsg); //Redundant? Maybe. But the 3 compilers seem inconsistent in their handling of exceptions
								//VS in debugger crashes (good) and shows you where (good) but doesn't 
								// call the function specified in set_terminate (bad)
								//VS MinGW and Unix, w/o debugging, show the crash message and abort -- good.
		throw SSDL_Exception();
	}
	return result;
}

/*TTF_Font* SSDL_OpenFont (const char* filename, int point)
{
	SSDL_Display::Instance();  //be sure SSDL is initialized...

	//Laura Mercy, what a lot of code just to check for file extension!
	enum {MAXLENGTH=5};
	char ext [5];
	if (_splitpath_s (filename, NULL, 0, NULL, 0, NULL, 0, ext, MAXLENGTH))
	{
		ostringstream os; os << "Could not extract extension from filename " << filename <<"; max length is " << MAXLENGTH-1;
		SDL_SetError (os.str().c_str());
		throw SSDL_Exception ();
	}

	//and if it's not there, add it.  I don't check for the WRONG one; SDL_TTF can do that
	string finalFilename = filename;
	if (strcmp (ext, "") ==0) finalFilename += ".ttf";

	//SSDL_Display::Instance (); //be sure it's all set up BEFORE we try to load a font
	TTF_Font* result = TTF_OpenFont (finalFilename.c_str(), point);
	if (! result) throw SSDL_Exception ();
	return result;
}*/


