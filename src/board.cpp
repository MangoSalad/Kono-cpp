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

board::board(unsigned short a_boardSize, std::vector< std::vector <char> > &a_boardTable)
{
    m_boardSize = a_boardSize;
    boardTable = &a_boardTable;
    //memcpy(boardTable,boardTable,a_boardSize*sizeof(char));
}

bool board::isValidPieceToMove(char a_color, int a_row, int a_column)
{
    if(a_row - 1 < 0 || a_column - 1 < 0 || a_row - 1 >= m_boardSize || a_column - 1 >= m_boardSize) 
    {
        return false;
    }
    else
    {
        return ((*boardTable)[a_row-1][a_column-1] == a_color || (*boardTable)[a_row-1][a_column-1] == tolower(a_color,std::locale()) ) ? true : false;
    }
}

// obvi needs better logic
bool board::isValidLocationToMove(int a_row, int a_column,bool isSuperPiece)
{
    if(a_row - 1 < 0 || a_column - 1 < 0 || a_row - 1 >= m_boardSize || a_column - 1 >= m_boardSize) 
    {
        return false;
    }
    else
    {
        if(isSuperPiece)
        {
            return true;
        }
        else
        {
            return ((*boardTable)[a_row-1][a_column-1] != 'W' && (*boardTable)[a_row-1][a_column-1] != 'B') ? true : false;
        }
    }
}

// obvi needs better logic
bool board::isValidOpenLocation(int a_row, int a_column)
{
    if(a_row - 1 < 0 || a_column - 1 < 0 || a_row - 1 >= m_boardSize || a_column - 1 >= m_boardSize) 
    {
        return false;
    }
    else
    {
        return ((*boardTable)[a_row-1][a_column-1] == '+') ? true : false;
    }
}

void board::updateBoard(int a_initialRow, int a_initialColumn, int a_finalRow, int a_finalColumn, char a_color)
{
    if(isReadyToUpgrade(a_finalRow,a_color))
    {
        (*boardTable)[a_finalRow-1][a_finalColumn-1] = tolower(a_color,std::locale());
    }
    else
    {
        if((*boardTable)[a_initialRow-1][a_initialColumn-1] == tolower(a_color,std::locale()))
        {
            (*boardTable)[a_finalRow-1][a_finalColumn-1] = tolower(a_color,std::locale());    
        }
        else
        {
            (*boardTable)[a_finalRow-1][a_finalColumn-1] = a_color;
        }
    }
    (*boardTable)[a_initialRow-1][a_initialColumn-1] = '+';
    
}

bool board::isReadyToUpgrade(int a_row,char a_color)
{
    if( (a_color == 'W' || a_color == 'w' ) && (a_row-1) == (m_boardSize -1) )
    {
        return true;
    }
    else if ( (a_color == 'B' || a_color == 'b' ) && (a_row-1) == 0 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

char board::getPieceAtLocation(int a_row, int a_column) const
{
    if(a_row - 1 < 0 || a_column - 1 < 0 || a_row - 1 >= m_boardSize || a_column - 1 >= m_boardSize) 
    {
        return ' ';
    }
    else
    {
        return (*boardTable)[a_row-1][a_column-1];
    }
};