#ifndef HUMAN_H
#define HUMAN_H

#include "player.h"
#include "board.h"

class human : public player {
    public:

        // Default Constructor
        human(char a_color);
        
        // Accepts user input to make player move.
        void play(board &gameBoard);

    private:
        // Human Player color.
        char m_color;

};

#endif