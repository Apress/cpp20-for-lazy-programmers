// One step in a game of craps
// 		-- from _C++20 for Lazy Programmers_

#include <ctime>    // for time function
#include <cstdlib>  // for srand, rand
#include "SSDL.h"

constexpr int SIDES_PER_DIE = 6;

int rollDie ();		             // roll a 6-sided die

int main (int argc, char** argv)
{
    srand ((unsigned int) (time (nullptr))); 
                                // This starts the random # generator
                                // It gets called once per program

    SSDL_SetWindowTitle ("Craps roll");
    
    sout << "Ready to roll?  Hit a key to continue.\n";
    SSDL_WaitKey ();
    
    int roll1 = rollDie (), roll2 = rollDie ();
    sout << "You rolled a " << roll1 << " and a " << roll2;
    
    switch (roll1 + roll2)
    {
    case  2: 
    case  3:
    case 12: sout << " -- craps. You lose the pass line bet.\n";
             break;
    case  7:
    case 11: sout << " -- natural. You win the pass line bet.\n";
             break;
    default: sout <<", so " << roll1 + roll2 << " is your point.\n";
    }
    
    sout << "Hit a key to end.\n";
    SSDL_WaitKey();
    
    return 0;
}

int rollDie () { return rand() % SIDES_PER_DIE + 1; }
