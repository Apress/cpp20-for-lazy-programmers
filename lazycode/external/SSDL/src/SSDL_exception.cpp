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

//This is ssdl_exception.cpp, which provides an exception class that SSDL throws

#include <SDL.h>
#include "SSDL_exception.h"

void SSDL_terminate () //DOES NOT GET CALLED when we are in the Debugger
{
	//yes, but how do I know what exception was thrown?
	//I *could* just call SDL_GetError again -- I think -- but the correct thing is to use
	//What will it display if the error was not SDL?
	try
	{
		throw;
	}
	catch (const SSDL_Exception& c)
	{
		SDL_ShowSimpleMessageBox (SDL_MESSAGEBOX_ERROR, "SDL Error", c, NULL); //SDL_GetError (), NULL);
	}

	abort ();
}
