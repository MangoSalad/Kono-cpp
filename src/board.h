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

        // checks if the spot can moved to 
        bool isValidLocationToMove(int a_row, int a_column,bool isSuperPiece = false);

        // checks if the spot on the board is open
        bool isValidOpenLocation(int a_row, int a_column);

        // updates a position of the board 
        void updateBoard(int a_initialRow, int a_initialColumn, int a_finalRow, int a_finalColumn,char a_color);

        // gets size of board
        int getBoardSize() const { return m_boardSize; };

        // get specific piece at location
        char getPieceAtLocation(int a_row, int a_column) const;
    
    protected:

    private:
        // Size of the Board.
        int m_boardSize;

        // checks if the piece can be upgraded to super piece
        bool isReadyToUpgrade(int a_row,char a_color);

        //board
        std::vector <std::vector <char> > * boardTable;
};

#endif