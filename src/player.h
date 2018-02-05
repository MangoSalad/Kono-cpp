#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"

class player{
    public:
        
        player();
        
        virtual void play(std::vector< std::vector <char> > &boardTable);

        // provides help to user for strategy.
        void help(board &gameBoard,char a_color,char a_opponentColor);


    protected:
    private:
        board * localBoard;
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
        

        // Updates variables pertaining the computer player so that computer can make decisions.
        void updateState();

        // Get pieces to move offensively.
        std::pair<int,int> pickRandomPiece();

        // Offensive Strategy
        void playOffensively();        

        // Defensive Strategies
        bool blockFromWest();
        bool blockFromEast();

        // Capture strategy
        bool playCapture();

        // Retreat Strategy
        bool checkForRetreat();
        void playRetreat();

        // Output to console decisions of the computer.
        void showDefenseDecision(int a_initialRow, int a_initialColumn,std::string a_direction, int a_finalRow, int a_finalColumn);
        void showOffenseDecision(int a_initialRow, int a_initialColumn,std::string a_direction, int a_finalRow, int a_finalColumn);
        void showRetreatDecision(int a_initialRow, int a_initialColumn,std::string a_direction, int a_finalRow, int a_finalColumn);
        void showCaptureDecision(int a_initialRow, int a_initialColumn,std::string a_direction, int a_finalRow, int a_finalColumn);
};

#endif