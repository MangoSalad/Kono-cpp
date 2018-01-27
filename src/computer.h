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

};

#endif