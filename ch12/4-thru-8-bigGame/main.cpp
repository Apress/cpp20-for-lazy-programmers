//Program to catch falling Hallowe'en candy
//      -- from _C++20 for Lazy Programmers_

#include <cmath> //for sqrt
#include "SSDL.h" 

//dimensions of screen and screen locations
constexpr int SCREEN_WIDTH=675, SCREEN_HEIGHT=522; //dimensions of bkgd

constexpr int CANDY_START_HEIGHT =  15;  //where candy falls from

constexpr int MARGIN             =  25;  //As close to the left/right edges 
                                         // of the screen as moving objects
                                         // are allowed to get

constexpr int BOTTOM_LINE        = 480; //Where last line of text is printed
                                        //on instruction & splash screens

//dimensions of important objects
constexpr int CANDY_WIDTH  = 60, CANDY_HEIGHT  = 20;
constexpr int BASKET_WIDTH = 70, BASKET_HEIGHT = 90;

//how many candies you can catch or miss before winning/losing
constexpr int MAX_CAUGHT   = 10, MAX_MISSED    = 10; 
                                 //If you change this, change 
                                 // printInstructions too
                                 // because it specifies this

//fonts for splash screens and catch/miss statistics
constexpr int SMALL_FONT_SIZE  = 12,
              MEDIUM_FONT_SIZE = 24,
              LARGE_FONT_SIZE  = 36;

const SSDL_Font SMALL_FONT 
    = SSDL_OpenFont ("media/Sinister-Fonts_Werewolf-Moon/Werewolf Moon.ttf",
                     SMALL_FONT_SIZE);
const SSDL_Font MEDIUM_FONT
    = SSDL_OpenFont ("media/Sinister-Fonts_Werewolf-Moon/Werewolf Moon.ttf", 
                     MEDIUM_FONT_SIZE);
const SSDL_Font LARGE_FONT 
    = SSDL_OpenFont ("media/Sinister-Fonts_Werewolf-Moon/Werewolf Moon.ttf", 
                     LARGE_FONT_SIZE);

//how far our victory/defeat messages are from left side of screen
constexpr int FINAL_SCREEN_MESSAGE_OFFSET_X = 40;

//background
const SSDL_Image BKGD_IMAGE     
    = SSDL_LoadImage("media/haunted-house.jpg");

//sounds and music
const SSDL_Music BKGD_MUSIC
    = SSDL_LoadMUS(
	       "media/159509__mistersherlock__halloween-graveyd-short.mp3");
const SSDL_Sound THUNK_SOUND
    = SSDL_LoadWAV("media/457741__osiruswaltz__wall-bump-1.wav");
const SSDL_Sound DROP_SOUND   
    = SSDL_LoadWAV("media/388284__matypresidente__water-drop-short.wav");

//structs
struct Point2D { int x_ = 0, y_ = 0; };

using Vector2D = Point2D; 

struct Object
{
    Point2D     loc_;
    int         rotation_      = 0; 

    Vector2D    velocity_;
    int         rotationSpeed_ = 0;

    SSDL_Sprite sprite_;
};

//major functions called by the main program
bool playGame            ();

//startup/ending screens to communicate with user
void printInstructions   ();
void displayVictoryScreen();
void displayDefeatScreen ();

int main (int argc, char** argv)
{
    //set up window and font
    SSDL_SetWindowTitle ("Catch the falling candy");
    SSDL_SetWindowSize  (SCREEN_WIDTH, SCREEN_HEIGHT);

    //prepare music
    SSDL_VolumeMusic (int (MIX_MAX_VOLUME * 0.1));
    SSDL_PlayMusic   (BKGD_MUSIC);

    //initial splash screen
    printInstructions ();

    //The game itself
    bool isVictory = playGame ();

    //final screen:  victory or defeat
    SSDL_RenderClear (BLACK);
    SSDL_HaltMusic   ();
    
    if (isVictory) displayVictoryScreen ();
    else           displayDefeatScreen  ();

    SSDL_RenderTextCentered("Click mouse to end", 
                            SCREEN_WIDTH/2, BOTTOM_LINE, SMALL_FONT);
    SSDL_WaitMouse();  //because if we wait for a key, we're likely 
                        // to have left or right arrow depressed 
                        // when we reach this line... and we never
                        // get to read the final message

    return 0;
}

