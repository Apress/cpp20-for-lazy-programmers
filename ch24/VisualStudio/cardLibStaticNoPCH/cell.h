// Cell class
//        -- from _C++20 for Lazy Programmers_

#ifndef CELL_H
#define CELL_H

#include "waste.h"

namespace cards
{
    class Cell: public Waste 
    {
    public:
        Cell ()                                      {}
        Cell(const Cell& other) : Waste (other)      {}
        Cell& operator= (const Cell& other) = delete;

        // public inheritance, so all public members of Waste are here...

        bool isFull    () const {return ! isEmpty (); } 
    
        void addCardLegally (const Card& card) 
        { 
            if (isFull ()) throw IllegalMove (); // Cell must be empty
            else Waste::addCardLegally (card); 
        }
    };
} //namespace cards
#endif //CELL_H
