#include "board.h"
#include "stdafx.h"

board::board(unsigned short a_boardSize)
{
    // Save size locally.
    m_boardSize = a_boardSize;

    // Initialize the entire table.
    std::vector <int> rows (5,0);

    boardTable = new std::vector < std::vector<int> > (m_boardSize,rows);
    
};