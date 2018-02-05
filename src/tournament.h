/*
*   This class contains the following:
*       1. Starts new round.
*       2. Loads existing round from saved game filed.
*       3. Holds current score for human and computer player.
*       4. Displays menu for player to interact with (play game, save game, help mode, and quit game)
*/

#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include "game.h"

class tournament {
    public:
        
        // Starts new game.
        tournament();

        // Loads existing game from file.
        tournament(std::string a_savedGame);

        // Destructor responsbile for freeing resources.
        ~tournament();

        // Shows menu.
        void showMenu() const;

        // Saves current game to file.
        void saveGame(std::string a_fileName) const;

        // Calls human to play game.
        void playGame() const;

        // Enters help mode.
        void helpGame() const;

        // Print winner and overall tournament score to the screen.
        void showWinner() const;

        // Return winner.
        char getWinner() const;

        // Calculate tournament scores.
        void calculateScores();

        // Checks to see if game won.
        bool isGameWon();

        // Creates new round.
        void newRound(char winnerFromGame);

        // Deduct 5 points from player for quiting game.
        void quitGamePenalty();

    protected:

    private:

        // Current game round
        game * round;

        // Current Round #.
        unsigned short m_tournamentRound;

        // Player tournament scores.
        int m_computerScore;
        int m_humanScore;

        // Attributes loaded from existing game file.
        char m_computerColorFromFile;
        char m_humanColorFromFile;
        std::vector <std::vector <char> > * m_boardTableFromFile;
        unsigned short m_boardSizeFromFile;
        char m_nextPlayerFromFile;

        // Filename of saved game.
        std::string m_savedGame;

        // Utility Functions        

        // Load existing game file and perform checks on it.
        bool loadSavedFile(std::string a_savedGame);

        
};

#endif