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

#ifndef SSDL_DISPLAY_H
#define SSDL_DISPLAY_H

#include <sstream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "SSDL_color.h"
#include "SSDL_exception.h"
#include "SSDL_font.h"
#include "SSDL_singletonManager.h"

class SSDL_Image;

class SSDL_Display
{
	friend void atexitHandler(); //I advise against friends...but every rule has an exception.
public:
	enum {DEFAULT_WIDTH = 640, DEFAULT_HEIGHT = 480};

	SSDL_Display                  (const SSDL_Display&) = delete;
	const SSDL_Display& operator= (const SSDL_Display&) = delete;

	static SSDL_Display& Instance ()
	{
 		static SSDL_Display myInstance;
		return myInstance;
	}	

	void RenderTextLine    (const char* str, int x, int y, const TTF_Font* font, bool isCentered = false); 
	void RenderText        (const char* str, int x, int y, const TTF_Font* font, bool isCentered = false);
	//void scrollVertically  (unsigned int pixels); //Not currently done; maybe nice in next version

	bool isTimeToQuit () const { return isTimeToQuit_; }
	void declareTimeToQuit ()  { isTimeToQuit_ = true; }

	operator SDL_Renderer* () const { return sdlRenderer_; }
	operator SDL_Window*   () const { return sdlWindow_;   }

	void setWindowSize (int w, int h);

	int  advance(char ch) const
	{
		int result;
		if (TTF_GlyphMetrics ((TTF_Font*) (const TTF_Font*) SSDL_GetCurrentFont(), ch, NULL, NULL, NULL, NULL, &result))
			throw SSDL_Exception ();
		return result;
	}
	int fontLineSkip () const
	{
		return TTF_FontLineSkip((TTF_Font*) SSDL_GetCurrentFont());
		//return TTF_FontLineSkip ((TTF_Font*) (const TTF_Font*) currentFont());
		//why the double cast?  SDL_ttf library's never heard of const -- so we must first convert to ptr, then discard const
	}


	const SSDL_Color& background () const { return background_; }
	void	 setBackground (const SSDL_Color& c) { background_ = c; }

	TTF_Font* currentFont() const { return currentFont_; }
	void setCurrentFont(TTF_Font* newFont) { currentFont_ = newFont; }

private:
	SDL_Window*   sdlWindow_;
	SDL_Renderer* sdlRenderer_;
	TTF_Font*	  currentFont_;
	SSDL_Color	  background_;

	bool		  isTimeToQuit_;

	SSDL_Display  ();	
	~SSDL_Display (); 
};



inline bool SSDL_IsQuit      () { return SSDL_Display::Instance().isTimeToQuit(); }
inline void SSDL_DeclareQuit () { SSDL_Display::Instance().declareTimeToQuit();   }

inline void SSDL_SetRenderDrawColor (const SSDL_Color& c)
{
	SDL_SetRenderDrawColor(SSDL_Display::Instance(), c.r, c.g, c.b, c.a);	
}

inline SSDL_Color SSDL_GetRenderDrawColor ()
{
	SSDL_Color c;
	SDL_GetRenderDrawColor (SSDL_Display::Instance(), &c.r, &c.g, &c.b, &c.a);
	return c;
}

inline void SSDL_SetRenderEraseColor (const SSDL_Color& c)
{
	SSDL_Display::Instance().setBackground (c);
}

inline const SSDL_Color& SSDL_GetRenderEraseColor ()
{
	return SSDL_Display::Instance().background();
}

inline void SSDL_RenderClearAux ()
{
	if (SDL_RenderClear (SSDL_Display::Instance()) < 0) throw SSDL_Exception ();
}

void SSDL_RenderClear(const SSDL_Color& c = SSDL_Display::Instance().background());

inline
void SSDL_RenderTextAux (const char* str, int x, int y, const TTF_Font* font = SSDL_GetCurrentFont())
{
	SSDL_Display::Instance().RenderText (str, x, y, font);
}

inline
void SSDL_RenderTextCenteredAux (const char* str, int x, int y, const TTF_Font* font = SSDL_GetCurrentFont())
{
	SSDL_Display::Instance().RenderText (str, x, y, font, true); //true for "yes, center it"
}

template <typename T>
inline
void SSDL_RenderTextCentered (const T& thing, int x, int y, const TTF_Font* font = SSDL_GetCurrentFont())
{
	std::ostringstream os; os << thing;
	SSDL_RenderTextCenteredAux (os.str().c_str(), x, y, font);
}

template <typename T>
inline
void SSDL_RenderText (const T& thing, int x, int y, const TTF_Font* font = SSDL_GetCurrentFont())
{
	std::ostringstream os; os << thing;
	SSDL_RenderTextAux (os.str().c_str(), x, y, font);
}

//...I could do a template specialization here, but it doesn't seem necessary.  It will slow printing of
// strings ever so slightly if I don't.

inline void SSDL_RenderImage (SDL_Texture* image, const SDL_Rect& src, const SDL_Rect& dst)
{
	if (SDL_RenderCopy (SSDL_Display::Instance(), image, &src, &dst) != 0) throw SSDL_Exception ();
}

inline void SSDL_RenderImageEx (SDL_Texture* image, const SDL_Rect& src, const SDL_Rect& dst, double angleInDegrees = 0.0, 
								SDL_RendererFlip flipValue = SDL_FLIP_NONE)
{
	SDL_RenderCopyEx (SSDL_Display::Instance(), image, &src, &dst, angleInDegrees, NULL, flipValue);
}

inline void SSDL_QueryImage (SDL_Texture* image, int& w, int& h)
{
	SDL_QueryTexture (image, NULL, NULL, &w, &h);
}

inline int SSDL_GetImageWidth  (SDL_Texture* image) { int w, h; SSDL_QueryImage (image, w, h); return w; }
inline int SSDL_GetImageHeight (SDL_Texture* image) { int w, h; SSDL_QueryImage (image, w, h); return h; }

void SSDL_RenderImage (SDL_Texture* image, int x, int y, int stretchWidth=0, int stretchHeight=0);

inline void SSDL_RenderPresent () { SDL_RenderPresent (SSDL_Display::Instance ()); }

inline void SSDL_GetWindowPosition(int&        x, int&        y)
{
	SDL_GetWindowPosition ( SSDL_Display::Instance(), &x, &y);
}
inline void SSDL_GetWindowSize (int& x, int& y)
{
	SDL_GetWindowSize     (SSDL_Display::Instance(), &x, &y);
}
inline const char*	SSDL_GetWindowTitle ()				{ return SDL_GetWindowTitle (SSDL_Display::Instance()); }
inline void			SSDL_SetWindowTitle(const char* t)	{ SDL_SetWindowTitle (SSDL_Display::Instance(), t);		}
inline void			SSDL_SetWindowPosition (int x,int y){ SDL_SetWindowPosition(SSDL_Display::Instance(), x,y); }
inline void			SSDL_RestoreWindow  ()				{ SDL_RestoreWindow (SSDL_Display::Instance());			}
inline void			SSDL_MinimizeWindow ()				{ SDL_MinimizeWindow(SSDL_Display::Instance());			}
inline void			SSDL_MaximizeWindow ()				{ SDL_MaximizeWindow(SSDL_Display::Instance());			}
inline int          SSDL_GetWindowWidth ()              { int w, h; SSDL_GetWindowSize (w, h); return w;        }
inline int			SSDL_GetWindowHeight()				{ int w, h; SSDL_GetWindowSize (w, h); return h;		}

inline void			SSDL_SetWindowSize(int w, int h)        { SSDL_Display::Instance().setWindowSize(w, h); }
#endif