//class Montana, for a game of Montana solitaire
//    -- from _C++20 for Lazy Programmers_

#include <iostream>
#include "deck.h"
#include "io.h"       // for bool getAnswerYorN (const char[]);
#include "montana.h"

using namespace std;

    // Playing the game

// This function sets up the grid so we already won; deck and waste
//   are set up appropriately. Used to test detectVictory function

void setupForVictory(Cell grid_[Montana::ROWS][Montana::CLMS], 
                     Deck& deck, Waste&  waste)
{
        // Fill each row with (all 1 suit) 2, 3, ... K, (empty)
    for (unsigned int row = 0; row < Montana::ROWS; ++row)
        for (unsigned int clm = 0; clm < Montana::CLMS - 1; ++clm)
            grid_[row][clm].addCardLegally (Card (Rank(clm + 2), 
                                                  Suit(row)));

        // empty deck
    while (! deck.isEmpty())  deck.deal();

#ifdef __cpp_using_enum 
    using enum Suit, enum Rank;
#endif
    
    // put the aces in waste
    while (!waste.isEmpty()) waste.removeTop();
    for (Suit s = HEARTS; s <= SPADES; ++s)
        waste.addCardLegally(Card(ACE, s));
}

void Montana::play ()
{
    Deck  deck;
    Waste waste;
    bool  isVictory = false;

    resetGrid(); // prepare for deal by ensuring grid is empty

    for (int turn = 1; turn <= MAX_TURNS && ! isVictory; ++turn)
    {
        cout << "********************* New turn! "
                "**********************\n";

        // To test detectVictory func, uncomment setupForVictory,
        // comment out deal, and see if isVictory becomes true
        // setupForVictory(grid_, deck, waste);

        deck.shuffle ();             // Shuffle deck
        deal (deck, waste);          // fill grid with cards
                                     //   and remove aces                                     
        identifyEmptyCells ();       // remember where the aces were
                                     //   in a list of 4 emptyCells_
                                     
        bool letsQuitOrEndTurn = false;       
        isVictory = detectVictory(); // already won? Unlikely, but...

        while (! isVictory && ! letsQuitOrEndTurn)
        {
            display(); 
            makeLegalMove (letsQuitOrEndTurn); // play a turn
            isVictory=detectVictory();         // did we win?
        }

        cleanup (deck, waste);        // collect cards for redeal

        // If user won, we go on and leave loop
        // If we're out of turns, we go on and leave loop
        // Otherwise give user a chance to quit
        if (!isVictory && turn < MAX_TURNS)
            if (getYorNAnswer("Quit game (Y/N)?"))
                break;
    }

    congratulationsOrCondolences (isVictory);
}

void Montana::makeLegalMove (bool& letsQuitOrEndTurn)
{
    bool isValidMove = false;

    do
    {
        cout << "Move (e.g. A 1 5 to fill cell A with "
             << "the card at row 1, clm 5; q to quit/end turn)? ";

        // Which empty space will we fill -- or are we quitting?
        char letter; cin >> letter;
        if (toupper(letter) == 'Q') letsQuitOrEndTurn = true; 
        else
        {
            int emptyCellIndex = toupper(letter) - 'A';

            try
            {
                // Which cell are we moving from?
                GridLoc from;  cin >> from;
                // Which cell are we moving to?
                GridLoc to = emptyCells_[emptyCellIndex];

                // If the empty cell exists, and is really empty...
                if (inRange(emptyCellIndex) && cellAt(to).isEmpty())
                    // if card to move exists, and move is legal...
                    if (!cellAt(from).isEmpty() &&
                        canGoHere(cellAt(from).top(), to))
                    {
                        isValidMove = true;
                        makeMove(from, to);
                        emptyCells_[emptyCellIndex] = from;
                    }
            }
            catch (const BadInput&) {}
                // reading GridLoc went bad -- just try again
        } 
    } while (! isValidMove && ! letsQuitOrEndTurn);
}

void Montana::makeMove  (const GridLoc& oldLoc, 
                         const GridLoc& newLoc)
{
    cellAt(newLoc).addCardLegally (cellAt(oldLoc).removeTop ());
}

bool Montana::detectVictory () const // You win if all cells are correct
{
    bool result = true;

    for (unsigned int row = 0; row < ROWS && result; ++row)
        for (unsigned int clm = 0; clm < CLMS - 1 && result; ++clm)
            // skip last clm; if it's off we'll notice elsewhere
            if (! cellIsCorrect (row, clm))
                result = false;

    return result;
}

