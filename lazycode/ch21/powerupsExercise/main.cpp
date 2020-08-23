//Program to animate some powerups on mouse clicks
//		-- from _C++20 for Lazy Programmers_

#include <vector>
#include "flashyPowerup.h"
#include "megaPowerup.h"
#include "wormhole.h"

using namespace std;

Powerup* selectPowerup  (vector<Powerup>& objects); 
void     printScore     (int score);
void     move           (vector<Powerup>& powerups); 

int main (int argc, char** argv) 
{
    //This should not compile when the exercise is done:
    //Powerup p;

    SSDL_SetWindowSize (500, 300);	//make window smaller
    SSDL_SetWindowTitle("Click on a powerup for points!");

    //Create a set of powerups
    vector<Powerup> powerups; 
    enum {RADIUS = 30};

    //consisting of three powerups
    powerups.push_back (FlashyPowerup ( 75, 150, RADIUS));
    powerups.push_back (Wormhole      (250, 150, RADIUS));
    powerups.push_back (MegaPowerup   (425, 150, RADIUS));

    //color those powerups
    const SSDL_Color YELLOW (255, 255, 0);
    const SSDL_Color COLORS [] = { BLUE, YELLOW, GREEN };
    for (unsigned int i = 0; i < powerups.size(); ++i)
        powerups[i].setColor (COLORS [i]);

    //do a game loop
    while (SSDL_IsNextFrame ())
    {
        SSDL_DefaultEventHandler ();

        SSDL_RenderClear ();	//clear the screen

        static int score = 0;
        printScore (score);

        //see if the user clicked on a powerup
        Powerup* shapeSelected = selectPowerup (powerups);
        if (shapeSelected)	//if so, and it's not already animated
            if (! shapeSelected->isAnimated ())
            {			//animated it, and update score
                shapeSelected->startAnimation ();
                score += shapeSelected->value ();
            }

        //Drawing...but we should animate
        for (unsigned int i = 0; i < powerups.size(); ++i)
            powerups[i].draw ();//<-- Change this to animate
	
        move (powerups);        //let the powerup set isBounce around the screen
    }

    return 0;
}

void move (vector<Powerup>& powerups)
{
    enum {SPEED=5};

    static int dx = 1, dy=1;				//Initially, we're headed SE

    for (unsigned int i = 0; i < powerups.size(); ++i)	//move 'em around the screen
        powerups[i].moveBy(dx*SPEED, dy*SPEED);

    bool isBounceX = false, isBounceY = false;          //Do we need to reverse direction?

    for (unsigned int i = 0; i < powerups.size(); ++i)  //If any powerup...
	{
	    //goes off screen to left
	    if (powerups[i].location().x_ < powerups[i].radius()) isBounceX = true;
	    //...or right
	    if (powerups[i].location().x_ > SSDL_GetWindowWidth() - powerups[i].radius())
		isBounceX = true;
	    //...or top
	    if (powerups[i].location().y_ < powerups[i].radius()) isBounceY = true;
	    //...or bottom,
	    if (powerups[i].location().y_ > SSDL_GetWindowHeight()- powerups[i].radius())
		isBounceY = true;
	    //then bounce back in that direction
	}

    if (isBounceX) dx *= -1; //if we need to bounce, change direction
    if (isBounceY) dy *= -1;
}

void printScore (int score)
{
    SSDL_SetRenderDrawColor (WHITE);
    enum {SCORE_MSG_WIDTH = 80, SCORE_NUM_WIDTH=20};

    SSDL_SetCursor(SSDL_GetWindowWidth() - SCORE_MSG_WIDTH, 0); 
    sout << "Score:  " << score;
}

//from Chapter 12
bool getMouseClickWithDelay (int waitingPeriod)
{
    static int timeSinceLastMouseClick = 0;
    bool isClicked = false;	          //no click yet...

    //click, so reset waiting time
    //and return that a click happened
    if (timeSinceLastMouseClick > waitingPeriod && SSDL_GetMouseClick ())
    {
        timeSinceLastMouseClick = 0; isClicked = true;
    }
    else                                  //don't report click; just update time
        ++timeSinceLastMouseClick;

    return isClicked;
}

Powerup* selectPowerup (std::vector<Powerup>& objects)
{
    int x = SSDL_GetMouseX(), y = SSDL_GetMouseY(); //get position
	
    enum {MOUSE_CLICK_DELAY = 10};		    //no mouse click? never mind
    if (! getMouseClickWithDelay (MOUSE_CLICK_DELAY)) return nullptr;

    //if mouse clicked, find the object clicked on (if any) and return a pointer to it
    for (unsigned int i = 0; i < objects.size(); ++i)
        if (objects[i].contains(x, y))
            return &(objects[i]);

    return nullptr; //but if nothing was clicked on, return nothing
}

