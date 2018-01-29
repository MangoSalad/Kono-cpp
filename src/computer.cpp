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
    updateState(gameBoard);
    // std::vector< std::vector <char> > board = gameBoard.getBoard();
    
    // typedef std::vector< std::vector<char> >::iterator iter;
    // iter row = board.begin();
    // iter end = board.end();

    // // If opponent piece is close to base, go block.
    // // If already blocked, play offensively. 

    // // Finds closest opponent piece if opponent is black
    // for ( ; row != end ; ++row )
    // {
    //     typedef std::vector<char>::iterator col_iter;
    //     col_iter col = std::find(row->begin(), row->end(), 'B');
    //     if ( col != row->end() )
    //     {
    //         std::cout << "row "   << distance(board.begin(),row)+1 << ", col " << distance(row->begin(),col)+1 << '\n';
    //         break;
    //     }
    // }

    //Iterators
    // if(m_color == 'W')
    // {
    //     std::vector< std::vector <char> >::iterator closestOpponentPiece = find(board.begin(),board.end(),'B');
    //     std::vector< std::vector <char> >::iterator furthestFriendlyPiece = std::find(board.end(),board.begin(),'W');

    //     int distanceToClosestOpponentPiece = distance(board.begin(),closestOpponentPiece);
    //     int distanceToFurthestFriendlyPiece = distance(board.end(),furthestFriendlyPiece);

    //     std::cout<<"Closest Opponent: " <<distanceToClosestOpponentPiece <<" Furthest Friendly: " << distanceToFurthestFriendlyPiece << std::endl;
    //     //board[distanceToClosestOpponentPiece] = 'C';
    // }
    
};

void computer::updateState(board &gameBoard)
{
    std::vector< std::vector <char> > board = gameBoard.getBoard();
    m_boardSize = gameBoard.getBoardSize();
    iter friendlySide;
    iter opponentSide;
    
    // Load vector of available computer pieces.
    for( int row = 0; row < m_boardSize; row++ )
    {
        for( int col = 0; col < m_boardSize; col++ )
        {
            if(board[row][col]==m_color)
            {
                std::cout << "row: " << row + 1 << ", col: " << col + 1 << std::endl;
                m_availablePieces.push_back( std::make_pair(row,col) );
            }
        }
    }

    if( m_color == 'W')
    {
        // If friendly side is on the top (W), opponnent side is on bottom (B)
        friendlySide = board.begin();
        opponentSide = board.end();
        
        // Iterate from top to bottom to find closest opponent
        for ( ; friendlySide <= opponentSide ; ++friendlySide )
        {
            colIter col = std::find(friendlySide->begin(), friendlySide->end(), m_opponentColor);
            if ( col != friendlySide->end() )
            {
                std::cout << "Closest Opponent: row "   << distance(board.begin(),friendlySide)+1 << ", col " << distance(friendlySide->begin(),col)+1 << '\n';
                break;
            }
        }
    }
    else
    {
        // If friendly side is on the bottom (B), opponnent side is on top (W)
        friendlySide = board.end();
        opponentSide = board.begin();

        for ( ; friendlySide >= opponentSide ; --friendlySide )
        {
            colIter col = std::find(friendlySide->begin(), friendlySide->end(), m_opponentColor);
            if ( col != friendlySide->end() )
            {
                std::cout << "Closest Opponent: row "   << distance(board.begin(),friendlySide)+1 << ", col " << distance(friendlySide->begin(),col)+1 << '\n';
                break;
            }
        }
        
        friendlySide = board.end();

        for ( ; opponentSide != friendlySide ; ++opponentSide )
        {
            colIter col = std::find(opponentSide->begin(), opponentSide->end(), m_color);
            if ( col != opponentSide->end() )
            {
                std::cout << "Furthest Friendly: row "   << distance(board.begin(),opponentSide)+1 << ", col " << distance(opponentSide->begin(),col)+1 << '\n';
                break;
            }
        }

    }

    // get position of closest opponent piece

    // row = board.end() - 1;

    // for ( ; row >= board.begin() ; --row )
    // {
    //     colIter col = std::find(row->begin(), row->end(), m_color);
    //     if ( col != row->end() )
    //     {
    //         std::cout << "Furthest Friendly: row "   << distance(board.begin(),row)+1 << ", col " << distance(row->begin(),col)+1 << '\n';
    //         break;
    //     }
    // }


    // get position of furthest friendly piece
};