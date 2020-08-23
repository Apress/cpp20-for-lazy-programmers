//Deck class
//  -- from _C++20 for Lazy Programmers_

#include "pch.h"
#include <cstdlib> // for rand
#define IM_COMPILING_MY_CARD_LIBRARY_RIGHT_NOW  
                   // see setup.h. Must come before card 
                   //  related includes, after "stdafx.h" if any
#include "deck.h"

using namespace std;

namespace cards
{
    DECLSPEC Deck::Deck ()
    {
#ifdef __cpp_using_enum 
        using enum Suit;
        using enum Rank;
#endif

        for (Suit s = HEARTS; s <= SPADES; ++s)
            for (Rank r = ACE; r <= KING; ++r)
                addCard (Card (r, s));
    }

    DECLSPEC void Deck::shuffle ()
    {
        // Not very simple, and not very efficient! 
        //  So: write your own:
        //  clear, simple, and ... O(N).

        CardGroup newDeck; // make a new deck

        while (size() > 0) // while there are cards in this one
            {
                // take a card at random from the deck
                int loc = rand() % size();
                Card c = remove(loc); 

                // add it to newDeck
                newDeck.addCard (c);
            }

        // copy newDeck back into this one
        for (unsigned int i = 0; i < newDeck.size(); ++i)
            addCard(newDeck[i]);
    }
} //namespace cards