void Montana::congratulationsOrCondolences (bool isVictory) const
{
    if (isVictory) cout << "Whoo-hoo!  You won!\n";
    else           cout << "You lost!\n";
}

// Displaying

void Montana::display       () const
{
    // First, print column numbers at top
    cout << "     "; // this is for alignment with subsequent rows
    for (unsigned int clm = 0; clm < CLMS; ++clm)
        if (clm < 10) cout<<clm<<"    "; else cout<<clm<<"   ";

    cout << endl;

    // Then print each row
    for (unsigned int row = 0; row < ROWS; ++row)   
    {                                               
        cout << row << ":  ";                       
                                                    
        for (unsigned int clm = 0; clm < CLMS; ++clm)
            if (grid_[row][clm].isEmpty ())
                cout << ">" <<whichEmptyCell (row, clm) 
                     << "<  "; 
            else
                cout << grid_[row][clm] << " ";
        cout << endl;
    }
}

// Dealing and redealing

void Montana::deal (Deck& deck, Waste& waste)
{
    // Deal out all the cards
    for (unsigned int row = 0; row < ROWS; ++row)
        for (unsigned int clm = 0; clm < CLMS; ++clm)
            if (grid_[row][clm].isEmpty ())
                grid_[row][clm].addCardLegally (deck.deal());

    // Remove aces
    for (unsigned int row = 0; row < ROWS; ++row)
        for (unsigned int clm = 0; clm < CLMS; ++clm)
            if (grid_[row][clm].top ().rank () == Rank::ACE)
                waste.addCardLegally (grid_[row][clm].removeTop ());
}

void Montana::cleanup (Deck& deck, Waste& waste)// collect cards
                                                // for redeal
{
    for (unsigned int row = 0; row < ROWS; ++row)
    {
        bool weAreInTheOrderedPartOfRow = true; 
        // don't collect cards from ordered part

        for (unsigned int clm = 0; clm < CLMS; ++clm)
        {
            // notice if we're leaving ordered part
            if (weAreInTheOrderedPartOfRow)     
            {               
                if (! cellIsCorrect (row, clm))
                    weAreInTheOrderedPartOfRow = false;
            }

            // if in unordered part, collect any cards you find
            if (! weAreInTheOrderedPartOfRow && 
                grid_[row][clm].isFull())
                deck.addCard (grid_[row][clm].removeTop ());
        }
    }

    // Now add waste to the deck
    while (! waste.isEmpty ()) deck.addCard (waste.removeTop());   
}

void Montana::resetGrid () // make it empty
{
    for (unsigned int row = 0; row < ROWS; ++row)
        for (unsigned int clm = 0; clm < CLMS; ++clm)
            if (! grid_[row][clm].isEmpty())
                grid_[row][clm].removeTop();
}

// Finding empty cells

void Montana::identifyEmptyCells ()     
{
    int whichEmptyCell = 0;
    
                            // For each empty cell
    for (unsigned int row = 0; row < ROWS; ++row) 
        for (unsigned int clm = 0; clm < CLMS; ++clm)
            if (grid_[row][clm].isEmpty())
            {
                            // store its loc in emptyCells_ array
                emptyCells_[whichEmptyCell++] = GridLoc(row, clm);
                if (whichEmptyCell > NUM_EMPTY_CELLS)
                    throw OutOfRange();
            }
}

char Montana::whichEmptyCell (int row, int clm) const 
               // used for printing:
               // display needs to know whether to print A B C or D
{
    static constexpr int NOT_FOUND = -1;
    int result = NOT_FOUND; 

    for (int i = 0; i < NUM_EMPTY_CELLS; ++i)
        if (emptyCells_[i].row_ == row && emptyCells_[i].clm_ == clm) 
            result = i;

    if (result == NOT_FOUND) throw OutOfRange ();

    return result+'A'; // which one is 0-3, but we display as A-D
}

    // Verifying valid move

bool Montana::canGoHere(const Card& c, const GridLoc& loc) const
{
    // Can't have Card c here if:
    //  "here" is not in bounds of the array
    // If it's clm 0, c must be a 2
    // If not, prev cell in row must not be empty
    //  and c must follow it, in suit

    if (!inRange(loc))                        return false;
    if (loc.clm_ == 0)                        return c.rank() == Rank(2);
    if (grid_[loc.row_][loc.clm_-1].isEmpty())return false;
    return canFollow(c, grid_[loc.row_][loc.clm_-1].top());
}
