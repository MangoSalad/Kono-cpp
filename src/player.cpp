#include "stdafx.h"
#include "player.h"
#include "board.h"

player::player()
{
};

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

std::pair<int,int> player::pickRandomPiece()
{
    return (*m_availablePieces)[rand() % (m_availablePieces->size()-1)];
}

void player::showOffensiveDecision(int a_initalRow, int a_initialColumn, int a_finalRow, int a_finalColumn)
{
    std::cout << "It is suggested to move the piece at (" << a_initalRow << "," << a_initialColumn << ")." << std::endl;
    std::cout << "You should advance the piece to (" << a_finalColumn << "," << a_finalColumn << ")." << std::endl;
}

void player::showDefensiveDecision(int a_initalRow, int a_initialColumn, int a_finalRow, int a_finalColumn)
{
    std::cout << "It is suggested to move the piece at (" << a_initalRow << "," << a_initialColumn << ")." << std::endl;
    std::cout << "You should block the computer piece at (" << a_finalRow << "," << a_finalColumn <<")." << std::endl;
}

void player::playOffensively(board &gameBoard)
{
    if(m_color == 'W')
    {
        // Picking random piece.
        bool didMove = true;
        while(didMove)
        {
        std::pair<int,int> pieceToMove = pickRandomPiece();

        if(gameBoard.isValidPieceToMove(m_color,pieceToMove.first+1,pieceToMove.second+1))
        {
            if(gameBoard.isValidLocationToMove(pieceToMove.first+2,pieceToMove.second+2))
            {
                showOffensiveDecision(pieceToMove.first + 1, pieceToMove.second + 1, pieceToMove.first + 2, pieceToMove.second + 2);
                didMove = false;
            }
            else if(gameBoard.isValidLocationToMove(pieceToMove.first+2,pieceToMove.second))
            {
                showOffensiveDecision(pieceToMove.first + 1, pieceToMove.second + 1, pieceToMove.first + 2, pieceToMove.second);
                didMove = false;
            }
            else
            {
                std::cout << "Invalid location to move to.\n";
            }
        }
        }   
    }
    // computer is black
    else
    {
        // Picking random piece.
        bool didMove = true;
        while(didMove)
        {
        std::pair<int,int> pieceToMove = pickRandomPiece();

        if(gameBoard.isValidPieceToMove(m_color,pieceToMove.first+1,pieceToMove.second+1))
        {
            if(gameBoard.isValidLocationToMove(pieceToMove.first,pieceToMove.second+2))
            {
                showOffensiveDecision(pieceToMove.first + 1,  pieceToMove.second + 1, pieceToMove.first, pieceToMove.second + 2);
                didMove = false;
            }
            else if(gameBoard.isValidLocationToMove(pieceToMove.first,pieceToMove.second))
            {
                showOffensiveDecision(pieceToMove.first + 1,pieceToMove.second + 1, pieceToMove.first, pieceToMove.second);
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

bool player::blockFromWest(board &gameBoard)
{
    std::cout << "blocking from west \n";
    std::cout << "opponent: "<<m_closestOpponent.first <<" " << m_closestOpponent.second << "\n"; 
    std::cout << m_color << std::endl;

    // Computer color is white.
    if(m_color == 'W')
    {
        // If a there is an available piece located NW, move to block the oppponent piece.
        if(gameBoard.isValidPieceToMove(m_color,m_closestOpponent.first-1,m_closestOpponent.second-1) && gameBoard.isValidLocationToMove(m_closestOpponent.first,m_closestOpponent.second))
        //    boardTable[m_closestOpponent.first-2][m_closestOpponent.second-2] == m_color)
        {
            showDefensiveDecision(m_closestOpponent.first-1, m_closestOpponent.second-1, m_closestOpponent.first+1, m_closestOpponent.second+1);
            return true;
        }

        // MAYBE first -1 ???
        // If a there is an available piece located SW, move to block the oppponent piece.
        else if(gameBoard.isValidPieceToMove(m_color,m_closestOpponent.first,m_closestOpponent.second-1) && gameBoard.isValidLocationToMove(m_closestOpponent.first,m_closestOpponent.second))
        //boardTable[m_closestOpponent.first][m_closestOpponent.second-2] == m_color
        {
            showDefensiveDecision(m_closestOpponent.first, m_closestOpponent.second-1, m_closestOpponent.first+1, m_closestOpponent.second+1);
            return true;
        }
        // If a there is an available piece located N, move to block the oppponent piece.
        else if(gameBoard.isValidPieceToMove(m_color,m_closestOpponent.first-1,m_closestOpponent.second) && gameBoard.isValidLocationToMove(m_closestOpponent.first,m_closestOpponent.second))
        //boardTable[m_closestOpponent.first-2][m_closestOpponent.second] == m_color
        {
            showDefensiveDecision(m_closestOpponent.first -1,m_closestOpponent.second, m_closestOpponent.first+1, m_closestOpponent.second+1);
            return true;
        }
        // Else report back that it could not be blocked from the west side.
        else 
        {
            return false;
        }
    }

    // Computer color is black.
    else
    {
        // Check if there is an available piece from the West.
        
        if(gameBoard.isValidPieceToMove(m_color,m_closestOpponent.first+1,m_closestOpponent.second-1) && gameBoard.isValidLocationToMove(m_closestOpponent.first+2,m_closestOpponent.second))
        //    boardTable[m_closestOpponent.first-2][m_closestOpponent.second-2] == m_color)
        {
            showDefensiveDecision(m_closestOpponent.first+1,m_closestOpponent.second-1, m_closestOpponent.first+1, m_closestOpponent.second+1);
            return true;
        }

        // MAYBE first -1 ???
        // Check if there is an available piece from the Southwest.
        else if(gameBoard.isValidPieceToMove(m_color,m_closestOpponent.first+3,m_closestOpponent.second-1) && gameBoard.isValidLocationToMove(m_closestOpponent.first+2,m_closestOpponent.second))
        //boardTable[m_closestOpponent.first][m_closestOpponent.second-2] == m_color
        {
            showDefensiveDecision(m_closestOpponent.first+3,m_closestOpponent.second-1,m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }

        // Check if there is an available piece from the South.
        else if(gameBoard.isValidPieceToMove(m_color,m_closestOpponent.first+3,m_closestOpponent.second+1) && gameBoard.isValidLocationToMove(m_closestOpponent.first+2,m_closestOpponent.second))
        //boardTable[m_closestOpponent.first-2][m_closestOpponent.second] == m_color
        {
            showDefensiveDecision(m_closestOpponent.first+3,m_closestOpponent.second+1,m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }
        // Else report back that it could not be blocked from the west side.
        else 
        {
            return false;
        }

    }
    
}

bool player::blockFromEast(board &gameBoard)
{
    std::cout << "blocking from east \n";
    std::cout << "opponent: "<<m_closestOpponent.first <<" " << m_closestOpponent.second << "\n";
    
    if(m_color == 'W')
    {
        // If a there is an available piece located NE, move to block the oppponent piece.
        std::cout << 1 << std::endl;
        if(gameBoard.isValidPieceToMove(m_color,m_closestOpponent.first-1,m_closestOpponent.second+3) && gameBoard.isValidLocationToMove(m_closestOpponent.first,m_closestOpponent.second+2))
        //boardTable[m_closestOpponent.first-2][m_closestOpponent.second+2] == m_color
        {
            showDefensiveDecision(m_closestOpponent.first-1,m_closestOpponent.second+3,m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }
        std::cout << 2 << std::endl;
        // If a there is an available piece located E, move to block the oppponent piece.
        if(gameBoard.isValidPieceToMove(m_color,m_closestOpponent.first+1,m_closestOpponent.second+3) && gameBoard.isValidLocationToMove(m_closestOpponent.first,m_closestOpponent.second+2))
        {
            showDefensiveDecision(m_closestOpponent.first +1, m_closestOpponent.second+3, m_closestOpponent.first+1, m_closestOpponent.second+1);
            return true;
        }
        // If a there is an available piece located N, move to block the oppponent piece.
        std::cout << 3 << std::endl;

        if(gameBoard.isValidPieceToMove(m_color,m_closestOpponent.first-1,m_closestOpponent.second+1) && gameBoard.isValidLocationToMove(m_closestOpponent.first,m_closestOpponent.second+2))
        //boardTable[m_closestOpponent.first-2][m_closestOpponent.second] == m_color
        {
            showDefensiveDecision(m_closestOpponent.first -1, m_closestOpponent.second, m_closestOpponent.first+1, m_closestOpponent.second+1);
            return true;
        }

        std::cout << 4 << std::endl;
        // Else report back that it could not be blocked from the west side.
        return false;
    }
    //computer color is black
    else
    {
        // Check if there is an available piece from the East.
        if(gameBoard.isValidPieceToMove(m_color,m_closestOpponent.first+1,m_closestOpponent.second+3) && gameBoard.isValidLocationToMove(m_closestOpponent.first+2,m_closestOpponent.second+2))
        //boardTable[m_closestOpponent.first-2][m_closestOpponent.second+2] == m_color
        {
            showDefensiveDecision(m_closestOpponent.first+1,m_closestOpponent.second+3,m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }
        std::cout << 2 << std::endl;
        
        // Check if there is an available piece from the Southeast.
        if(gameBoard.isValidPieceToMove(m_color,m_closestOpponent.first+3,m_closestOpponent.second+3) && gameBoard.isValidLocationToMove(m_closestOpponent.first+2,m_closestOpponent.second+2))
        {
            showDefensiveDecision(m_closestOpponent.first +3,m_closestOpponent.second+3,m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }
        
        std::cout << 3 << std::endl;

        // Check if there is an available piece from the South.
        if(gameBoard.isValidPieceToMove(m_color,m_closestOpponent.first+3,m_closestOpponent.second+1) && gameBoard.isValidLocationToMove(m_closestOpponent.first+2,m_closestOpponent.second+2))
        //boardTable[m_closestOpponent.first-2][m_closestOpponent.second] == m_color
        {
            showDefensiveDecision(m_closestOpponent.first +3, m_closestOpponent.second +1, m_closestOpponent.first+1, m_closestOpponent.second+1);
            return true;
        }

        std::cout << 4 << std::endl;
        // Else report back that it could not be blocked from the west side.
        return false;   
    }
    
    
};

void player::help(board &gameBoard,char a_color,char a_opponentColor)
{
    m_color = a_color;
    m_opponentColor = a_opponentColor;
    updateState(gameBoard);

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
                playOffensively(gameBoard);      
            }                
            //ELSE - Check available pieces that can block opponent.
            else
            {
                //if(boardTable[m_closestOpponent.first-2][m_closestOpponent.second] == m_color)
                std::cout << "Moving to block piece at " << "(" << m_closestOpponent.first + 1<< "," << m_closestOpponent.second + 1 << "). \n";

                std::cout<<"moving piece to block it"<<std::endl;
                
                // Check if west side is blocked, if so, then prepare to block from east.
                if(!blockFromEast(gameBoard))
                {
                    if(!blockFromWest(gameBoard))
                    {
                        playOffensively(gameBoard);
                    }
                }

            }
        }
        else
        //ELSE - randomly move piece to opponent's end.
        {
            playOffensively(gameBoard);   
        }
    }

    // Computer is black
    else
    {
        if(m_closestOpponent.first+1 >= std::sqrt(m_boardSize))
        {
            //IF - if the opponent's piece is already blocked, continue to play offensively.
            if( gameBoard.isValidOpenLocation(m_closestOpponent.first+2,m_closestOpponent.second) && gameBoard.isValidOpenLocation(m_closestOpponent.first+2,m_closestOpponent.second+2))
            {   
                std::cout << "Piece is already blocked. " << boardTable[m_closestOpponent.first+2][m_closestOpponent.second] << boardTable[m_closestOpponent.first+2][m_closestOpponent.second+2] << " \n";
                playOffensively(gameBoard);      
            }                
            //ELSE - Check available pieces that can block opponent.
            else
            {
                //if(boardTable[m_closestOpponent.first-2][m_closestOpponent.second] == m_color)
                std::cout << "Moving to block piece at " << "(" << m_closestOpponent.first + 1<< "," << m_closestOpponent.second + 1 << "). \n";

                std::cout<<"moving piece to block it"<<std::endl;

                bool didBlock = false;
                
                // Check if west side is blocked, if so, then prepare to block from east.
                if(gameBoard.isValidOpenLocation(m_closestOpponent.first+2,m_closestOpponent.second))
                {
                    didBlock = blockFromEast(gameBoard);
                }
                if(gameBoard.isValidOpenLocation(m_closestOpponent.first+2,m_closestOpponent.second+2))
                {
                    didBlock = blockFromWest(gameBoard);
                }
                if(!didBlock)
                {
                    playOffensively(gameBoard);
                }
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
void player::updateState(board &gameBoard)
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
            if(boardTable[row][col]==m_color || boardTable[row][col]==tolower(m_color,std::locale()) )
            {
                m_availablePieces -> push_back( std::make_pair(row,col) );
            }
        }
    }

    std::cout << "loaded available pieces \n";

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