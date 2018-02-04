#include "board.h"
#include "boardview.h"
#include "stdafx.h"

boardView::boardView(){};

/* ********************************************************************* 
Function Name: showBoard 
Purpose: Shows the board to the user in proper format.
Parameters: 
            boardTable, vector<vector<char>> passed by reference.
Return Value: none.
Local Variables: 
            boardSize, an integer that holds the board size.
Algorithm: 
            1) Get the size of the board.s
            2) Print 'N'
            3) For each row while less than the size of the board do steps 3-7
            4) Print the row number and piece at [row][column] followed by '-'
            5) Print a new line
            6) For a '|' under each coordinate.
            7) If there are no more rows, print 'S'
            8) Print 'W'
            9) Print column numbers
            10) Print 'E'
Assistance Received: none 
********************************************************************* */
void
boardView::showBoard(std::vector< std::vector <char> > & boardTable) const
{
    // Get size of board.
    int boardSize = boardTable.size();

    // Print North compass.
    std::cout << "N" << std::endl;

    // For each row..
    for( int row = 0; row < boardSize; row++ )
    {
        // Print the row #.
        std::cout << row + 1 << "  ";

        // Print the piece at the [row][col] coordinate followed by '-'
        for( int col = 0; col < boardSize; col++ )
        {
            if(col != 0)
                std::cout << " - ";
            std::cout << boardTable[row][col];
        }

        // Print at new line.
        std::cout << std::endl;
        
        // If it is not the last row, print '|' under each coordinate.
        if( row != (boardSize - 1))
        {
            std::cout << "   ";
            for( int col = 0; col < boardSize; col++ )
            {
                std::cout << "|   ";
            }
        }

        // If it is the last row, print the South Compass.
        else
        {
            std::cout << "S";
        }

        // Print at new line.
        std::cout << std::endl;
    }

    // Print the West Compass.
    std::cout << "W  ";

    // Print the column #.
    for( int col = 1; col <= boardSize; col++ )
    {
        std::cout << col << "   ";
    }

    // Print East Compass.
    std::cout << "E" << std::endl;
};