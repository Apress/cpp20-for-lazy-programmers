//Test my own rand function by printing 10 random digits
//		-- from _C++20 for Lazy Programmers_

#include "SSDL.h"

unsigned long int seed;	        //Current random number seed 

void srand (unsigned int what)  //Start the random number generator	
{
    seed = what;
}

int rand ()                     //Return a pseudo-random integer 
{
    static constexpr unsigned int INCREMENT = 51138;
    static constexpr unsigned int MULTIPLIER= 21503;
    static constexpr unsigned int MODULUS   = 32767;
    
    seed += INCREMENT;
    seed *= MULTIPLIER;
    seed %= MODULUS;
    
    return seed;
}

int main (int argc, char** argv)
{
    int mySeed;
    sout << "What sequence do you want? Enter an int: ";
    ssin >> mySeed;
	
    srand (mySeed); //This starts the random # generator
                    //It gets called once per program
					
    sout << "10 random digits: "; //Print the digits
    for (int i = 0; i < 10; ++i)
        sout << rand()%10 << ' ';	
    sout << '\n';
    
    sout << "Hit a key to end.\n";
    SSDL_WaitKey();
    
    return 0;
}

