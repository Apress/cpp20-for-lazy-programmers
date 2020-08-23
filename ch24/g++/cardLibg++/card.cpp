//Card class
//  -- from C++20 for Lazy Programmers

#include "card.h"

using namespace std;

namespace Cards
{
    void Card::read  (std::istream &in )       
    { 
        try {   in  >> rank_  >> suit_;  }
        catch (BadRankException&) // if reading rank_ threw an exception
            {
                in >> suit_;          //  consume the suit as well
                throw;                //  and continue throwing the exception
            }
    }

    istream& operator>> (istream& in, Suit& s)
    {
#ifdef __cpp_using_enum 
        using enum Suit;
#endif

        char answer; in >> answer;

        switch (toupper (answer))
            {
            case 'H': s = HEARTS;   break;
            case 'S': s = SPADES;   break;
            case 'C': s = CLUBS;    break;
            case 'D': s = DIAMONDS; break;
            default : throw BadSuitException ();
            }

        return in;
    }

    ostream& operator<< (ostream& out, Suit suit) // prints a Suit
    {
#ifdef __cpp_using_enum 
        using enum Suit;
#endif

        switch (suit)
            {
            case CLUBS  :  out << 'C'; break; 
            case DIAMONDS: out << 'D'; break; 
            case HEARTS :  out << 'H'; break;
            case SPADES :  out << 'S'; break;
            default     :  out << '?'; break; 
            }

        return out;
    }

    // '0'-'0' gives 0, '1'-'0' gives 1, etc. ... so this is how
    //   to convert a digit to an int
    inline int char2Int (char ch) { return ch - '0'; }

    // These comments lined up in Word, honest.
    istream& operator>> (istream& in, Rank& r)
    {
#ifdef __cpp_using_enum 
        using enum Rank;
#endif

        char answer; in>> answer;

        switch (toupper (answer))              // Valid ranks include
            {
            case 'A': r = ACE;   break;            // 'A','J','Q','K'...
            case 'J': r = JACK;  break;
            case 'Q': r = QUEEN; break;
            case 'K': r = KING;  break;
            case '1':                              // "10" (but not 11, etc.)
                in >> answer;                      // get next digit
                r = Rank (10 + char2Int(answer));  // Rank is 10+value of 
                //   next digit
                if (r != Rank(10))                 // Only valid rank starting
                    throw BadRankException();      //   with '1', is 10
                break;
            default : 
                if ('2' <= answer && answer <= '9')// '2'...'9' are valid
                    r = Rank (char2Int (answer));  //  ranks too
                else
                    throw BadRankException ();     // all others are invalid
            }

        return in;
    }

    ostream& operator<< (ostream& out, Rank r)
    {
#ifdef __cpp_using_enum 
        using enum Rank;
#endif

        switch (r)
            {
            case ACE     : out << " A"; break; // lining them up for neatness
            case JACK    : out << " J"; break;
            case QUEEN   : out << " Q"; break;
            case KING    : out << " K"; break;
            case Rank(10): out <<   10; break;    
            default      : out << ' ' << int (r); 
            }

        return out;
    }
} //namespace Cards
