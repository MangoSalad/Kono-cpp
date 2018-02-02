#include "stdafx.h"
#include "human.h"

human::human(char a_color)
{
    m_color = a_color;
};

void human::play(board &gameBoard)
{
    unsigned short initialRow = 0;
    unsigned short initialColumn = 0;

    std::cout << "What piece do you want to move?" << std::endl;
    std::cout << "Enter row: ";
    std::cin >> initialRow;
    std::cout << "Enter column: ";
    std::cin >> initialColumn;

    // Check if the piece to move is valid.
    if( gameBoard.isValidPieceToMove(m_color,initialRow,initialColumn) )
    {
        unsigned short finalRow = 0;
        unsigned short finalColumn = 0;
        bool isSuperPiece = false;

        std::string locationToMove;

        std::cout << "Where do you want to move this piece to? (NW/NE/SW/SE)" << std::endl;
        std::cin >> locationToMove;

        if(locationToMove == "NW")
        {
            finalRow = initialRow-1;
            finalColumn = initialColumn-1;
        }
        else if(locationToMove == "NE")
        {
            finalRow = initialRow-1;
            finalColumn = initialColumn+1;
        }
        else if(locationToMove == "SE")
        {
            finalRow = initialRow+1;
            finalColumn = initialColumn+1;
        }
        else if(locationToMove == "SW")
        {
            finalRow = initialRow+1;
            finalColumn = initialColumn-1;
        }

        // std::cout << "Enter row: ";
        // std::cin >> finalRow;
        // std::cout << "Enter column: ";
        // std::cin >> finalColumn;

        // Check if the location is valid.
        if(gameBoard.getPieceAtLocation(initialRow,initialColumn) == tolower(m_color,std::locale()))
        {
            isSuperPiece = true;
        }

        
        if(gameBoard.isValidLocationToMove(finalRow,finalColumn,isSuperPiece))
        {
            gameBoard.updateBoard(initialRow, initialColumn, finalRow, finalColumn, m_color);
        }
        else
        {
            std::cout << "Cannot move there..." << std::endl;
        }

    }
    else
    {
        std::cout << "Cannot move this piece..." << std::endl;
    }
    
};