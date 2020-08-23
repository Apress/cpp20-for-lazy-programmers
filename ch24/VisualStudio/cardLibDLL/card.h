//Card class
//  -- from _C++20 for Lazy Programmers_

#ifndef CARD_H
#define CARD_H

#include <iostream>
#include "cardsSetup.h"  // defines DECLSPEC

namespace cards
{
    // Rank and Suit:  integral parts of Card

    // I make these global so that I don't have to forget
    //  "Card::" over and over when I use them.

#ifdef __cpp_using_enum            
    enum class Rank  { ACE=1,  JACK=11, QUEEN, KING    }; // Card rank
    enum class Suit  { HEARTS, DIAMONDS, CLUBS, SPADES }; // Card suit
    enum class Color { BLACK,  RED                     }; // Card color
#else // Just in case the compiler doesn't handle using enum class yet...
    enum       Rank  { ACE=1,  JACK=11, QUEEN, KING    }; // Card rank
    enum       Suit  { HEARTS, DIAMONDS, CLUBS, SPADES }; // Card suit
    enum       Color { BLACK,  RED                     }; // Card color
#endif

    inline
    Color toColor(Suit s)           // DECLSPEC isn't needed for inlines
    {
#ifdef __cpp_using_enum 
        using enum Suit;
        using enum Color;
#endif

        if (s == HEARTS || s == DIAMONDS) return RED; else return BLACK;
    } 

    // I/O on Rank and Suit
    DECLSPEC std::ostream& operator<< (std::ostream& out, Rank r);
    DECLSPEC std::ostream& operator<< (std::ostream& out, Suit s);
    DECLSPEC std::istream& operator>> (std::istream& in, Rank& r);
    DECLSPEC std::istream& operator>> (std::istream& in, Suit& s);

    // Told you we'd find a way to do arithmetic with enums...
    inline Rank operator+  (Rank  r, int t) { return Rank(int(r) + t); }
    inline Rank operator+= (Rank& r, int t) { return r = r + t;        }
    inline Rank operator++ (Rank& r) { r = Rank(int(r) + 1); return r; }
    inline Rank operator++ (Rank& r, int) 
    { 
        Rank result = r; ++r; return result; 
    }

    inline Suit operator++ (Suit& s) { s = Suit(int(s) + 1); return s; }
    inline Suit operator++ (Suit& s, int) 
    { 
        Suit result = s; ++s; return result; 
    }

    class BadRankException {};  // used if a Rank is out of range
    class BadSuitException {};  // used if a Suit is out of range

    // ...and class Card.

    class Card
    {
    public:
        Card (Rank r = Rank(0), Suit s = Suit(0)) : 
            rank_ (r), suit_ (s)               
        {       
        }
        Card(const Card& other) : Card(other.rank_, other.suit_) {}
    
        Card& operator= (const Card& other) 
        {
            rank_ = other.rank(); suit_ = other.suit (); return *this;
        }

        bool operator== (const Card& other) const 
        { 
            return rank() == other.rank () && suit() == other.suit(); 
        }
#ifndef __cpp_impl_three_way_comparison   // Old compiler? Gotta make !=
        bool operator!= (const Card& other) const
        {
            return !(*this == other);
        }
#endif

        Suit  suit () const { return suit_;            }
        Rank  rank () const { return rank_;            }
        Color color() const { return toColor (suit()); }

        void print (std::ostream &out) const { out << rank() << suit(); }
        DECLSPEC void read  (std::istream &in );
    private:
        Suit suit_;
        Rank rank_;
    };

    inline std::ostream& operator<< (std::ostream& out, const Card& foo)
    {
        foo.print (out); return out;
    }

    inline std::istream& operator>> (std::istream& in,        Card& foo)
    {
        foo.read  (in);  return in;
    }
} //namespace cards
#endif //CARD_H
