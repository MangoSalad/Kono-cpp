#ifndef HUMAN_H
#define HUMAN_H

#include "player.h"
#include "board.h"

class human : public player {
    public:
        human(char a_Color);
        void play(board &gameBoard);
    private:
        char m_color;

};

#endif