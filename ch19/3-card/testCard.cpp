//Card class tester
//  -- from C++20 for Lazy Programmers

#include <iostream>
#include <cassert> 
#include "card.h"

using namespace std;

int main ()
{
#ifdef __cpp_using_enum 
    using enum Suit;
    using enum Rank;
    using enum Color; 
#endif

    // Test ctors are doing things right... 
    //   and ==, !=, and access functions
    const Card ACE_OF_SPACES(ACE, SPADES);
    const Card COPY_OF_ACE_OF_SPACES(ACE_OF_SPACES);

    assert (ACE_OF_SPACES ==COPY_OF_ACE_OF_SPACES);
    assert (COPY_OF_ACE_OF_SPACES.rank() == ACE && 
            COPY_OF_ACE_OF_SPACES.suit() == SPADES);
    assert (toColor(HEARTS) == RED);
    assert (COPY_OF_ACE_OF_SPACES.color() == BLACK);

    // Now without things being const
    Card someCard;
    assert(someCard == Card(Rank(0), Suit(0)));
    assert(someCard != ACE_OF_SPACES);
    someCard        = ACE_OF_SPACES;
    assert(someCard == ACE_OF_SPACES);
    
    cout << "Enter 3 cards, using S for spades, H for hearts, etc.\n"
        << "E.g. KS, 10H, 2C.  You can enter bogus ones like 12H or 5X.\n"
        << "Use 0 for 10.\n";

    // Test I/O, and exception throwing
    static constexpr int INPUT_TRIALS = 3 ;
    for (int i = 0; i < INPUT_TRIALS; ++i)
        try
        {
            Card inputCard;
            cout << "? ";
            cin >> inputCard;
            cout << "You entered " << inputCard << endl;
        }
        catch (const BadRankException&)
        {
            cout << "The rank is invalid.\n";
        }
        catch (const BadSuitException&)
        {
            cout << "The suit is invalid; rank may be bad too.\n";
        }

    cout << "\nIf there are no unexpected error messages, "
         << "it looks like class Card is working!\n";

    return 0;
}
