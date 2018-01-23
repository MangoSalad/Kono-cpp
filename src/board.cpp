#include "board.h"

board::board(unsigned short a_boardSize)
{
    // Save size locally.
    m_boardSize = a_boardSize;

    // Initialize the entire table.
    table = new int*[m_boardSize];
    
    for( int row = 0; row < m_boardSize; row++ )
    {
        // Allocate to the row
        table[row] = new int[m_boardSize];

        for( int col = 0; col < m_boardSize; col++ )
            table[row][col] = false;
    }
};