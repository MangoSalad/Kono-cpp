#include "board.h"
#include "stdafx.h"

// Constructor for loading new board.
board::board(unsigned short a_boardSize)
{
    // Save size locally.
    m_boardSize = a_boardSize;

    // Initialize the entire table.
    std::vector <char> rows (m_boardSize,'+');
    boardTable = new std::vector < std::vector<char> > (m_boardSize,rows);

    // Place pieces on the board.

    // Place white pieces on white side.
    for(int i = 0; i < m_boardSize; i++)
    {
        (*boardTable)[0][i] = 'W';
    }

    (*boardTable)[1][0] = 'W';
    (*boardTable)[1][m_boardSize-1] = 'W';

    // Place black pieces on black side.
    for(int i = 0; i < m_boardSize; i++)
    {
        (*boardTable)[m_boardSize-1][i] = 'B';
    }

    (*boardTable)[m_boardSize-2][0] = 'B';
    (*boardTable)[m_boardSize-2][m_boardSize-1] = 'B';
    
};

// Constructor for loading existing board from file.
board::board(unsigned short a_boardSize, std::vector< std::vector <char> > &a_boardTable)
{
    m_boardSize = a_boardSize;
    boardTable = &a_boardTable;
}

/* ********************************************************************* 
Function Name: isValidPieceToMove 
Purpose: Checks if a given piece is a valid piece to move.
Parameters: 
            a_color, char that holds the color of the piece.
            a_row, integer for the row coordinate.
            a_column, integer for the column coordinate.
Return Value: Boolean value if the piece is valid to move.
Local Variables: 
            none.
Algorithm: 
            1) Check if row or column are out of bounds.
            2) Retun true if the given row/column coordinate matches the a_color provided.
            3) Else return false.
Assistance Received: none 
********************************************************************* */
bool
board::isValidPieceToMove(char a_color, int a_row, int a_column)
{
    // Row or column is out of bounds.
    if(a_row - 1 < 0 || a_column - 1 < 0 || a_row - 1 >= m_boardSize || a_column - 1 >= m_boardSize) 
    {
        return false;
    }
    else
    {
        // Row/Column in board matches the color provided.
        return ((*boardTable)[a_row-1][a_column-1] == a_color || (*boardTable)[a_row-1][a_column-1] == tolower(a_color,std::locale()) ) ? true : false;
    }
}

/* ********************************************************************* 
Function Name: isValidLocationToMove 
Purpose: Checks if a given row/column coordinate is a valid location to move to.
Parameters: 
            a_row, integer for the row coordinate.
            a_column, integer for the column coordinate.
            isSuperPiece, boolean value that is true if piece is a super piece (can capture).
Return Value: Boolean value if the location is valid to move to.
Local Variables: 
            none.
Algorithm: 
            1) Check if row or column are out of bounds.
            2) Return true if the piece is a super piece.
            3) Check if the location is neither white or black.
Assistance Received: none 
********************************************************************* */
bool
board::isValidLocationToMove(int a_row, int a_column,bool isSuperPiece)
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
            // Check if the location is open '+' .
            return ((*boardTable)[a_row-1][a_column-1] != 'W' && (*boardTable)[a_row-1][a_column-1] != 'B') ? true : false;
        }
    }
}

// what is this?
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

/* ********************************************************************* 
Function Name: updateBoard 
Purpose: Updates the board given a pair of old coordinates and new coordinates.
    Changes the new coordinate to the provided piece and changes the old coordinate to open.
Parameters: 
            a_initialRow, integer for old row coordinate.
            a_initialColumn, integer for old column coordinate.
            a_finalRow, integer for new row coordinate.
            a_finalRow, integer for new column coordinate.
            a_color, char is the color piece
Return Value: none.
Local Variables: 
            none.
Algorithm: 
            1) Check if the piece provided is ready to become a super piece. If so, change piece to lowercase.
            2) Update the new coordinate with the piece.
            3) Update old coordinate with open space.
Assistance Received: none 
********************************************************************* */
void
board::updateBoard(int a_initialRow, int a_initialColumn, int a_finalRow, int a_finalColumn, char a_color)
{
    // Checks if the piece can become a super piece.
    if(isReadyToUpgrade(a_finalRow,a_color))
    {
        // Make piece lowercase.
        (*boardTable)[a_finalRow-1][a_finalColumn-1] = tolower(a_color,std::locale());
    }

    else
    {
        // Move super piece to new location.
        if((*boardTable)[a_initialRow-1][a_initialColumn-1] == tolower(a_color,std::locale()))
        {
            (*boardTable)[a_finalRow-1][a_finalColumn-1] = tolower(a_color,std::locale());    
        }
        // Move regular piece to new locatoin.
        else
        {   
            (*boardTable)[a_finalRow-1][a_finalColumn-1] = a_color;
        }
    }

    // Make old location open.
    (*boardTable)[a_initialRow-1][a_initialColumn-1] = '+';  
};

