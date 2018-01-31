#include "stdafx.h"
#include "player.h"
#include "board.h"

player::player()
{
};

void player::strategyHelp(char a_color,board &gameBoard)
{
    m_color = a_color;
    updateStateForStrategy(gameBoard);

    availablePiecesIter availablePieces = (*m_availablePieces).begin();

    
    // If home side is top.
    if(m_color == 'W')
    {
        //IF - opponent's piece is close to home, check if that piece is blocked.
        if(m_closestOpponent.first <= std::sqrt(m_boardSize))
        {
            //IF - if the opponent's piece is already blocked, continue to play offensively.
            if( boardTable[m_closestOpponent.first-1][m_closestOpponent.second-1] == m_color && boardTable[m_closestOpponent.first-1][m_closestOpponent.second+1] == m_color)
            {   
                std::cout << "Piece is already blocked. " << boardTable[m_closestOpponent.first-1][m_closestOpponent.second-1] << boardTable[m_closestOpponent.first-1][m_closestOpponent.second+1] << " \n";
                checkOffensiveStrategy(gameBoard);      
            }                
            //ELSE - Check available pieces that can block opponent.
            else
            {
                //if(boardTable[m_closestOpponent.first-2][m_closestOpponent.second] == m_color)
                std::cout << "Moving to block piece at " << "(" << m_closestOpponent.first + 1<< "," << m_closestOpponent.second + 1 << "). \n";

                std::cout<<"moving piece to block it"<<std::endl;
                
                // Check if west side is blocked, if so, then prepare to block from east.
                if( boardTable[m_closestOpponent.first-1][m_closestOpponent.second-1] == m_color)
                {
                    std::cout << "left side is blocked.\n";
                    checkDefensiveEastStrategy(gameBoard);
                }

                // Check if right side is blocked, if so, then prepare to block from west.
                else if (boardTable[m_closestOpponent.first-1][m_closestOpponent.second+1] == m_color)
                {       
                    std::cout << "right side is blocked. Moving to block left side. \n";
                    checkDefensiveWestStrategy(gameBoard);
                }

                else
                {
                    std::cout << "neitherside is blocked.\n";
                    if(!checkDefensiveWestStrategy(gameBoard))
                        std::cout << "";
                    else if (!checkDefensiveEastStrategy(gameBoard))
                        std::cout << "";
                    else checkOffensiveStrategy(gameBoard);
                }

            }
        }
        else
        //ELSE - randomly move piece to opponent's end.
        {
            checkOffensiveStrategy(gameBoard);   
        }
    }
    
    delete m_availablePieces;
}

void player::updateStateForStrategy(board &gameBoard)
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
}

void player::play(std::vector< std::vector <char> > &boardTable)
{
    std::cout << "In player class - play()" << std::endl;

    unsigned short pieceToMove = 0;
    std::cout << "What piece do you want to move?" << std::endl;
    std::cin >> pieceToMove;

    unsigned short locationToMove = 0;
    std::cout << "Where do you want to move this piece to?" << std::endl;
    std::cin >> locationToMove;


    //when playing, must ask for piece to move. 
    //check if piece is valid to move
    //make move
    //check if move is valid
};

std::pair<int,int> player::pickOffensivePiece()
{
    return (*m_availablePieces)[rand() % (m_availablePieces->size()-1)];
}

