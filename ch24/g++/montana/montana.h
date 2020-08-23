//class Montana, for a game of Montana solitaire
//  -- from _C++20 for Lazy Programmers_

#include "gridLoc.h"
#include "cell.h"
#include "deck.h"

#ifndef MONTANA_H
#define MONTANA_H

class Montana
{
public:
    static constexpr int ROWS = 4, CLMS  = 13;
    static constexpr int NUM_EMPTY_CELLS =  4;// 4 empty cells in grid
    static constexpr int MAX_TURNS       =  4;// 4 turns allowed


    class OutOfRange {};          // Exception class for card locations 

    Montana                  ()               {};
    Montana                  (const Montana&) = delete;
    Montana& operator=       (const Montana&) = delete;

    void play ();

private:
        // displaying
    void display            () const;

        // dealing and redealing
    void deal               (Cards::Deck& deck, Cards::Waste& waste);
    void cleanup            (Cards::Deck& deck, Cards::Waste& waste); 
    void resetGrid          (); //  make it empty

        // playing a turn
    void makeLegalMove      (bool& letsQuitOrEndTurn);
    void makeMove           (const GridLoc& oldLoc, 
                             const GridLoc& newLoc);
    bool detectVictory      () const;
    void congratulationsOrCondolences(bool isVictory) const;

        // working with empty cells
    
    // store in emptyCells_ the location of each empty cell
    void identifyEmptyCells ();
 
    // which of the empty cells has this row and clm? A B C or D?
    char whichEmptyCell     (int row, int clm) const;
 
    // Is this a valid cell index? It must be 0-3.
    bool inRange(unsigned int emptyCellIndex) const
    {
        return (emptyCellIndex < NUM_EMPTY_CELLS);
    }

        // placing cards

    Cards::Cell&        cellAt(const GridLoc& loc)
    {
        if (inRange(loc)) return grid_[loc.row_][loc.clm_];
        else throw OutOfRange();
    }

    const Cards::Cell& cellAt(const GridLoc& loc) const
    {
        if (inRange(loc)) return grid_[loc.row_][loc.clm_];
        else throw OutOfRange();
    }

    // Is this location within the grid?
    bool inRange(const GridLoc& loc) const
    {
        return (0 <= loc.row_ && loc.row_ < ROWS &&
                0 <= loc.clm_ && loc.clm_ < CLMS);
    }

    // Can Card c follow other card?
    bool canFollow(const Cards::Card& c, const Cards::Card& other) const
    {
        return c.suit() == other.suit() &&
            c.rank() == other.rank() + 1;
    }

    // Can card c go at this location?
    bool canGoHere(const Cards::Card& c, const GridLoc& loc) const;

    // Is the cell at row, clm ordered at its location? That is,
    //     could we put it here if it weren't already?
    bool cellIsCorrect(int row, int clm) const
    {
        return ! grid_[row][clm].isEmpty () &&
               canGoHere(grid_[row][clm].top(), GridLoc(row, clm));
    }
    
    // data members
    Cards::Cell   grid_ [ROWS][CLMS];     // where the cards are
    GridLoc emptyCells_ [NUM_EMPTY_CELLS];// where the empty cells are
};

#endif //MONTANA_H
