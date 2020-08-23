//Tester program for CardGroup
//  -- from _C++20 for Lazy Programmers_

#include <iostream>
#include <cstdlib> // for srand
#include <cassert> // for assert
#include "cardGroup.h"

using namespace std;

int main ()
{
#ifdef __cpp_using_enum 
    using enum Suit;
    using enum Rank;
    using enum Color;
#endif

    // CardGroup
    // Test isFull, isEmpty
    CardGroup group1;
    assert (! group1.isFull()); assert (group1.isEmpty());
    for (int i = 0; i < CardGroup::MAX_SIZE; ++i)
        group1.addCardLegally (Card ());
    try
    {
        group1.addCardLegally (Card());
        cout << "addCardLegally's not finding an error--but should.\n";
    }
    catch (const IllegalMove&) {}
    assert (group1.isFull()); assert (! group1.isEmpty());

    // Test copy ctor, =, ==, !=
    CardGroup group2 = group1; assert (group1 == group2); 
    assert (group1 != CardGroup());

    CardGroup CG1 (Card (ACE, SPADES));        // Test ctors, ==, and !=
    assert (CG1.top () == Card(ACE,SPADES)); 
    Hand CG2 = CG1;                            // Hand == CardGroup
    assert (CG1 == CG2); assert (! (CG1 != CG2));

    CG1.addCardLegally (Card (ACE, DIAMONDS)); // Test size, =, ==, and !=
    assert(CG1.top () == Card(ACE,DIAMONDS));  // addCardLegally
    assert (CG1.size() == 2);   
    assert (! (CG1 == CG2));
    assert (CG1 != CG2);
    CG2 = CG1;
    assert (CG1 == CG2);
    assert (! (CG1 != CG2));
     
    assert (CG1[1] == Card(ACE, DIAMONDS));// Test []
    cout << "Two aces: " << CG1 << endl;

    CG2.remove (0);                     // Test remove
    assert (CG2.top () == Card (ACE, DIAMONDS));

    CG1.removeTop ();                   // Test removeTop
    assert (CG1.top () == Card (ACE, SPADES));
    CG1.removeTop ();
    cout << "No cards: " << CG1 << endl;

    try 
    { 
        CG1.removeTop (); 
        cout << "Error: removeTop should've thrown an exception.\n";
    } 
    catch (const OutOfRange&) { }

    cout << "If no errors were reported, testGroups "
        "must have succeeded!\n";

    return 0;
}
