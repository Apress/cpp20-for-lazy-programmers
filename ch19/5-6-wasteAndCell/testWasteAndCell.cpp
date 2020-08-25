// Test CardGroup, Waste, Cell, Deck
//    -- from _C++20 for Lazy Programmers_

#include <iostream>
#include <cassert> // for assert
#include "waste.h"
#include "cell.h"

using namespace std;

int main ()
{
#ifdef __cpp_using_enum 
    using enum Suit;
    using enum Rank;
    using enum Color;
#endif

    // Test Waste
    Waste waste; 
    Waste w1 (waste);     assert (w1 == waste);
    
    // Test Cell, thereby testing more of Waste
    Cell cell;
    cout << "No card:             " << cell << '\n';
    cell.addCardLegally (Card (Rank(2), CLUBS));
    try
    {
        cell.addCardLegally (Card());
        cout << "Error: added a second card to a cell!\n";
    }
    catch (const IllegalMove&) {}

    Cell c1 = cell;      assert (c1 == cell);
    assert (c1.isFull ());
    assert (! c1.Waste::isFull ());
	cout << "This is 2 of clubs: " << cell << '\n';;
    cell.removeTop ();
    try
    {
        cell.top ();
        cout << "Error: can't look at top of empty cell!\n";
    }
    catch (const OutOfRange&) {}

    cout << "If no errors were reported, testWasteAndCell "
        "must have succeeded!\n";

    return 0;
}
