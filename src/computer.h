#ifndef COMPUTER_H
#define COMPUTER_H

#include "player.h"
#include "board.h"

class computer : public player {
    public:

        // Default constructor.
        computer(char a_color);

        // Decides on computer strategy for turn.
        void play(board &gameBoard);
    
    protected:

    private:
        
        // Board object
        board * localBoard;

        // Color of the computer.
        char m_color;

        // Coloer of the opponent.
        char m_opponentColor;

        // Positions of available computer pieces
        std::vector< std::pair<int,int> > * m_availablePieces;
        std::vector< std::vector <char> > boardTable; 
        int m_boardSize;

        // Iterators
        typedef std::vector<char>::iterator colIter;
        typedef std::vector< std::vector<char> >::iterator iter;
        typedef std::vector< std::pair<int,int> >::iterator availablePiecesIter; 
        
        // Position of important deciding pieces.
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