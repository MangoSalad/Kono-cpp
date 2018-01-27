#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include "game.h"

class tournament {
    public:
        
        //default constructor
        tournament();

        // Load a game froma  filer
        tournament(std::string a_savedGame);

        //add constructor for loading game

        //add destructor for saving game

    protected:

    private:

        bool loadSavedFile(std::string a_savedGame);

        // Filename of saved game.
        std::string m_savedGame;
        unsigned short m_tournamentRound;

        // Prompts user to decide if they would like to play another round.
        bool continueGame();

        // Current game round
        game * round;

        // List of attributes loaded from saved game file.
        unsigned short m_tournamentRoundFromFile;
        unsigned short m_computerScoreFromFile;
        char m_computerColorFromFile;
        unsigned short m_humanScoreFromFile;
        char m_humanColorFromFile;

        std::vector <std::vector <char> > * m_boardTableFromFile;
        unsigned short m_boardSizeFromFile;
        char m_nextPlayerFromFile;


};

#endif