//// Startup/ending screens to communicate with user ////

void printInstructions ()
{
    constexpr int LINE_HEIGHT = 40;
	
    SSDL_SetRenderDrawColor (WHITE);
    SSDL_RenderTextCentered ("Catch 10 treats in ", 
              SCREEN_WIDTH/2,              0, MEDIUM_FONT);
    SSDL_RenderTextCentered("your basket to win",
              SCREEN_WIDTH/2, LINE_HEIGHT   , MEDIUM_FONT); 
    SSDL_RenderTextCentered ("Miss 10 treats and",
              SCREEN_WIDTH/2, LINE_HEIGHT*3 , MEDIUM_FONT);
    SSDL_RenderTextCentered("the next treat is YOU",
              SCREEN_WIDTH/2, LINE_HEIGHT*4 , MEDIUM_FONT);
    
    SSDL_RenderTextCentered ("Use arrow keys to move",
              SCREEN_WIDTH/2, LINE_HEIGHT*6 , MEDIUM_FONT);
    SSDL_RenderTextCentered("left and right",
              SCREEN_WIDTH/2, LINE_HEIGHT*7 , MEDIUM_FONT);
    
    SSDL_RenderTextCentered ("Click mouse to",
              SCREEN_WIDTH/2, LINE_HEIGHT*9 , MEDIUM_FONT);
    SSDL_RenderTextCentered("toggle stats display",
              SCREEN_WIDTH/2, LINE_HEIGHT*10, MEDIUM_FONT);
    
    SSDL_RenderTextCentered ("Hit any key to continue",
              SCREEN_WIDTH/2, BOTTOM_LINE,    SMALL_FONT);

    SSDL_WaitKey      ();
}

void displayVictoryScreen ()
{
    //sound and picture
    static const SSDL_Sound VICTORY_SOUND
        = SSDL_LoadWAV("media/342153__robcro6010__circus-theme-short.wav");
    SSDL_PlaySound(VICTORY_SOUND);
    static const SSDL_Image GOOD_PUMPKIN
        = SSDL_LoadImage("media/goodPumpkin.png");
    SSDL_RenderImage(GOOD_PUMPKIN, SCREEN_WIDTH / 4, 0);

    //victory message
    SSDL_SetRenderDrawColor(WHITE);
    SSDL_RenderText ("Hooah!"  ,
                     FINAL_SCREEN_MESSAGE_OFFSET_X, SCREEN_HEIGHT/4, 
                     LARGE_FONT); 
    constexpr int LINE_DISTANCE_Y = 96; //an arbitrarily chosen number...
    SSDL_RenderText ("You won!",
                     FINAL_SCREEN_MESSAGE_OFFSET_X,
                     SCREEN_HEIGHT/4+LINE_DISTANCE_Y,
                     LARGE_FONT); 
}

void displayDefeatScreen ()
{
    //sound and picture
    static const SSDL_Sound DEFEAT_SOUND 
        = SSDL_LoadWAV("media/326813__mrose6__echoed-screams-short.wav");
    SSDL_PlaySound(DEFEAT_SOUND);
    static const SSDL_Image SAD_PUMPKIN
        = SSDL_LoadImage("media/sadPumpkin.png");
    SSDL_RenderImage(SAD_PUMPKIN, SCREEN_WIDTH / 4, 0);

    //defeat message
    SSDL_SetRenderDrawColor (WHITE);
    SSDL_RenderText ("Oh, no!", FINAL_SCREEN_MESSAGE_OFFSET_X,
                     SCREEN_HEIGHT/4, LARGE_FONT); 
}

///////////////////// Initializing /////////////////////////

void resetCandyPosition(Object& candy);

