#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "player.h"
#include "human.h"
#include "computer.h"
#include "boardView.h"

class game {
    public:
        game();

        // Load round from file.
        game(char a_colorHumanPlayer, char a_colorComputerPlayer, char a_currentTurn, unsigned short a_boardSize, std::vector< std::vector <char> > &boardTable);

        ~game(); 

        // If winner of previous round, set player manually.
        void setFirstPlayer(char a_firstPlayer);

        // If winner of previous round, set player color manually.
        //void setWinnerFirstPlayerColor();

    protected:

    private:

        // Calls menu, and determines what to do after menu
        void continueGame();

        // Calculate first player. If true -> human. Else -> computer;
        void calculateFirstPlayer();

        // If human is first, human selects color. Else, a computer randomly selects the color.
        void setFirstPlayerColor();

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

        // holds who is first player. 'h' for human, 'c' for computer.
        char m_firstPlayer;

        // Color of the human player. Either 'B' for "black" or 'W' for "white" 
        char m_colorHumanPlayer;
        char m_colorComputerPlayer;

        // 'h' for human, 'c' for computer.
        char m_currentTurn;

};

#endif