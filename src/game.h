#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "player.h"
#include "human.h"
#include "computer.h"
#include "boardview.h"

class game {
    public:

        // Default constructor.
        game();

        // Constructor that loads existing round from file.
        game(char a_colorHumanPlayer, char a_colorComputerPlayer, char a_currentTurn, unsigned short a_boardSize, std::vector< std::vector <char> > &boardTable);

        // Destructor.
        ~game(); 

        // If winner of previous round, set player color manually.
        //void setWinnerFirstPlayerColor();

        // Show menu to user.
        void showMenu() const;

        // Depending on turn, calls the play() method for computer or human.
        void playRound();

        // Utility Functions

        // I am defining selector functions here for faster compile time.
        
        // Get the computer player's color.
        std::string getComputerColor() const { return (m_colorComputerPlayer == 'W') ? "White" : "Black"; };

        // Get the human player's color.
        std::string getHumanColor() const { return (m_colorHumanPlayer == 'W') ? "White" : "Black"; };

        // Get who is the next player in the round.
        std::string getNextPlayer() const { return (m_currentTurn == 'h') ? "Human" : "Computer"; };

        // Get the state of the board. Return reference of the board by calling getBoard() method in Board class.
        std::vector <std::vector <char> > & getBoardState() const { return gameBoard -> getBoard(); };

        // Get the size of the board.
        unsigned short getBoardSize() const { return m_gameBoardSize; };

        // For human, calls help.
        void getHelp();

        // Calculates the scores of the round upon commpletion.
        void calculateScore();

        // Get the human player score.
        int getHumanScore() const { return m_humanScore; };
        
        // Get the computer player score.
        int getComputerScore() const { return m_computerScore; };

        // Check if pieces have occupied the opponnent's side spaces.
        bool isHomeSideCapture();

    protected:

    private:

        // Pointers to objects of classes.

        // Board Model logic.
        board * gameBoard;

        // Human player logic.
        human  * humanPlayer;

        // Computer player logic.
        computer * computerPlayer;

        // Board View logic.
        boardView * display;

        // Scores for players.
        int m_humanScore;
        int m_computerScore;

        // Board size.
        unsigned short m_gameBoardSize;

        // Color of the human player. Either 'B' for "black" or 'W' for "white" 
        char m_colorHumanPlayer;
        char m_colorComputerPlayer;

        // Holds the current turn. Either 'h' for human, 'c' for computer.
        char m_currentTurn;

        //REVIEW MORE HERE

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

};

#endif