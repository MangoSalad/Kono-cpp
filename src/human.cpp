#include "stdafx.h"
#include "human.h"

// Default constructor.
human::human(char a_color)
{
    m_color = a_color;
};

/* ********************************************************************* 
Function Name: play 
Purpose: Asks user for which pieces to move and moves the piece.
Parameters: 
            gameBoard, passed by reference. Instantiated board class.
Return Value: none.
Local Variables: 
            initialRow, an unsigned short integer that is assigned the row of the piece the user will move.
            initialColumn, an unsigned short integer that is assigned the column of the piece the user will move.
            finalRow, an unsigned short integer that is assigned the row the piece will move to.
            finalColumn, an unsigned short integer that is assigned the column the piece will move to.
            isSuperPiece, a boolean that checks if the piece is a superpiece
            locationToMove, string. Direction to move the piece.
Algorithm: 
            1) Add all the grades 
            2) Divide the sum by the number of students in class to calculate the average 
Assistance Received: none 
********************************************************************* */
void
human::play(board &gameBoard)
{
    // Row/Column of the piece that the user will move.
    unsigned short initialRow = 0;
    unsigned short initialColumn = 0;

    // Ask user what piece to move.
    while(true)
    {
        std::cout << "What piece do you want to move?" << std::endl;
        std::cout << "Enter row: ";
        std::cin >> initialRow;
        std::cout << "Enter column: ";
        std::cin >> initialColumn;

        // Check if the piece to move is valid.
        if( gameBoard.isValidPieceToMove(m_color,initialRow,initialColumn))
        {
            unsigned short finalRow = 0;
            unsigned short finalColumn = 0;
            bool isSuperPiece = false;
            std::string locationToMove;

            // Ask user the direction to move the piece.
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

            // Check if the piece is a super piece.
            if(gameBoard.getPieceAtLocation(initialRow,initialColumn) == tolower(m_color,std::locale()))
            {
                isSuperPiece = true;
            }

            // Check if the location is valid.
            if(gameBoard.isValidLocationToMove(finalRow,finalColumn,isSuperPiece))
            {
                gameBoard.updateBoard(initialRow, initialColumn, finalRow, finalColumn, m_color);
                break;
            }

            // Incorrect choice.
            else
            {
                std::cout << "Cannot move to this location." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            }
        }

        // Incorrect choice.
        else
        {
            std::cout << "Cannot move this piece." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }  
    }
};