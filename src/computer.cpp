#include "stdafx.h"
#include "computer.h"
#include "board.h"

computer::computer(char a_color)
{
    m_color = a_color;
    if(m_color == 'W')
    {
        m_opponentColor = 'B';
    }
    else
    {
        m_opponentColor = 'W';
    }
};

void computer::play(board &gameBoard)
{
    std::vector< std::vector <char> > board = gameBoard.getBoard();
    
    // Iterators
    // if(m_color == 'W')
    // {
    //     std::vector< std::vector <char> >::iterator closestOpponentPiece = std::find(board.begin(),board.end(),'B');
    //     std::vector< std::vector <char> >::iterator furthestFriendlyPiece = std::find(board.end(),board.begin(),'W');

    //     int distanceToClosestOpponentPiece = distance(board.begin(),closestOpponentPiece);
    //     int distanceToFurthestFriendlyPiece = distance(board.end(),furthestFriendlyPiece);

    //     std::cout<<"Closest Opponent: " <<distanceToClosestOpponentPiece <<" Furthest Friendly: " << distanceToFurthestFriendlyPiece << std::endl;
    //     //board[distanceToClosestOpponentPiece] = 'C';
    // }
    
    // If opponent piece is close to home, play defensively.
    

    // Else, play offensively and aim for center end of opponent's home. 


    // int boardSize = board.size();

    // // Print North compass.
    // std::cout << "N" << std::endl;

    // for( int row = 0; row < boardSize; row++ )
    // {
    //     // Print row numbers.
    //     std::cout << row + 1 << "  ";

    //     for( int col = 0; col < boardSize; col++ )
    //     {
    //         if(col != 0)
    //             std::cout << " - ";
    //         std::cout << board[row][col];
    //     }

    //     std::cout << std::endl;
        
        
    //     if( row != (boardSize - 1))
    //     {
    //         std::cout << "   ";
    //         for( int col = 0; col < boardSize; col++ )
    //         {
    //             std::cout << "|   ";
    //         }
    //     }
    //     else
    //     {
    //         std::cout << "S";
    //     }

    //     std::cout << std::endl;
    // }

    // std::cout << "W  ";

    // for( int col = 1; col <= boardSize; col++ )
    // {
    //     std::cout << col << "   ";
    // }

    // std::cout << "E" << std::endl;

};