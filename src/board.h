#ifndef BOARD_H
#define BOARD_H

#include "stdafx.h"

class board {
    public:
        // Start new board.
        board(unsigned short a_boardSize);

        // Load board from file.
        board(unsigned short a_boardSize, std::vector< std::vector <char> > &a_boardTable);

        // Return current state of the board.
        std::vector <std::vector <char> > & getBoard() const { return *boardTable; };

        // Sets the initial board state.
        //void setInitialBoardState();

        // Checks if the piece selected to move is valid.
        bool isValidPieceToMove(char a_color, int a_row, int a_column);

        bool isValidLocationToMove(int a_row, int a_column);

        void updateBoard(int a_initialRow, int a_initialColumn, int a_finalRow, int a_finalColumn,char a_color);

        int getBoardSize() const { return m_boardSize; };
    
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
        int m_boardSize;

        //board
        std::vector <std::vector <char> > * boardTable;
};

#endif