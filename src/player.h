#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"

class player{
    public:
        
        player();

        virtual void play(std::vector< std::vector <char> > &boardTable);

        // Provides help for human player.
        void help(board &gameBoard,char a_color,char a_opponentColor);


    protected:
        // Board logic.
        board * localBoard;
        int m_boardSize;

        // Color of player, color of opponent. 
        char m_color;
        char m_opponentColor;

        // Positions of available computer pieces.
        std::vector< std::pair<int,int> > * m_availablePieces;
        std::vector< std::vector <char> > boardTable; 

        // Iterators, used for when computer tries to understand state of the board.
        typedef std::vector<char>::iterator colIter;
        typedef std::vector< std::vector<char> >::iterator iter;
        typedef std::vector< std::pair<int,int> >::iterator availablePiecesIter; 
        
        // Piece positions of important pieces.
        std::pair<int,int> m_furthestFriendly;
        std::pair<int,int> m_closestOpponent;
        
        // Get pieces to move offensively.
        std::pair<int,int> pickRandomPiece();

        // Updates variables pertaining the computer player so that computer can make decisions.
        void updateState(board &a_gameBoard, char a_color, char a_opponentColor);

        // Check if retreat is possible.
        bool checkForRetreat();

    private:
        
        // Offensive Strategy for Help Mode.
        void playOffensively();        

        // Defensive Strategies for Help Mode.
        bool blockFromWest();
        bool blockFromEast();

        // Capture strategy for Help Mode.
        bool playCapture();

        // Retreat Strategy for Help Mode.
        void playRetreat();

        // Output to console decisions of the computer for Help Mode.
        void showDefenseDecision(int a_initialRow, int a_initialColumn,std::string a_direction, int a_finalRow, int a_finalColumn);
        void showOffenseDecision(int a_initialRow, int a_initialColumn,std::string a_direction, int a_finalRow, int a_finalColumn);
        void showRetreatDecision(int a_initialRow, int a_initialColumn,std::string a_direction, int a_finalRow, int a_finalColumn);
        void showCaptureDecision(int a_initialRow, int a_initialColumn,std::string a_direction, int a_finalRow, int a_finalColumn);
};

#endif