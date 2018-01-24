#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include "game.h"

class tournament {
    public:
        
        //default constructor
        tournament();

        //add constructor for loading game

        //add destructor for saving game

    protected:

    private:

        unsigned short tournamentRound;

        // Prompts user to decide if they would like to play another round.
        bool continueGame();

        game * round;

};

#endif