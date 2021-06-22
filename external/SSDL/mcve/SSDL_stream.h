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

//This is SSDL stream I/O, culminating in sin (which reads from kbd, prints chars to output, and reads in text)
// and sout (which prints to screen)

#ifndef SSDL_STREAM_H
#define SSDL_STREAM_H

#include <iostream>
#include <cassert>
#include <cstring> //for memmove
#include "SSDL_font.h"
#include "SSDL_io.h"
#include "SSDL_image.h"

//extern SSDL_Font* currentFont; //move to SSDL_font, and make it generally avaiable?

//SDL has a cursor, but that's for mouse.
//I need one for my stream IO.
//I will make it as a square, based on font size, with a line at the bottom.
//It will be drawn to cursorX, cursorY location
//Backspace should move it back, leaving behind an empty box (use SSDL_Display background color)
//When we put text there, make sure to erase it!

//scrolling will be triggered when cursorY() gets to within fontLineSkip*2 pixels of the bottom of the screen.
//It will capture the screen, 0 to maxX, fontLineSkip to maxY;
// paste it onto the screen at position 0, 0
// past an empty rectangle of SSDL_Display's background color at position 0, maxY-fontLineSkip

//I'm pretty sure this is all do-able


class SSDL_StreamIOSystem
{
public:
  static SSDL_StreamIOSystem& Instance ()
  {
    static SSDL_StreamIOSystem myStreamIOSystem;
    return myStreamIOSystem;
  }
  SSDL_StreamIOSystem(const SSDL_StreamIOSystem&) = delete;
  const SSDL_StreamIOSystem& operator= (const SSDL_StreamIOSystem&) = delete;

  TTF_Font* currentFont () const { return SSDL_GetCurrentFont (); }

  int  cursorX() const { return cursorX_; }
  int  cursorY() const { return cursorY_; }
  int& cursorX()		 { return cursorX_; }
  int& cursorY()		 { return cursorY_; }
  void setCursor (int x, int y) { cursorX_ = x; cursorY_ = y; }
  void eraseCharAtCursor (char c); //should not be called after changing font... odd things'll happen

private:
  SSDL_StreamIOSystem () : /*currentFont_ (NULL), */cursorX_(0), cursorY_(0)
  {
  }

  int cursorX_, cursorY_;
};

inline void SSDL_SetCursor (int x, int y) { SSDL_StreamIOSystem::Instance().setCursor (x, y); }

/*
  If newFont goes away (wherever SSDL_SetStreamIOFont was called from, currentFont now points to nothing.
  But we have no way of copying a font.  We could only store its file name and point and reload it, which
  is slow and not SDL-like.
  So we'll tell the library users:  don't set to a font and then let that font go out of scope -- then
  the current font will be gone!  That's not too unreasonable.
*/

//Does all this really need to be template?

template<class _Elem, class _Traits = std::char_traits <_Elem> >
class SSDL_BufferOut: public std::basic_streambuf<_Elem, _Traits>
{
public:
  typedef _Elem                           char_type;
  typedef _Traits                         traits_type;
  typedef typename traits_type::int_type int_type;
  typedef typename traits_type::off_type off_type;
  typedef typename traits_type::pos_type pos_type;

  SSDL_BufferOut()  { } 
  void printChar (_Elem ch); 
protected:
  int_type overflow (int_type c = traits_type::eof ());
};

template <class charType, class TraitsType>
void SSDL_BufferOut<charType, TraitsType>::printChar (charType ch)
{
  //fontLineSkip is how far to go down to next line
  //advance is how far to go right to next char
  //it varies except in fixed-width font
  //This may blow away my hope of saving time by sending entire strings -- or not.  Not sure
  // it'll be O(N) to find the advance, but I don't know how long it takes to render a string

  //Why all this casting to TTF_Font*?  Because SDL2_ttf library hasn't heard of const, so it objects
  // when I send a const pointer.
  int fontLineSkip = TTF_FontLineSkip ((TTF_Font*) (const TTF_Font*) SSDL_StreamIOSystem::Instance().currentFont()); //and what font is that?
  int myAdvance;
  if (TTF_GlyphMetrics ((TTF_Font*) (const TTF_Font*) SSDL_StreamIOSystem::Instance().currentFont(), ch, NULL, NULL, NULL, NULL, &myAdvance))
    throw SSDL_Exception ();
  static char buf[2] = {'\0'};
  //static int cursorX = 0, cursorY = 0; //DEFINITELY we will move this soon.

  switch (ch)
    {
    case '\n':
    case '\r':
      SSDL_StreamIOSystem::Instance().cursorY() += fontLineSkip;
      SSDL_StreamIOSystem::Instance().cursorX() =   0;
      break;
    case '\t':
      SSDL_StreamIOSystem::Instance().cursorX() = (((SSDL_StreamIOSystem::Instance().cursorX()/myAdvance)/8)+1)*8*myAdvance; //8 spaces per tab, by convention
      break;
    default:
      buf[0] = ch;
      SSDL_RenderText (buf, SSDL_StreamIOSystem::Instance().cursorX(), SSDL_StreamIOSystem::Instance().cursorY(), (TTF_Font*) (const TTF_Font*) SSDL_StreamIOSystem::Instance().currentFont());
      SSDL_StreamIOSystem::Instance().cursorX() += myAdvance;
    }
}

