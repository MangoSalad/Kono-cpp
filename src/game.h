#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "human.h"
#include "computer.h"
#include "boardView.h"

class game {
    public:
        game();

    protected:

    private:

        // Calculate first player. If true -> human. Else -> computer;
        bool calculateFirstPlayer();

        unsigned short displayMenu();
        
        // Sets the size of the board.
        void setBoardSize();

        unsigned short getBoardSize();

        // Randomly chooses number between 2 - 12. (1 pairs of dice)
        unsigned short randomDice();

        // Sums the current score state for player.
        unsigned short calculateScoreForPlayer();
        
        board * gameBoard;
        human  * humanPlayer;
        computer * computerPlayer;
        boardView * display;

        unsigned short humanScore;
        unsigned short computerScore;

        unsigned short gameBoardSize;

};

#endif