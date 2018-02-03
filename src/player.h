#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"

class player{
    public:
        player();
        virtual void play(std::vector< std::vector <char> > &boardTable);

        // provides help to user for strategy.
        void updateState(board &gameBoard);

        void playOffensively(board &gameBoard);
        bool blockFromWest(board &gameBoard);
        bool blockFromEast(board &gameBoard);
        void help(board &gameBoard,char a_color,char a_opponentColor);
        std::pair<int,int> pickRandomPiece();

        // Outputs the decision for the user to play offensively.
        void showOffensiveDecision(int a_initalRow, int a_initialColumn, int a_finalRow, int a_finalColumn);

        // Outputs the decision for the user to play defensively.
        void showDefensiveDecision(int a_initalRow, int a_initialColumn, int a_finalRow, int a_finalColumn);

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