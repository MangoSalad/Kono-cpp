#include "board.h"
#include "boardView.h"


void boardView::displayBoard()
{
    //get table
    int ** table = board.getTable();

    for( int row = 0; row < m_boardSize; row++ )
    {
        for( int col = 0; col < m_boardSize; col++ )
            std::cout << table[row][col] << std::endl;
    }
}