template <class _ELem, class _Traits>
typename SSDL_BufferOut<_ELem, _Traits>::int_type
SSDL_BufferOut<_ELem, _Traits>::overflow (typename SSDL_BufferOut<_ELem, _Traits>::int_type c)
{
  //This is likely inefficient:  better to send big chunks rather than individual chunks
  //Later, make SSDL use this aright.  For now...
  printChar (c);
  //PRINT IT ON THE SCREEN -- I think!
  //return std::basic_filebuf<_ELem, _Traits>::overflow (c);

  //return something that isn't _Traits::eof() -- unless we fail somehow
  //What if we're passed eof?  Should we return failure (eof)?

  return 0; //Is this OK?
  //return (! _Traits::eof ());
}

template <class charT, class traits = std::char_traits<charT> >
class SSDL_BufferIn: public std::basic_streambuf<charT, traits>
{
public:
  enum {BUFFER_SIZE = 256};

  typedef charT                          char_type;
  typedef traits                         traits_type;
  typedef typename traits_type::int_type int_type;
  typedef typename traits_type::off_type off_type;
  typedef typename traits_type::pos_type pos_type;

  SSDL_BufferIn ()
  {
    this->setg (buffer_, buffer_, buffer_);
    //This tells C++ where the read buffer starts, where it ends, and where the next char to read is
    // We offset it so there is an area to prepend things?  Don't know yet
  }
protected:
  int numCharsInBuffer () const { return int(this->egptr()-this->gptr()); }//it's the end position minus the next-char position
  char buffer_[BUFFER_SIZE]; //OK, but what if it grows too high? //should it be an int array?  setg says no

  int_type underflow ();
  int_type pbackfail (int_type c);
private:
  int_type  getMoreChars ();
  void egbump (int n)           //I wonder why this isn't built in?  moves end ptr by n units.
  {
    this->setg (this->eback(), this->gptr(), this->egptr()+n);
  }

  void handleBackspace(bool& charRemoved);			//used by getMoreChars ()
  void addACharacter(char c, bool& quit);				//used by getMoreChars ()
};

extern std::ostream sout;
extern std::istream ssin;

//As I understand it, underflow is here for when the istream class wants another character, it can get it
// from the source I provide (the buffer, if there is anything in it; if not, from the device that gives us chars)
template <class charType, class TraitsType>
typename SSDL_BufferIn<charType, TraitsType>::int_type SSDL_BufferIn<charType, TraitsType>::underflow ()
{
  if (numCharsInBuffer() > 0)						//If we have a char in the buffer to provide...
    return TraitsType::to_int_type (*(this->gptr()));	//... return it!  Job complete
  else if (getMoreChars ()>0)						//Can we get one from the device?
    return TraitsType::to_int_type (*(this->gptr()));	//If so, we did it; return the next char available
  else											//NO way to get a character!  Oh, no!  Return failure
    return TraitsType::eof ();
}

template <class charType, class TraitsType>
void SSDL_BufferIn<charType, TraitsType>::handleBackspace(bool& charRemoved)	//process a backspace in my input
{
  charRemoved = false;

  if (this->egptr() != this->eback() && SSDL_StreamIOSystem::Instance().cursorX() > 0) //last condition:  can we be assured it's right?  Cd we be
    //off by a few pixels?
    {
      char prevChar = *((this->egptr()) - 1);
      switch (prevChar)
	{
	case '\n':
	case '\r':
	case -1: //eof
	  break;
	default:
	  SSDL_StreamIOSystem::Instance().cursorX()
	    -= SSDL_Display::Instance().advance(prevChar);

	  SSDL_StreamIOSystem::Instance().eraseCharAtCursor(prevChar); //erase the char backspaced over

	  assert(SSDL_StreamIOSystem::Instance().cursorX() >= 0); //we shd've had at least 1 char on line, plus my new blank space!
	  egbump(-1); //move gptr back 1 space, so we're ignoring where we were
	  charRemoved = true;

	  break;
	}
    }
}

