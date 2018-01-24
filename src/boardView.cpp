#include "board.h"
#include "boardView.h"
#include "stdafx.h"

boardView::boardView(){};

void boardView::showBoard(std::vector< std::vector <int> > & boardTable) 
{
    int boardSize = boardTable.size();

    // Print North compass.
    std::cout << "N" << std::endl;

    for( int row = 0; row < boardSize; row++ )
    {
        // Print row numbers.
        std::cout << row + 1 << "  ";

        for( int col = 0; col < boardSize; col++ )
        {
            if(col != 0)
                std::cout << " - ";
            std::cout << boardTable[row][col];
        }

        std::cout << std::endl;
        
        
        if( row != (boardSize - 1))
        {
            std::cout << "   ";
            for( int col = 0; col < boardSize; col++ )
            {
                std::cout << "|   ";
            }
        }
        else
        {
            std::cout << "S";
        }

        std::cout << std::endl;
    }

    std::cout << "W  ";

    for( int col = 1; col <= boardSize; col++ )
    {
        std::cout << col << "   ";
    }

    std::cout << "E" << std::endl;

}