void player::checkOffensiveStrategy(board &gameBoard)
{
    if(m_color == 'W')
    {
        std::cout << "Moving piece to play offensively.\n";

        // Picking random piece.
        bool didMove = true;
        while(didMove)
        {
        std::pair<int,int> pieceToMove = pickOffensivePiece();

        std::cout << "Moving piece (" << pieceToMove.first + 1 << "," << pieceToMove.second + 1<< ").\n";

        if(gameBoard.isValidPieceToMove(m_color,pieceToMove.first+1,pieceToMove.second+1))
        {
            std::cout << "Valid piece to move.\n";

            if(gameBoard.isValidLocationToMove(pieceToMove.first+2,pieceToMove.second+2))
            {
                std::cout << "Moving SE\n";
                didMove = false;
            }
            else if(gameBoard.isValidLocationToMove(pieceToMove.first+2,pieceToMove.second-2))
            {
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

bool player::checkDefensiveWestStrategy(board &gameBoard)
{
    std::cout << "blocking from west \n";
    // If a there is an available piece located NW, move to block the oppponent piece.
    if(boardTable[m_closestOpponent.first-2][m_closestOpponent.second-2] == m_color)
    {
        std::cout << "The computer moved the piece at (" << m_closestOpponent.first-1 <<","<<m_closestOpponent.second-1 << ") southeast." << std::endl;
        std::cout << "It wanted to block the human piece at ("<< m_closestOpponent.first+1 <<","<<m_closestOpponent.second+1 <<")." << std::endl;
        return true;
    }
    // If a there is an available piece located SW, move to block the oppponent piece.
    else if(boardTable[m_closestOpponent.first][m_closestOpponent.second-2] == m_color)
    {
        std::cout << "The computer moved the piece at (" << m_closestOpponent.first <<","<<m_closestOpponent.second-1 << ") northeast." << std::endl;
        std::cout << "It wanted to block the human piece at ("<< m_closestOpponent.first+1 <<","<<m_closestOpponent.second+1 <<")." << std::endl;

        return true;
    }
    // If a there is an available piece located N, move to block the oppponent piece.
    else if(boardTable[m_closestOpponent.first-2][m_closestOpponent.second] == m_color)
    {
        std::cout << "The computer moved the piece at (" << m_closestOpponent.first -1 <<","<<m_closestOpponent.second << ") southwest." << std::endl;
        std::cout << "It wanted to block the human piece at ("<< m_closestOpponent.first+1 <<","<<m_closestOpponent.second+1 <<")." << std::endl;

        return true;
    }
    // Else report back that it could not be blocked from the west side.
    else 
    {
        return false;
    }
}

bool player::checkDefensiveEastStrategy(board &gameBoard)
{
    std::cout << "blocking from east \n";
    // If a there is an available piece located NE, move to block the oppponent piece.
    if(boardTable[m_closestOpponent.first-2][m_closestOpponent.second+2] == m_color)
    {
        std::cout << "The computer moved the piece at (" << m_closestOpponent.first-1 <<","<<m_closestOpponent.second+1 << ") southwest." << std::endl;
        std::cout << "It wanted to block the human piece at ("<< m_closestOpponent.first+1 <<","<<m_closestOpponent.second+1 <<")." << std::endl;

        gameBoard.updateBoard(m_closestOpponent.first-1, m_closestOpponent.first+1, m_closestOpponent.first,m_closestOpponent.second, m_color); 
        return true;
    }
    // If a there is an available piece located SE, move to block the oppponent piece.
    else if(boardTable[m_closestOpponent.first][m_closestOpponent.second+2] == m_color)
    {
        std::cout << "The computer moved the piece at (" << m_closestOpponent.first <<","<<m_closestOpponent.second+1 << ") northwest." << std::endl;
        std::cout << "It wanted to block the human piece at ("<< m_closestOpponent.first+1 <<","<<m_closestOpponent.second+1 <<")." << std::endl;

        gameBoard.updateBoard(m_closestOpponent.first, m_closestOpponent.first+1, m_closestOpponent.first,m_closestOpponent.second, m_color); 
        return true;
    }
    // If a there is an available piece located N, move to block the oppponent piece.
    else if(boardTable[m_closestOpponent.first-2][m_closestOpponent.second] == m_color)
    {
        std::cout << "The computer moved the piece at (" << m_closestOpponent.first -1 <<","<<m_closestOpponent.second << ") southeast." << std::endl;
        std::cout << "It wanted to block the human piece at ("<< m_closestOpponent.first+1 <<","<<m_closestOpponent.second+1 <<")." << std::endl;

        gameBoard.updateBoard(m_closestOpponent.first-1, m_closestOpponent.first, m_closestOpponent.first,m_closestOpponent.second, m_color); 
        return true;
    }
    // Else report back that it could not be blocked from the west side.
    else 
    {
        return false;
    }
};