inline bool isNumLockOn (SDL_Keymod mod) { return (mod & KMOD_NUM) != 0; }

//We got a character through ssin... display it and send it where it should go.
template <class charType, class TraitsType>
void  SSDL_BufferIn<charType, TraitsType>::addACharacter(char c, bool& OKWereDone)
{
  if (this->gptr() >= this->eback() + BUFFER_SIZE - 1) //no room!
    {
      OKWereDone = true;	//What will this look like?  Test with tiny buffer size.
      return;
    }

  sout << c;
  *(this->egptr()) = c;
  egbump(1); //move end pointer one step further
}

template <class charType, class TraitsType>
typename SSDL_BufferIn<charType, TraitsType>::int_type  SSDL_BufferIn<charType, TraitsType>::getMoreChars ()
{
  SSDL_RenderPresent();	//We're about to wait for user input... so let's see what's already there

  //As it is, unless you backspace, you _never_ have gptr going back...and it should!  Can I be guaranteed
  // that every time istream calls underflow, it ate all the chars SSDL_BufferIn provided?  Yes!  So I will
  //move everything back.

  assert (this->eback () == buffer_); //if not, why not?
  if (this->gptr() != this->eback())
    memmove (this->eback(), this->gptr(), this->egptr()-this->gptr()); // I think this'll move things back!

  bool OKWereDone = false;
  int  numCharsRead = 0;

  while (! OKWereDone) //Looks a lot like SSDL_WaitEvent...
    {
      SDL_Event event;

      while (SDL_PollEvent(&event) != 0)
	{
	  SDL_Keymod   mod		= SDL_GetModState();
	  bool	     isNumLock	= isNumLockOn(mod);
	  SDL_Scancode scancode;

	  //If a quit message came, let's get out.
	  SSDL_CheckForQuitMessages(event);
	  if (SSDL_Display::Instance().isTimeToQuit())
	    {
	      OKWereDone = true;  break;
	    }

	  //Now let's process two kinds of messages.  SDL_KEYDOWN for when we get a backspace or a return
	  //SDL_TEXTINPUT for when we get useful, printable text.

	  switch (event.type)
	    {
	    case SDL_KEYDOWN:
	      scancode = event.key.keysym.scancode;
	      if (scancode == SDL_SCANCODE_BACKSPACE || (!isNumLock && scancode == SDL_SCANCODE_KP_BACKSPACE))
		{
		  bool charRemoved;
		  handleBackspace(charRemoved);
		  if (charRemoved) --numCharsRead;
		  SSDL_RenderPresent();	//Let user see what's typed 
		}
	      if (scancode == SDL_SCANCODE_RETURN || scancode == SDL_SCANCODE_RETURN2)
		{
		  OKWereDone = true;

		  addACharacter(event.key.keysym.sym, OKWereDone);
		  ++numCharsRead;
		  SSDL_RenderPresent();	//Let user see what's typed 
		}
	      break;
	    case SDL_TEXTINPUT:
	      addACharacter(event.text.text[0], OKWereDone);
	      ++numCharsRead;
	      SSDL_RenderPresent();	//Let user see what's typed 
	    }
	}
    }

  SSDL_RenderPresent();	//Do we need to do it again just to be sure? Wouldn't hurt
  return numCharsRead;

  ////assert:  numCharsInBuffer() == 0, that is, gptr() == eback() == egptr(), that is, start==next==finish
  //int result = getCharsSomehow ();
  //if (result <= 0) return -1; //getChars failed; return failure.  Should NEVER HAPPEN
  //else
  //	setg (buffer_ ,
  //		  buffer_ ,
  //		  buffer_ +result;
}

template <class charType, class TraitsType>
typename SSDL_BufferIn<charType, TraitsType>::int_type SSDL_BufferIn<charType, TraitsType>::pbackfail (int_type c)
{
  if (this->gptr() == this->eback ()) //if there is no further back we can go -- we're at start of buffer
    return TraitsType::eof (); //then failse
  else
    {
      this->gbump(-1); //back up one space
      //and if there's no EOF where we just went, put our char there
      if (! TraitsType::eq_int_type (c, TraitsType::eof ()))
	{
	  *(this->gptr()) = TraitsType::to_char_type (c);
	  return c;
	}
      else
	return TraitsType::not_eof(c);
    }
}

#endif //SSDL_STREAM_H
