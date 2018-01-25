#ifndef BOARD_H
#define BOARD_H

#include "stdafx.h"

class board {
    public:
        board(unsigned short a_boardSize);

        // Return current state of the board.
        std::vector <std::vector <char> > & getBoard() const { return *boardTable; };

        // Sets the initial board state.
        //void setInitialBoardState();
    
    protected:
        //  Set of variables that reflects the state of the board at a certain position.
        enum positionState {
            BLANK = '+',
            WHITE = 'W',
            BLACK = 'B',
            SUPERWHITE = 'W',
            SUPERBLACK = 'B'
            };

    private:
        // Size of the Board.
        unsigned short m_boardSize;

        //board
        std::vector <std::vector <char> > * boardTable;
};

#endif