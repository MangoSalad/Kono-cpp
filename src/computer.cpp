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

    std::vector< std::vector <char> > board = gameBoard.getBoard();
    
    // If home side is top.
    if(m_color == 'W')
    {
        //IF - opponent's piece is close to home, check if that piece is blocked.
        std::cout << "first: " << m_closestOpponent.first << "\n";
        if(m_closestOpponent.first <= 3)
        {
            std::cout << "Moving to block\n";
            //IF - if the opponent's piece is block, play offensively.
            if( board[m_closestOpponent.first-1][m_closestOpponent.second-1] == m_color && board[m_closestOpponent.first-1][m_closestOpponent.second+1] == m_color)
            {   
                std::cout << "Piece is already blocked. " << board[m_closestOpponent.first-1][m_closestOpponent.second-1] << board[m_closestOpponent.first-1][m_closestOpponent.second+1] << " \n";
                   
            }
            //ELSE - Randomy move a nearby piece to block it.
            else
            {
                std::cout<<"moving piece to block it"<<std::endl;

            }

        }
        //ELSE - randomly move piece to opponent's end.
        { 
            std::cout << "Moving piece to play offensively.\n";

            // Picking random piece.
            bool didMove = true;
            while(didMove)
            {
            std::pair<int,int> pieceToMove = (*m_availablePieces)[rand() % (m_availablePieces->size()-1)];

            std::cout << "Moving piece (" << pieceToMove.first + 1 << "," << pieceToMove.second + 1<< ").\n";

            if(gameBoard.isValidPieceToMove(m_color,pieceToMove.first+1,pieceToMove.second+1))
            {
                std::cout << "Valid piece to move.\n";

                if(gameBoard.isValidLocationToMove(pieceToMove.first+2,pieceToMove.second+2))
                {
                    gameBoard.updateBoard(pieceToMove.first+1, pieceToMove.second+1, pieceToMove.first+2,pieceToMove.second+2, m_color);
                    std::cout << "Moving SE\n";
                    didMove = false;
                }
                else if(gameBoard.isValidLocationToMove(pieceToMove.first+2,pieceToMove.second-2))
                {
                    gameBoard.updateBoard(pieceToMove.first+1, pieceToMove.second+1, pieceToMove.first+2,pieceToMove.second-2, m_color);
                    std::cout << "Moving SW\n";
                    didMove = false;
                }
                else
                {
                    std::cout << "Invalid location to move to.\n";
                }
            }
            }            
            //gameBoard.updateBoard(pieceToMove.first-1, pieceToMove.second-1, finalRow, finalColumn, m_color);


        }
    }
    
    delete m_availablePieces;
    
};

void computer::updateState(board &gameBoard)
{
    std::vector< std::vector <char> > board = gameBoard.getBoard();
    m_boardSize = gameBoard.getBoardSize();
    iter friendlySide;
    iter opponentSide;

    m_availablePieces = new std::vector< std::pair<int,int> >;
    //clear old values
    // while(!m_availablePieces.empty())
    // {   
    //     m_availablePieces.pop_back();
    // }
    
    // Load vector of available computer pieces.
    for( int row = 0; row < m_boardSize; row++ )
    {
        for( int col = 0; col < m_boardSize; col++ )
        {
            if(board[row][col]==m_color)
            {
                std::cout << "row: " << row + 1 << ", col: " << col + 1 << std::endl;
                m_availablePieces -> push_back( std::make_pair(row,col) );
            }
        }
    }

    if( m_color == 'W')
    {
        // If friendly side is on the top (W), opponnent side is on bottom (B)
        friendlySide = board.begin();
        opponentSide = board.end()-1;
        
        // Iterate from top to bottom to find closest opponent
        for ( ; friendlySide != opponentSide ; ++friendlySide )
        {
            colIter col = std::find(friendlySide->begin(), friendlySide->end(), m_opponentColor);
            if ( col != friendlySide->end() )
            {
                std::cout << "Closest Opponent: row "   << distance(board.begin(),friendlySide)+1 << ", col " << distance(friendlySide->begin(),col)+1 << '\n';
                m_closestOpponent = std::make_pair(distance(board.begin(),friendlySide)+1,distance(friendlySide->begin(),col)+1);
                break;
            }
        }

        friendlySide = board.begin();

        // Iterate from bottom to top to find furthest friendly piece.
        for ( ; opponentSide >= friendlySide ; --opponentSide )
        {
            colIter col = std::find(opponentSide->begin(), opponentSide->end(), m_color);
            if ( col != opponentSide->end() )
            {
                std::cout << "Furthest Friendly: row "   << distance(board.begin(),opponentSide)+1 << ", col " << distance(opponentSide->begin(),col)+1 << '\n';
                m_furthestFriendly = std::make_pair(distance(board.begin(),opponentSide)+1, distance(opponentSide->begin(),col)+1);
                break;
            }
        }
    }
    else
    {
        // If friendly side is on the bottom (B), opponnent side is on top (W)
        friendlySide = board.end()-1;
        opponentSide = board.begin();

        // Iterate from the bottom to the top to find the closest opponent piece.
        for ( ; friendlySide >= opponentSide ; --friendlySide )
        {
            colIter col = std::find(friendlySide->begin(), friendlySide->end(), m_opponentColor);
            if ( col != friendlySide->end() )
            {
                std::cout << "Closest Opponent: row "   << distance(board.begin(),friendlySide)+1 << ", col " << distance(friendlySide->begin(),col)+1 << '\n';
                m_closestOpponent = std::make_pair(distance(board.begin(),friendlySide)+1, distance(friendlySide->begin(),col)+1);
                break;
            }
        }

        friendlySide = board.end()-1;

        // Iterate from the the top to the bottom to find the furthest friendly piece.
        for ( ; opponentSide != friendlySide ; ++opponentSide )
        {
            colIter col = std::find(opponentSide->begin(), opponentSide->end(), m_color);
            if ( col != opponentSide->end() )
            {
                std::cout << "Furthest Friendly: row "   << distance(board.begin(),opponentSide)+1 << ", col " << distance(opponentSide->begin(),col)+1 << '\n';
                m_furthestFriendly = std::make_pair(distance(board.begin(),opponentSide)+1, distance(opponentSide->begin(),col)+1);
                break;
            }
        }
    }

};