#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"

class player{
    public:
        player();
        virtual void play(std::vector< std::vector <char> > &boardTable);

        // provides help to user for strategy.
        void strategyHelp(char a_color,board &gameBoard);
        void updateStateForStrategy(board &gameBoard);

        bool checkDefensiveWestStrategy(board &gameBoard);
        bool checkDefensiveEastStrategy(board &gameBoard);
        void checkOffensiveStrategy(board &gameBoard);
        std::pair<int,int> pickOffensivePiece();

    protected:
    private:
        board * gameBoard;
        int m_boardSize;

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
};

#endif