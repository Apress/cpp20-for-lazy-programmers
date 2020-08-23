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

#ifndef SSDL_EXCEPTION_H
#define SSDL_EXCEPTION_H

#include <iostream>
#include <string>
#include <SDL.h>

class SSDL_Exception 
{
public:
	SSDL_Exception(const char* message = SDL_GetError()) : contents_(message) {}
	/*SSDL_Exception () : contents_ (SDL_GetError ()) 
	{
	}*/
	void print (std::ostream& out) const{ out << contents_;          }
	operator const std::string () const { return contents_;			 }
	operator const char*	   () const { return contents_.c_str (); }
private:
	std::string contents_;
};

inline
std::ostream& operator<< (std::ostream& out, const SSDL_Exception& foo)
{
	foo.print (out); return out;
}

void SSDL_terminate ();
#endif