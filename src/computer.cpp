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

std::pair<int,int> computer::pickRandomPiece()
{
    return (*m_availablePieces)[rand() % (m_availablePieces->size()-1)];
}

void computer::playOffensively(board &gameBoard)
{
    if(m_color == 'W')
    {
        std::cout << "Moving piece to play offensively.\n";

        // Picking random piece.
        bool didMove = true;
        while(didMove)
        {
        std::pair<int,int> pieceToMove = pickRandomPiece();

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

    }

}

void computer::play(board &gameBoard)
{
    updateState(gameBoard);

    availablePiecesIter availablePieces = (*m_availablePieces).begin();
    
    // If home side is top.
    if(m_color == 'W')
    {
        //IF - opponent's piece is close to home, check if that piece is blocked.
        if(m_closestOpponent.first <= std::sqrt(m_boardSize))
        {
            std::cout << "Moving to block piece at " << "(" << m_closestOpponent.first + 1<< "," << m_closestOpponent.second + 1 << "). \n";
            //IF - if the opponent's piece is block, play offensively.
            if( boardTable[m_closestOpponent.first-1][m_closestOpponent.second-1] == m_color && boardTable[m_closestOpponent.first-1][m_closestOpponent.second+1] == m_color)
            {   
                std::cout << "Piece is already blocked. " << boardTable[m_closestOpponent.first-1][m_closestOpponent.second-1] << boardTable[m_closestOpponent.first-1][m_closestOpponent.second+1] << " \n";
                   
            }
            //ELSE - Randomy move a nearby piece to block it.
            else
            {
                std::cout<<"moving piece to block it"<<std::endl;
                // check if leftside is blocked
                if( boardTable[m_closestOpponent.first-1][m_closestOpponent.second-1] == m_color)
                {
                    std::cout << "left side is blocked.\n";
                }
                // check if rightside is blocked
                else if (boardTable[m_closestOpponent.first-1][m_closestOpponent.second+1] == m_color)
                {       
                    std::cout << "right side is blocked. Moving to block left side. \n";                    
                }
                else
                {
                    std::cout << "neitherside is blocked.\n";
                    //if( find( (*m_availablePieces).begin(),(*m_availablePieces).end(), ))
                }
                // Check if leftside has piece that can be moved up.
                // Check if rightside has piece that can be moved up.
                // Search for nearby piece. 
            }
        }
        else
        //ELSE - randomly move piece to opponent's end.
        {
            playOffensively(gameBoard);   
        }
    }
    
    delete m_availablePieces;
    
};

// Allows computer to recognize friendly and opponent pieces.
void computer::updateState(board &gameBoard)
{
    boardTable = gameBoard.getBoard();
    m_boardSize = gameBoard.getBoardSize();

    iter friendlySide;
    iter opponentSide;

    // vector of availble friendly pieces
    m_availablePieces = new std::vector< std::pair<int,int> >;
    

    // Load vector of available computer pieces.
    for( int row = 0; row < m_boardSize; row++ )
    {
        for( int col = 0; col < m_boardSize; col++ )
        {
            if(boardTable[row][col]==m_color)
            {
                std::cout << "row: " << row + 1 << ", col: " << col + 1 << std::endl;
                m_availablePieces -> push_back( std::make_pair(row,col) );
            }
        }
    }

    if( m_color == 'W')
    {
        // If friendly side is on the top (W), opponnent side is on bottom (B)
        friendlySide = boardTable.begin();
        opponentSide = boardTable.end()-1;
        
        // Iterate from top to bottom to find closest opponent
        for ( ; friendlySide != opponentSide ; ++friendlySide )
        {
            colIter col = std::find(friendlySide->begin(), friendlySide->end(), m_opponentColor);
            if ( col != friendlySide->end() )
            {
                std::cout << "Closest Opponent: row "   << distance(boardTable.begin(),friendlySide)+1 << ", col " << distance(friendlySide->begin(),col)+1 << '\n';
                m_closestOpponent = std::make_pair(distance(boardTable.begin(),friendlySide),distance(friendlySide->begin(),col));
                break;
            }
        }

        friendlySide = boardTable.begin();

        // Iterate from bottom to top to find furthest friendly piece.
        for ( ; opponentSide >= friendlySide ; --opponentSide )
        {
            colIter col = std::find(opponentSide->begin(), opponentSide->end(), m_color);
            if ( col != opponentSide->end() )
            {
                std::cout << "Furthest Friendly: row "   << distance(boardTable.begin(),opponentSide)+1 << ", col " << distance(opponentSide->begin(),col)+1 << '\n';
                m_furthestFriendly = std::make_pair(distance(boardTable.begin(),opponentSide), distance(opponentSide->begin(),col));
                break;
            }
        }
    }
    else
    {
        // If friendly side is on the bottom (B), opponnent side is on top (W)
        friendlySide = boardTable.end()-1;
        opponentSide = boardTable.begin();

        // Iterate from the bottom to the top to find the closest opponent piece.
        for ( ; friendlySide >= opponentSide ; --friendlySide )
        {
            colIter col = std::find(friendlySide->begin(), friendlySide->end(), m_opponentColor);
            if ( col != friendlySide->end() )
            {
                std::cout << "Closest Opponent: row "   << distance(boardTable.begin(),friendlySide)+1 << ", col " << distance(friendlySide->begin(),col)+1 << '\n';
                m_closestOpponent = std::make_pair(distance(boardTable.begin(),friendlySide), distance(friendlySide->begin(),col));
                break;
            }
        }

        friendlySide = boardTable.end()-1;

        // Iterate from the the top to the bottom to find the furthest friendly piece.
        for ( ; opponentSide != friendlySide ; ++opponentSide )
        {
            colIter col = std::find(opponentSide->begin(), opponentSide->end(), m_color);
            if ( col != opponentSide->end() )
            {
                std::cout << "Furthest Friendly: row "   << distance(boardTable.begin(),opponentSide)+1 << ", col " << distance(opponentSide->begin(),col)+1 << '\n';
                m_furthestFriendly = std::make_pair(distance(boardTable.begin(),opponentSide), distance(opponentSide->begin(),col));
                break;
            }
        }
    }

};