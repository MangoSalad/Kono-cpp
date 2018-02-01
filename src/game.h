#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "player.h"
#include "human.h"
#include "computer.h"
#include "boardview.h"

class game {
    public:
        game();

        // Load round from file.
        game(char a_colorHumanPlayer, char a_colorComputerPlayer, char a_currentTurn, unsigned short a_boardSize, std::vector< std::vector <char> > &boardTable);

        ~game(); 

        // If winner of previous round, set player color manually.
        //void setWinnerFirstPlayerColor();

        void showMenu() const;

        void playRound();

        // Utility Selector Functions

        int getHumanScore() const { return humanScore; };

        int getComputerScore() const { return computerScore; };

        std::string getComputerColor() const { return (m_colorComputerPlayer == 'W') ? "White" : "Black"; };

        std::string getHumanColor() const { return (m_colorHumanPlayer == 'W') ? "White" : "Black"; };

        std::string getNextPlayer() const { return (m_currentTurn == 'h') ? "Human" : "Computer"; };

        std::vector <std::vector <char> > & getBoardState() const { return gameBoard -> getBoard(); };

        unsigned short getBoardSize() const { return m_gameBoardSize; };

        void getHelp();

        void calculateScore();

    protected:

    private:

        // Calls menu, and determines what to do after menu
        void continueGame();

        // Calculate first player. If true -> human. Else -> computer;
        void calculateFirstPlayer();

        // If human is first, human selects color. Else, a computer randomly selects the color.
        void setFirstPlayerColor();
        
        // Sets the size of the board.
        void setBoardSize();

        // Randomly chooses number between 2 - 12. (1 pairs of dice)
        int randomDice();

        // Sums the current score state for player.
        unsigned short calculateScoreForPlayer();
        
        board * gameBoard;
        human  * humanPlayer;
        computer * computerPlayer;
        boardView * display;

        int m_humanScore;
        int m_computerScore;

        unsigned short m_gameBoardSize;

        // Color of the human player. Either 'B' for "black" or 'W' for "white" 
        char m_colorHumanPlayer;
        char m_colorComputerPlayer;

        // 'h' for human, 'c' for computer.
        char m_currentTurn;

};

#endif