void initializeObjects(Object& basket, Object& candy, Object& yumMessage)
{
    //load those images
    SSDL_SetSpriteImage(candy.sprite_,
        SSDL_LoadImage("media/candy.png"));
    SSDL_SetSpriteImage(basket.sprite_,
        SSDL_LoadImage("media/jack-o-lantern.png"));
    SSDL_SetSpriteImage(yumMessage.sprite_,
        SSDL_LoadImage("media/yum.png"));

    //two images are the wrong size; we resize them.
    SSDL_SetSpriteSize(candy.sprite_, CANDY_WIDTH, CANDY_HEIGHT);
    SSDL_SetSpriteSize(basket.sprite_, BASKET_WIDTH, BASKET_HEIGHT);

    //move 'em so they're centered on the coords we set for them
    SSDL_SetSpriteOffset(candy.sprite_,
        CANDY_WIDTH / 2, CANDY_HEIGHT / 2);
    SSDL_SetSpriteOffset(basket.sprite_,
        BASKET_WIDTH / 2, BASKET_HEIGHT / 2);

    //put the objects in their starting positions
    basket.loc_.x_ = SCREEN_WIDTH / 2;
    basket.loc_.y_ = SCREEN_HEIGHT - BASKET_HEIGHT / 2;
    SSDL_SetSpriteLocation(basket.sprite_,
        basket.loc_.x_, basket.loc_.y_);
    resetCandyPosition(candy);
    //We don't care about yumMessage position till we make one

    //And set velocities
    //basket's can't be specified till we check inputs
    constexpr int CANDY_SPEED = 11;       //11 pixels per frame, straight down
    candy.velocity_.y_ = CANDY_SPEED;     //11 per frame straight down
                                          //Increase speeds for faster game
    yumMessage.velocity_ = { 1, -1 };     //Up and to the right

    //And rotational speeds
    candy.rotationSpeed_ = 1;             //Candy spins slightly
}

/////////////////////////// Drawing /////////////////////////////

//Display all 3 objects (2 if yumMessage is currently not visible)
void renderObjects(Object basket, Object candy, Object yumMessage,
    bool showYumMessage)
{
    SSDL_RenderSprite(basket.sprite_);
    SSDL_RenderSprite(candy.sprite_);
    if (showYumMessage) SSDL_RenderSprite(yumMessage.sprite_);
}

void renderStats(int Caught, int Missed)
{
    //Stats boxes, for reporting how many candies caught and missed
    SSDL_SetRenderDrawColor(BLACK);
    constexpr int BOX_WIDTH = 90, BOX_HEIGHT = 25;
    SSDL_RenderFillRect(0, 0,                        //Left box
        BOX_WIDTH, BOX_HEIGHT);
    SSDL_RenderFillRect(SCREEN_WIDTH - BOX_WIDTH, 0, //Right box
        SCREEN_WIDTH - 1, BOX_HEIGHT);

    //Statistics themselves
    SSDL_SetRenderDrawColor(WHITE);
    SSDL_SetFont(SMALL_FONT);

    SSDL_SetCursor(0, 0);                            //Left box
    sout << "Caught: " << Caught;

    SSDL_SetCursor(SCREEN_WIDTH - BOX_WIDTH, 0);     //Right box
    sout << "Missed: " << Missed;
}

//////////////// Moving objects in the world ///////////////////

void resetCandyPosition (Object& candy)  //When it's time to drop 
                                         // another candy...
{
    //Put it at a random X location
    candy.loc_.x_ = MARGIN + rand() % (SCREEN_WIDTH - MARGIN); 
    candy.loc_.y_ = CANDY_START_HEIGHT;    //at the top of the screen

    SSDL_SetSpriteLocation(candy.sprite_, candy.loc_.x_, candy.loc_.y_);
}

void moveObject(Object& object)       
{
    object.loc_.x_ += object.velocity_.x_; //Every frame, move object
    object.loc_.y_ += object.velocity_.y_; //  as specified
    SSDL_SetSpriteLocation(object.sprite_, object.loc_.x_, object.loc_.y_);

                                           //...and spin as specified
    object.rotation_ += object.rotationSpeed_; 
    object.rotation_ %= 360;               //angle shouldn't go over 360
    SSDL_SetSpriteRotation(object.sprite_, object.rotation_);
}

void moveBasket(Object& basket, int basketSpeed)
{
    //Let user move basket with left and right arrows
    if (SSDL_IsKeyPressed (SDLK_LEFT )) basket.loc_.x_ -= basketSpeed;  
    if (SSDL_IsKeyPressed (SDLK_RIGHT)) basket.loc_.x_ += basketSpeed;  

    //..but don't let the user touch the sides of the screen
    if (basket.loc_.x_ < MARGIN)
        basket.loc_.x_ = MARGIN;
    if (basket.loc_.x_ > SCREEN_WIDTH - MARGIN)
        basket.loc_.x_ = SCREEN_WIDTH - MARGIN;

    //Tell the sprite about our changes on X
    SSDL_SetSpriteLocation(basket.sprite_,
                           basket.loc_.x_, basket.loc_.y_);
}

