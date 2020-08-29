// Program to do some things with enum and enum class
//               -- from _C++20 for Lazy Programmers_

#include "SSDL.h"

// The following weird construction says, "If the compiler supports 'using enum',
//  declare two enum classes. If not, declare two enums (w/o saying "class").

// In my opinion enum class, a relatively recent addition to C++, didn't 
//  really become useful till we got 'using enum.' So here I avoid it
//  ...unless your compiler is C++20-compliant in this regard. 

// Find more about this kind of #ifdef "preprocessor directive" at 
//  https://en.cppreference.com/w/cpp/feature_test
//   -- WB

//  Suit and Rank enumeration types
#ifdef __cpp_using_enum 
                 //  if __cpp_using_enum is defined, that is,
                 //  if the compiler supports "using enum,"
                 //     then use enum class
enum class Suit { CLUBS, DIAMONDS, HEARTS, SPADES };     
enum class Rank { ACE = 1, JACK = 11, QUEEN, KING };
#else            //  otherwise use plain enum
enum       Suit { CLUBS, DIAMONDS, HEARTS, SPADES }; 
enum       Rank { ACE = 1, JACK = 11, QUEEN, KING }; 
#endif

void print(Suit);

int main (int argc, char** argv)
{
    Suit firstCardSuit = Suit::HEARTS, secondCardSuit = Suit::SPADES;
    // Specifying "Suit::" is required for enum class type
    //  unless you say "using enum class Suit;"
    
    Rank myRank = Rank (8);
    myRank = Rank(int(myRank) + 1);
    myRank = Rank(int(myRank) + 1); // ack, that's a lot of casting!

    sout << "All possible cards:\n";
    
    for (int s = int(Suit::CLUBS); s <= int(Suit::SPADES); ++s) 
    {                                 // can't declare s as Suit; ++s
                                      //  wouldn't compile.
                                      // Also, must cast to int explicitly
        for (int r = int(Rank::ACE); r <= int(Rank::KING); ++r)
                                      // Same for declaring r as Rank
        {
	    // prints rank as 1, 2, ... 13 -- clunky
	    // But Exercise 3 fixes that
	    sout << r;
	    print(Suit(s));
	    sout << "...";
	}
	sout << '\n';
    }
                                
    int daysLeftTillVacation = int(Rank::QUEEN);
    // if you want to do this weird thing,
    // you must insist (by casting)

    myRank = Rank(14);                   // way weird, but C++ won't complain

	sout << "Hit any key to end.\n";
    SSDL_WaitKey ();

    return 0;
} 

void print(Suit suit)
{
#ifdef __cpp_using_enum // do the "using enum," if supported
    using enum Suit;
#endif

    switch (suit)
    {
    case CLUBS:    sout << 'C'; break;
    case DIAMONDS: sout << 'D'; break;
    case HEARTS:   sout << 'H'; break;
    case SPADES:   sout << 'S'; break;
    default:       sout << '?'; break;
    }
}
