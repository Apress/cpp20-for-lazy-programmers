//Program to do a few things with a Tic-Tac-Toe board
//              -- from _C++20 for Lazy Programmers_

#include "SSDL.h"

//Dimensions of board and text notes
constexpr int MAX_ROWS     =   3, MAX_CLMS    =   3,
              ROW_WIDTH    = 100, CLM_WIDTH   = 100,
              BOARD_HEIGHT = 300, BOARD_WIDTH = 300;
                 //enough room for 3x3 grid, given these widths

constexpr int TEXT_LINE_HEIGHT = 20;

//A Square is a place in the TicTacToe board
enum class Square { EMPTY, X, O }; 

//Displaying the board
void display(const Square board[MAX_ROWS][MAX_CLMS]);

int main(int argc, char** argv)
{
#ifdef __cpp_using_enum                 //If your compiler can do "using enum"
    using enum Square;                  // ...use it
#endif

    //Shrink the display to fit our board
    // allowing room for 2 lines of text at the bottom;
    // set title
    SSDL_SetWindowSize     (BOARD_WIDTH,
                            BOARD_HEIGHT + TEXT_LINE_HEIGHT * 2);
    SSDL_SetWindowTitle("Hit any key to end.");

    //Colors
    SSDL_RenderClear       (SSDL_CreateColor(30, 30, 30)); //charcoal
    SSDL_SetRenderDrawColor(SSDL_CreateColor(245, 245, 220)); //beige

    //The board, initialized to give X 3 in a row
#ifdef __cpp_using_enum                 //If your compiler can do "using enum"
    Square board[MAX_ROWS][MAX_CLMS] =  // ...no need for "Square::" before each value
        { {EMPTY, EMPTY,     X},
          {EMPTY,     X, EMPTY},
          {    X,     O,     O} };
#else                                   //else there is
    Square board[MAX_ROWS][MAX_CLMS] =
        { {Square::EMPTY, Square::EMPTY, Square::X    },
          {Square::EMPTY, Square::X,     Square::EMPTY},
          {Square::X,     Square::O,     Square::O    } };
#endif

    display (board);           //display it

    //Be sure the user knows what he's seeing is the right result
    SSDL_RenderText("You should see 3 X's diagonally, ",
                    0, MAX_ROWS * ROW_WIDTH);
    SSDL_RenderText("and two O's in the bottom row.",
                    0, MAX_ROWS * ROW_WIDTH + TEXT_LINE_HEIGHT);

    SSDL_WaitKey();

    return 0;
}

void display(const Square board[MAX_ROWS][MAX_CLMS])
{
    //Make 'em static: loaded once, and local to the only function
    // that needs 'em. What's not to like?
    static const SSDL_Image X_IMAGE = SSDL_LoadImage("media/X.png");
    static const SSDL_Image O_IMAGE = SSDL_LoadImage("media/O.png");

    //draw the X's and O's
    for (int row = 0; row < MAX_ROWS; ++row)
        for (int clm = 0; clm < MAX_CLMS; ++clm)
            switch (board[row][clm])
            {
            case Square::X: SSDL_RenderImage(X_IMAGE,
                                             clm*CLM_WIDTH, row*ROW_WIDTH);
                            break;
            case Square::O: SSDL_RenderImage(O_IMAGE,
                                             clm*CLM_WIDTH, row*ROW_WIDTH);
            }

    //draw the lines for the board:  first vertical, then horizontal
    //doing this last stops X and O bitmaps from covering the lines 
    constexpr int LINE_THICKNESS = 5;

    SSDL_RenderFillRect(CLM_WIDTH     - LINE_THICKNESS / 2, 0,
                        LINE_THICKNESS, BOARD_HEIGHT);
    SSDL_RenderFillRect(CLM_WIDTH * 2 - LINE_THICKNESS / 2, 0,
                        LINE_THICKNESS, BOARD_HEIGHT);
    SSDL_RenderFillRect(0, ROW_WIDTH  - LINE_THICKNESS / 2,
                        BOARD_WIDTH, LINE_THICKNESS);
    SSDL_RenderFillRect(0, ROW_WIDTH*2- LINE_THICKNESS / 2,
                        BOARD_WIDTH, LINE_THICKNESS);
}
