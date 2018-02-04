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

        // Checks if the piece selected to move is valid.
        bool isValidPieceToMove(char a_color, int a_row, int a_column);

        // Checks if the spot can moved to.
        bool isValidLocationToMove(int a_row, int a_column,bool isSuperPiece = false);

        // Checks if the spot on the board is open.
        bool isValidOpenLocation(int a_row, int a_column);

        // Updates a position of the board.
        void updateBoard(int a_initialRow, int a_initialColumn, int a_finalRow, int a_finalColumn,char a_color);

        // Get size of board.
        int getBoardSize() const { return m_boardSize; };

        // Get specific piece at location (row/column).
        char getPieceAtLocation(int a_row, int a_column) const;

        // Get vector of pieces located on the black side.
        std::vector <char> getBlackSide() const;

        // Get vector of pieces located on the white side.
        std::vector <char> getWhiteSide() const;

        // Get the # of remaining black pieces.
        int getNumberOfBlackPieces() const;
        
        // Get the # of remaining white pieces.
        int getNumberOfWhitePieces() const;
    
    protected:

    private:
        
        // Size of the Board.
        int m_boardSize;

        // Checks if the piece can be upgraded to super piece.
        bool isReadyToUpgrade(int a_row,char a_color);

        // Table
        std::vector <std::vector <char> > * boardTable;
};

#endif