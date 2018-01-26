#include "stdafx.h"
#include "human.h"

human::human(char a_color)
{
    m_color = a_color;
    std::cout << "in human class " << m_color << std::endl;
}

void human::play(board &gameBoard)
{
    std::cout << "in human class - play()" << std::endl;

    std::cout << "In player class - play()" << std::endl;

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

        std::cout << "Where do you want to move this piece to?" << std::endl;
        std::cout << "Enter row: ";
        std::cin >> finalRow;
        std::cout << "Enter column: ";
        std::cin >> finalColumn;
        if(gameBoard.isValidLocationToMove(finalRow,finalColumn))
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