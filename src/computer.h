#ifndef COMPUTER_H
#define COMPUTER_H

#include "player.h"
#include "board.h"

class computer : public player {
    public:
        computer(char a_color);
        void play(board &gameBoard);
    
    protected:

    private:
        char m_color;
        char m_opponentColor;

        // Positions of available computer pieces
        std::vector< std::pair<int,int> > * m_availablePieces;
        std::vector< std::vector <char> > boardTable; 

        // Iterators
        typedef std::vector<char>::iterator colIter;
        typedef std::vector< std::vector<char> >::iterator iter;
        typedef std::vector< std::pair<int,int> >::iterator availablePiecesIter; 
        
        std::pair<int,int> m_furthestFriendly;
        std::pair<int,int> m_closestOpponent;
        int m_boardSize;

        // Updates variables pertaining the computer player so that computer can make decisions.
        void updateState(board &gameBoard);

        std::pair<int,int> pickRandomPiece();

        void playOffensively(board &gameBoard);

};

#endif