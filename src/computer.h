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

        // Color of the computer.
        char m_color;

        // Coloer of the opponent.
        char m_opponentColor;

        // Offensive Strategy
        void playOffensively();        

        // Defensive Strategies
        bool blockFromWest();
        bool blockFromEast();

        // Capture strategy
        bool playCapture();

        // Retreat Strategy
        void playRetreat();

        // Output to console decisions of the computer.
        void showDefenseDecision(int a_initialRow, int a_initialColumn,std::string a_direction, int a_finalRow, int a_finalColumn);
        void showOffenseDecision(int a_initialRow, int a_initialColumn,std::string a_direction, int a_finalRow, int a_finalColumn);
        void showRetreatDecision(int a_initialRow, int a_initialColumn,std::string a_direction, int a_finalRow, int a_finalColumn);
        void showCaptureDecision(int a_initialRow, int a_initialColumn,std::string a_direction, int a_finalRow, int a_finalColumn);

};

#endif