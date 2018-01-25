#include "board.h"
#include "stdafx.h"

board::board(unsigned short a_boardSize)
{
    // Save size locally.
    m_boardSize = a_boardSize;

    // Initialize the entire table.
    std::vector <char> rows (m_boardSize,'+');

    boardTable = new std::vector < std::vector<char> > (m_boardSize,rows);

    // Place pieces on the board.
    for(int i = 0; i < m_boardSize; i++)
    {
        (*boardTable)[0][i] = 'W';
    }

    (*boardTable)[1][0] = 'W';
    (*boardTable)[1][m_boardSize-1] = 'W';

    for(int i = 0; i < m_boardSize; i++)
    {
        (*boardTable)[m_boardSize-1][i] = 'B';
    }

    (*boardTable)[m_boardSize-2][0] = 'B';
    (*boardTable)[m_boardSize-2][m_boardSize-1] = 'B';
    
};