//CardGroup class (playing cards)
//  -- from C++20 for Lazy Programmers

#include "cardgroup.h"

using namespace std;

namespace Cards
{
    void CardGroup::copy(const CardGroup& other)
    {
        howMany_ = other.size();                  // copy howMany_...

        for (unsigned int i = 0; i < size(); ++i) // ...and the contents
            (*this)[i] = other[i];
    }

    bool CardGroup::operator== (const CardGroup& other) const
    {
        if (size() != other.size()) return false;   // size this same?

        for (unsigned int i = 0; i < size(); ++i)   // ...and every element?
            if ((*this)[i] != other[i]) return false;

        return true;    
    }

    Card& CardGroup::operator[] (unsigned int index)
    {
        if (index >=  size()) throw OutOfRange ();
        else                  return contents_[index];
    }

    Card  CardGroup::operator[] (unsigned int index) const
    {
        if (index >=  size()) throw OutOfRange ();
        else                  return contents_[index];
    }

    void CardGroup::addCard (const Card& c)
    {
        if (isFull       ( )) throw OutOfRange ();
        else contents_[howMany_++] = c; 
    }

    Card CardGroup::remove    (unsigned int index)
    {
        if (index >= size()) throw OutOfRange ();

        Card result = (*this) [index];

        // This loop copies each Card *after* index, back 1 slot.
        // So the array might look like so, if you try to remove card#1:
        // K♦ 2♣ 8♥ J♦
        // K♦ 8♥ 8♥ J♦
        // K♦ 8♥ J♦ J♦
        // ...then we reduce howMany_ and have
        // K♦ 8♥ J♦  
        for (unsigned int i = index; i < size()-1; ++i)  
            (*this)[i] = (*this)[i+1];

        --howMany_;

        return result;
    }

    void CardGroup::addCardLegally(const Card& other)
    {
        if (isFull()) throw IllegalMove();
        addCard(other);
    }

    void CardGroup::print (ostream& out) const
    {
        if (isEmpty ()) 
            out << "---"; 
        else 
            for (unsigned int i = 0; i < size(); ++i) 
                out << (*this)[i] << ' ';
    }
} //namespace Cards
