// Program to display a 4-panel comic strip with stick figures.
// 		-- from _C++20 for Lazy Programmers_

#include "SSDL.h"

// function prototypes
void drawFrame    (const char* leftDialog, const char* rightDialog); 
void drawCharacter(int x, int y);
void drawDialog   (int x, int y, const char* dialog);
void hitEnterToContinue (); // wait for user to hit Enter

int main (int argc, char** argv)
{
    // Set up:  window title and font
    SSDL_SetWindowTitle ("My own 4-panel comic");
    const SSDL_Font COMIC_FONT = SSDL_OpenSystemFont("comic.ttf",18);
    SSDL_SetFont (COMIC_FONT);
	
    // Now the four frames
    drawFrame  ("Somebody said something really nasty\nto me "
                "on Internet.\nSo I put him in his place.",
                "Maybe it's not a him.\nMaybe it's a her.  "
                "You never know.");
    hitEnterToContinue();

    drawFrame  ("OK, her.  Whatever.  She kept saying\nall this "
                "stuff about how superior\nshe was.  I found "
                "a spelling error and\ntold her she can't even "
                "spell so she\nshould just shut up.",
                "If it's a her.  It *might* be a him.\nThe point "
                "is we just don't know.");
    hitEnterToContinue();

    drawFrame  ("The *point* is, he went on a rant about\nhow you "
                "can spell things like \"b4\"\nand so on in l33t, "
                "and I told him l33t\nis for lusers -- with a u, "
                "you know.\nThen he told me I misspelled \"loser.\"",
                "If it's a him.  It could be both.\nSometimes "
                "married people\nshare accounts.");
    hitEnterToContinue();

    drawFrame  ("You're making me crazy!",
                "Can I have the URL for that forum?\nI'm not "
                "done yet.");
    hitEnterToContinue ();

    return 0;
}

void drawFrame (const char* leftDialog, const char* rightDialog)
// draw a cartoon's frame, given dialog for each of two characters
{
    constexpr int LEFT_X  =   0, LEFT_Y  = 20;	
    constexpr int RIGHT_X = 320, RIGHT_Y = 40;	
    // right character is drawn a little lower
    // it doesn't look so much like a mirror image

    SSDL_RenderClear ();	// clear background to black
    drawCharacter    (LEFT_X,  LEFT_Y); 
    drawDialog       (LEFT_X,  LEFT_Y,  leftDialog);
    drawCharacter    (RIGHT_X, RIGHT_Y); 
    drawDialog       (RIGHT_X, RIGHT_Y, rightDialog);
}

void drawCharacter (int x, int y)
// draw a stick-figure character, with its dialog at the top.
//  The upper-left corner of it all is x, y
{
    constexpr int HEAD_RADIUS = 45;
    
    SSDL_RenderDrawCircle (x+140, y+195, HEAD_RADIUS);  // draw head

    SSDL_RenderDrawLine   (x+142, y+240, x+140, y+340); // draw body,
                                                   // slightly angled
	
    SSDL_RenderDrawLine   (x+142, y+260, x+115, y+340); // draw arms
    SSDL_RenderDrawLine   (x+142, y+260, x+165, y+342); 

    SSDL_RenderDrawLine   (x+140, y+340, x+100, y+420); // draw legs
    SSDL_RenderDrawLine   (x+140, y+340, x+157, y+420);
}

void drawDialog (int x, int y, const char* dialog)
// Draw the dialog for a character, with a line connecting
//  it to the character.  x, y is the upper-left corner of 
//  the whole set (dialog plus character)
{
    // line linking character to dialog
    SSDL_RenderDrawLine (x+90, y+100, x+112, y+130);
    // dialog itself
    SSDL_RenderText	(dialog, x+20, y);
}

void hitEnterToContinue()
{
    // How far up to put the "Hit a key" message
    constexpr int BOTTOM_LINE_HEIGHT = 25;

    // More succinct than "Hit any key to continue but not
    //  Escape because that ends the program"
    SSDL_RenderTextCentered("Hit Enter to continue",
                SSDL_GetWindowWidth() / 2,
                SSDL_GetWindowHeight() - BOTTOM_LINE_HEIGHT);

    SSDL_WaitKey();
}