////////What happens when a candy is caught or missed ////////

//Some math functions we need a lot...
int sqr(int num) { return num * num; }

double distance(Point2D a, Point2D b)
{
    return sqrt(sqr(b.x_ - a.x_) + sqr(b.y_ - a.y_));
}

//Circular collision detection, better for round-ish objects
bool inCollision(Point2D a, Point2D b, int aSize, int bSize)
{
    return (distance(a, b) < aSize/2 + bSize/2);
}

//Detect and handle collisions between basket and candy, 
// and update numberCaught
bool handleCatchingCandy (Object basket, Object& candy, Object& yumMessage,
                          int& numberCaught)
{
    if (inCollision (basket.loc_, candy.loc_, CANDY_WIDTH, BASKET_WIDTH))
    {
        SSDL_PlaySound (THUNK_SOUND); 

        ++numberCaught;

        resetCandyPosition (candy);

        yumMessage.loc_.x_    = basket.loc_.x_;
        yumMessage.loc_.y_    = basket.loc_.y_;

        return true;
    }
    else return false;
}

//Detect and handle when candy goes off bottom of screen, 
// and update numberMissed
void handleMissingCandy (Object& candy, int& numberMissed)
{
                                 //you missed it: it went off screen
    if (candy.loc_.y_ >= SCREEN_HEIGHT)  
    {
        SSDL_PlaySound (DROP_SOUND); 

        ++numberMissed;

        resetCandyPosition (candy);
    }
}

///////////////////// Events /////////////////////

void myEventHandler(bool& mouseClicked)
{
    SSDL_Event event;

    while (SSDL_PollEvent(event))
        switch (event.type)
        {
        case SDL_QUIT:            SSDL_DeclareQuit(); break;
        case SDL_KEYDOWN:         if (SSDL_IsKeyPressed(SDLK_ESCAPE)) 
                                      SSDL_DeclareQuit(); 
                                  break;
        case SDL_MOUSEBUTTONDOWN: mouseClicked = true;
        }
}

///// ** The game itself ** ////

bool playGame ()
{
    bool isVictory          = false;      //Did we win?  Not yet
    bool isDefeat           = false;      //Did we lose? Not yet
    bool letsDisplayStats   = true;       //Do we show stats on screen?
                                          //  Yes, for now

    int numberCaught = 0,                 //So far no candies
        numberMissed = 0;                 //  caught or missed

     //Initialize sprites
    Object basket, candy, yumMessage;
    initializeObjects (basket, candy, yumMessage);

    //Main game loop
    while (SSDL_IsNextFrame () && ! isVictory && ! isDefeat) 
    {
        constexpr int FRAMES_FOR_YUM_MESSAGE = 60;
        static int framesLeftTillYumDisappears = 0;

        //Handle input events
        bool mouseClick = false; myEventHandler (mouseClick);
        if (mouseClick) letsDisplayStats = !letsDisplayStats;

        //Display the scene
        SSDL_RenderImage(BKGD_IMAGE, 0, 0);
        renderObjects (basket, candy, yumMessage,
                       framesLeftTillYumDisappears>0);
        if (letsDisplayStats) renderStats (numberCaught, numberMissed);

        //Updates:

        //Move objects in the scene
        constexpr int BASKET_SPEED = 7;    //7 pixels per frame, left or right
        moveBasket(basket, BASKET_SPEED);
        moveObject(candy); moveObject(yumMessage);

                                              //Did you catch a candy?
        if (handleCatchingCandy(basket, candy, yumMessage, numberCaught))
            framesLeftTillYumDisappears = FRAMES_FOR_YUM_MESSAGE;

        if (numberCaught >= MAX_CAUGHT) 
            isVictory = true; 
        else                                  //...or did it go off screen?
        {
            handleMissingCandy (candy, numberMissed);
            if (numberMissed >= MAX_MISSED) 
                isDefeat = true; //You just lost!
        }

        //Update yum message
        if (framesLeftTillYumDisappears > 0)  //if yumMessage is active
            --framesLeftTillYumDisappears;    //  keep counting down
    }

    return isVictory;
}
