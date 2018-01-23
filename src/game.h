#ifndef GAME_H
#define GAME_H

class game {
    public:
        game();

    protected:

    private:
        unsigned short displayMenu();
        
        // Sets the size of the board.
        void setBoardSize();

        // Randomly chooses number between 2 - 12. (1 pairs of dice)
        unsigned short randomDice();

        // Sums the current score state for player.
        unsigned short calculateScoreForPlayer();
        
        board gameBoard;
        human humanPlayer;
        computer computerPlayer;

        unsigned short humanScore;
        unsigned short computerScore;

};

#endif