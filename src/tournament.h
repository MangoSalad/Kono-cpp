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

        ~tournament();

        // Starts menu.
        void showMenu() const;

        // Saves current game to file.
        void saveGame() const;

        // Calls human to play game.
        void playGame() const;

        // Enters help mode.
        void helpGame() const;

    protected:

    private:

        // Current game round
        game * round;

        // Current Round #.
        unsigned short m_tournamentRound;

        unsigned int m_computerScore;
        unsigned int m_humanScore;

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

        // Prompts user to decide if they would like to play another round.
        bool continueGame();
};

#endif