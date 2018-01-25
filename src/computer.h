#ifndef COMPUTER_H
#define COMPUTER_H

#include "player.h"

class computer : public player {
    public:
        computer();
        void play();

};

#endif