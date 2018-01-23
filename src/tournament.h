#ifndef TOURNAMENT_H
#define TOURNAMENT_H

class tournament {
    public:
        //default constructor
        tournament();

    protected:

    private:

        // Set the board size. must be 5x5, 7x7, or 9x9.
        void setBoardSize();

        void setHumanPlayer();

        void setComputerPlayer();

};

#endif