/* ********************************************************************* 
Function Name: isReadyToUpgrade 
Purpose: Checks if a piece is ready to be upgraded to a super piece.
Parameters: 
            a_row, integer for row coordinate.
            a_color, char. Color of the piece
Return Value: Boolean value marking that its ready to upgrade the piece.
Local Variables: 
            none.
Algorithm: 
            1) Check if the piece provided is ready to become a super piece. If so, change piece to lowercase.
            2) Update the new coordinate with the piece.
            3) Update old coordinate with open space.
Assistance Received: none 
********************************************************************* */
bool
board::isReadyToUpgrade(int a_row,char a_color)
{
    // If the piece color is white and is located at the black-side of the board. Then it is ready to become super piece.
    if( (a_color == 'W' || a_color == 'w' ) && (a_row-1) == (m_boardSize -1) )
    {
        return true;
    }
    // If the piece color is black and is located at the white-side of the board. Then it is ready to become super piece.
    else if ( (a_color == 'B' || a_color == 'b' ) && (a_row-1) == 0 )
    {
        return true;
    }
    // Piece is not ready.
    else
    {
        return false;
    }
}

/* ********************************************************************* 
Function Name: getPieceAtLocation 
Purpose: Given a row and column, return the color of the piece at the coordinate.
Parameters: 
            a_row, integer for row coordinate.
            a_column, integer for column coordinate.
Return Value: Char value that is either 'W' for white piece or 'B' for black piece.
Local Variables: 
            none.
Algorithm: 
            1) Check if the coordinates provided are within the bounds of the board.
            2) If so, then return the piece located at the coordinate.
Assistance Received: none 
********************************************************************* */
char
board::getPieceAtLocation(int a_row, int a_column) const
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

/* ********************************************************************* 
Function Name: getBlackSide 
Purpose: Get a vector of pieces located on the home points of the black side.
Parameters: 
            none.
Return Value: Vector of pieces on the black-side.
Local Variables: 
            blackSide, vector that contains the pieces.
Algorithm: 
            1) Iterate through the black-side spaces and assign the peices to the local vector.
            2) Return the vector.
Assistance Received: none 
********************************************************************* */
std::vector <char> 
board::getBlackSide() const
{
    std::vector <char> blackSide (m_boardSize+2,'+');

    // Iterate through black side of the board.
    int i = 0;
    for(; i < m_boardSize; i++)
    {
        blackSide[i] = (*boardTable)[m_boardSize-1][i];
    }

    blackSide[i] = (*boardTable)[m_boardSize-2][0];
    i++;
    blackSide[i] = (*boardTable)[m_boardSize-2][m_boardSize-1];

    return blackSide;

};

/* ********************************************************************* 
Function Name: getWhiteSide 
Purpose: Get a vector of pieces located on the home points of the white side.
Parameters: 
            none.
Return Value: Vector of pieces on the white-side.
Local Variables: 
            whiteSide, vector that contains the pieces.
Algorithm: 
            1) Iterate through the white-side spaces and assign the peices to the local vector.
            2) Return the vector.
Assistance Received: none 
********************************************************************* */
std::vector <char> 
board::getWhiteSide() const
{
    std::vector <char> whiteSide (m_boardSize+2,'+');

    // Iterate through white side of the board.
    int i = 0;
    for(; i < m_boardSize; i++)
    {
        whiteSide[i] = (*boardTable)[0][i];
    }

    whiteSide[i] = (*boardTable)[1][0];
    i++;
    whiteSide[i] = (*boardTable)[1][m_boardSize-1];

    return whiteSide;

};

/* ********************************************************************* 
Function Name: getNumberOfBlackPieces 
Purpose: Get the number of remaining black pieces on the board.
Parameters: 
            none.
Return Value: Integer for # of black pieces.
Local Variables: 
            numberOfBlack, integer. Number of black pieces.
Algorithm: 
            1) Iterate through the board and count how many black pieces remain.
Assistance Received: none 
********************************************************************* */
int
board::getNumberOfBlackPieces() const
{
    int numberOfBlack=0;

    for(int i = 0; i < m_boardSize; i++)
    {
        for(int j = 0; j < m_boardSize; j++)
        {
            if((*boardTable)[i][j] == 'B' || (*boardTable)[i][j] == 'b')
            {
                numberOfBlack++;
            }
        }
    }

    return numberOfBlack;
};

/* ********************************************************************* 
Function Name: getNumberOfWhitePieces 
Purpose: Get the number of remaining white pieces on the board.
Parameters: 
            none.
Return Value: Integer for # of white pieces.
Local Variables: 
            numberOfWhite, integer. Number of white pieces.
Algorithm: 
            1) Iterate through the board and count how many white pieces remain.
Assistance Received: none 
********************************************************************* */   
int
board::getNumberOfWhitePieces() const
{
    int numberOfWhite=0;

    for(int i = 0; i < m_boardSize; i++)
    {
        for(int j = 0; j < m_boardSize; j++)
        {
            if((*boardTable)[i][j] == 'W' || (*boardTable)[i][j] == 'w')
            {
                numberOfWhite++;
            }
        }
    }

    return numberOfWhite;
};