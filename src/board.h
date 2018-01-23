#ifndef BOARD_H
#define BOARD_H

class board {
    public:
        board(unsigned short a_boardSize);

        // Return current state of the board.
        int** getBoard() { return table; };
    
    protected:
        //  Set of variables that reflects the state of the board at a certain position.
        enum positionState {blank,white,black,superWhite,superBlack};

    private:
        // Size of the Board.
        unsigned short m_boardSize;

        //board
        int ** table;
};

#endif