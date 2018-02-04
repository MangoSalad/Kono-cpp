#include "stdafx.h"
#include "computer.h"
#include "board.h"

// Default constructor.
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

/* ********************************************************************* 
Function Name: pickRandomPiece 
Purpose: Returns a random piece from available pieces. Used for offensive strategy.
Parameters: 
            none.
Return Value: Pair of ints representing row/column coordinates.
Local Variables: 
            none.
Algorithm: 
            1) Use rand to return a random index of available pieces.
Assistance Received: none 
********************************************************************* */
std::pair<int,int>
computer::pickRandomPiece()
{
    return (*m_availablePieces)[rand() % (m_availablePieces->size()-1)];
}

/* ********************************************************************* 
Function Name: showDefenseDecision 
Purpose: Shows the computer's decision to play block a piece and play defensively.
Parameters: 
            a_initialRow, an integer for the row coordinate of the computer piece.
            a_initialColumn, an integer for the column coordinate of the computer piece.
            a_direction, a string. Holds the direction that the computer is moving (NE,SE,SW,NW).
            a_finalRow, an integer for the row coordinate of the human piece that the computer is trying to block.
            a_finalColumn, an integer for the column coordinate of the human piece that the computer is trying to block.
Return Value: none.
Local Variables: 
            none.
Algorithm: 
            1) Announce to player the computer's decision to move a piece at a certain direction.
            2) Announce to player what piece is is trying to block.
Assistance Received: none 
********************************************************************* */
void
computer::showDefenseDecision(int a_initialRow, int a_initialColumn,std::string a_direction, int a_finalRow, int a_finalColumn)
{
    std::cout << "The computer moved the piece at (" << a_initialRow << "," << a_initialColumn << ") " << a_direction << "." << std::endl;
    std::cout << "It wanted to block the human piece at ("<< a_finalRow <<","<<a_finalColumn <<")." << std::endl;
}

/* ********************************************************************* 
Function Name: showOffenseDecision 
Purpose: Shows the computer's decision to play offensively.
Parameters: 
            a_initialRow, an integer for the row coordinate of the computer piece.
            a_initialColumn, an integer for the column coordinate of the computer piece.
            a_direction, a string. Holds the direction that the computer is moving (NE,SE,SW,NW).
            a_finalRow, an integer for the row coordinate that the piece is moving to.
            a_finalColumn, an integer for the column coordinate that the piece is moving to.
Return Value: none.
Local Variables: 
            none.
Algorithm: 
            1) Announce to player the computer's decision to move a piece at a certain direction.
            2) Announce to player where it is moving it.
Assistance Received: none 
********************************************************************* */
void
computer::showOffenseDecision(int a_initialRow, int a_initialColumn,std::string a_direction, int a_finalRow, int a_finalColumn)
{
    std::cout << "The computer moved the piece at (" << a_initialRow << "," << a_initialColumn << ") " << a_direction << "." << std::endl;
    std::cout << "It wanted to advance its piece to (" << a_finalRow << "," << a_finalColumn << ")" << std::endl;
}

void
computer::playOffensively()
{
    if(m_color == 'W')
    {
        // Picking random piece.
        bool didMove = true;
        while(didMove)
        {
        std::pair<int,int> pieceToMove = pickRandomPiece();

        if(localBoard -> isValidPieceToMove(m_color,pieceToMove.first+1,pieceToMove.second+1))
        {
            if(localBoard -> isValidLocationToMove(pieceToMove.first+2,pieceToMove.second+2))
            {
                localBoard -> updateBoard(pieceToMove.first+1, pieceToMove.second+1, pieceToMove.first+2,pieceToMove.second+2, m_color);
                showOffenseDecision( pieceToMove.first + 1,pieceToMove.second + 1,"southeast",pieceToMove.first + 2,pieceToMove.second + 2);
                didMove = false;
            }
            else if(localBoard -> isValidLocationToMove(pieceToMove.first+2,pieceToMove.second))
            {
                localBoard -> updateBoard(pieceToMove.first+1, pieceToMove.second+1, pieceToMove.first+2,pieceToMove.second, m_color);
                showOffenseDecision(pieceToMove.first + 1,pieceToMove.second + 1,"southwest",pieceToMove.first + 2, pieceToMove.second);
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

        if(localBoard -> isValidPieceToMove(m_color,pieceToMove.first+1,pieceToMove.second+1))
        {
            if(localBoard -> isValidLocationToMove(pieceToMove.first,pieceToMove.second+2))
            {
                localBoard -> updateBoard(pieceToMove.first+1, pieceToMove.second+1, pieceToMove.first,pieceToMove.second+2, m_color);
                showOffenseDecision(pieceToMove.first + 1,pieceToMove.second + 1,"northeast",pieceToMove.first,pieceToMove.second + 2);
                didMove = false;
            }
            else if(localBoard -> isValidLocationToMove(pieceToMove.first,pieceToMove.second))
            {
                localBoard -> updateBoard(pieceToMove.first+1, pieceToMove.second+1, pieceToMove.first,pieceToMove.second, m_color);
                showOffenseDecision(pieceToMove.first + 1,pieceToMove.second + 1,"northwest",pieceToMove.first,pieceToMove.second);
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

bool computer::blockFromWest()
{
    std::cout << "blocking from west \n";
    std::cout << "opponent: "<<m_closestOpponent.first <<" " << m_closestOpponent.second << "\n"; 
    std::cout << m_color << std::endl;

    // Computer color is white.
    if(m_color == 'W')
    {
        // If a there is an available piece located NW, move to block the oppponent piece.
        if(localBoard -> isValidPieceToMove(m_color,m_closestOpponent.first-1,m_closestOpponent.second-1) && localBoard -> isValidLocationToMove(m_closestOpponent.first,m_closestOpponent.second))
        //    boardTable[m_closestOpponent.first-2][m_closestOpponent.second-2] == m_color)
        {
            localBoard -> updateBoard(m_closestOpponent.first-1, m_closestOpponent.second-1, m_closestOpponent.first,m_closestOpponent.second, m_color); 
            showDefenseDecision(m_closestOpponent.first-1,m_closestOpponent.second-1,"southeast",m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }

        // MAYBE first -1 ???
        // If a there is an available piece located SW, move to block the oppponent piece.
        else if(localBoard -> isValidPieceToMove(m_color,m_closestOpponent.first,m_closestOpponent.second-1) && localBoard -> isValidLocationToMove(m_closestOpponent.first,m_closestOpponent.second))
        //boardTable[m_closestOpponent.first][m_closestOpponent.second-2] == m_color
        {
            localBoard -> updateBoard(m_closestOpponent.first, m_closestOpponent.second-1, m_closestOpponent.first,m_closestOpponent.second, m_color); 
            showDefenseDecision(m_closestOpponent.first,m_closestOpponent.second-1,"northeast",m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }
        // If a there is an available piece located N, move to block the oppponent piece.
        else if(localBoard -> isValidPieceToMove(m_color,m_closestOpponent.first-1,m_closestOpponent.second) && localBoard -> isValidLocationToMove(m_closestOpponent.first,m_closestOpponent.second))
        //boardTable[m_closestOpponent.first-2][m_closestOpponent.second] == m_color
        {
            localBoard -> updateBoard(m_closestOpponent.first-1, m_closestOpponent.second, m_closestOpponent.first,m_closestOpponent.second, m_color);
            showDefenseDecision(m_closestOpponent.first -1,m_closestOpponent.second,"southwest",m_closestOpponent.first+1,m_closestOpponent.second+1);
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
        
        if(localBoard -> isValidPieceToMove(m_color,m_closestOpponent.first+1,m_closestOpponent.second-1) && localBoard -> isValidLocationToMove(m_closestOpponent.first+2,m_closestOpponent.second))
        //    boardTable[m_closestOpponent.first-2][m_closestOpponent.second-2] == m_color)
        {
            localBoard -> updateBoard(m_closestOpponent.first+1, m_closestOpponent.second-1, m_closestOpponent.first+1,m_closestOpponent.second, m_color); 
            showDefenseDecision(m_closestOpponent.first+1,m_closestOpponent.second-1,"southeast",m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }

        // MAYBE first -1 ???
        // Check if there is an available piece from the Southwest.
        else if(localBoard -> isValidPieceToMove(m_color,m_closestOpponent.first+3,m_closestOpponent.second-1) && localBoard -> isValidLocationToMove(m_closestOpponent.first+2,m_closestOpponent.second))
        //boardTable[m_closestOpponent.first][m_closestOpponent.second-2] == m_color
        {
            localBoard -> updateBoard(m_closestOpponent.first+3, m_closestOpponent.second-1, m_closestOpponent.first+2,m_closestOpponent.second, m_color); 
            showDefenseDecision(m_closestOpponent.first+3,m_closestOpponent.second-1,"northeast",m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }

        // Check if there is an available piece from the South.
        else if(localBoard -> isValidPieceToMove(m_color,m_closestOpponent.first+3,m_closestOpponent.second+1) && localBoard -> isValidLocationToMove(m_closestOpponent.first+2,m_closestOpponent.second))
        //boardTable[m_closestOpponent.first-2][m_closestOpponent.second] == m_color
        {
            localBoard -> updateBoard(m_closestOpponent.first+3, m_closestOpponent.second+1, m_closestOpponent.first+2,m_closestOpponent.second, m_color);
            showDefenseDecision(m_closestOpponent.first+3,m_closestOpponent.second+1,"northwest",m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }
        // Else report back that it could not be blocked from the west side.
        else 
        {
            return false;
        }

    }
    
}

bool computer::blockFromEast()
{
    std::cout << "blocking from east \n";
    std::cout << "opponent: "<<m_closestOpponent.first <<" " << m_closestOpponent.second << "\n";
    
    if(m_color == 'W')
    {
        // If a there is an available piece located NE, move to block the oppponent piece.
        std::cout << 1 << std::endl;
        if(localBoard -> isValidPieceToMove(m_color,m_closestOpponent.first-1,m_closestOpponent.second+3) && localBoard -> isValidLocationToMove(m_closestOpponent.first,m_closestOpponent.second+2))
        //boardTable[m_closestOpponent.first-2][m_closestOpponent.second+2] == m_color
        {
            localBoard -> updateBoard(m_closestOpponent.first-1, m_closestOpponent.second+3, m_closestOpponent.first,m_closestOpponent.second+2, m_color);
            showDefenseDecision(m_closestOpponent.first-1,m_closestOpponent.second+3,"southwest",m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }
        std::cout << 2 << std::endl;
        // If a there is an available piece located E, move to block the oppponent piece.
        if(localBoard -> isValidPieceToMove(m_color,m_closestOpponent.first+1,m_closestOpponent.second+3) && localBoard -> isValidLocationToMove(m_closestOpponent.first,m_closestOpponent.second+2))
        {
            localBoard -> updateBoard(m_closestOpponent.first+1, m_closestOpponent.second+3, m_closestOpponent.first,m_closestOpponent.second+2, m_color); 
            showDefenseDecision(m_closestOpponent.first +1,m_closestOpponent.second+3,"northeast",m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }
        // If a there is an available piece located N, move to block the oppponent piece.
        std::cout << 3 << std::endl;

        if(localBoard -> isValidPieceToMove(m_color,m_closestOpponent.first-1,m_closestOpponent.second+1) && localBoard -> isValidLocationToMove(m_closestOpponent.first,m_closestOpponent.second+2))
        //boardTable[m_closestOpponent.first-2][m_closestOpponent.second] == m_color
        {
            localBoard -> updateBoard(m_closestOpponent.first-1, m_closestOpponent.second+1, m_closestOpponent.first,m_closestOpponent.second+2, m_color);
            showDefenseDecision(m_closestOpponent.first -1,m_closestOpponent.second,"southeast",m_closestOpponent.first+1,m_closestOpponent.second+1);
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
        if(localBoard -> isValidPieceToMove(m_color,m_closestOpponent.first+1,m_closestOpponent.second+3) && localBoard -> isValidLocationToMove(m_closestOpponent.first+2,m_closestOpponent.second+2))
        //boardTable[m_closestOpponent.first-2][m_closestOpponent.second+2] == m_color
        {
            localBoard -> updateBoard(m_closestOpponent.first+1, m_closestOpponent.second+3, m_closestOpponent.first+2,m_closestOpponent.second+2, m_color);
            showDefenseDecision(m_closestOpponent.first+1,m_closestOpponent.second+3,"southwest",m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }
        std::cout << 2 << std::endl;
        
        // Check if there is an available piece from the Southeast.
        if(localBoard -> isValidPieceToMove(m_color,m_closestOpponent.first+3,m_closestOpponent.second+3) && localBoard -> isValidLocationToMove(m_closestOpponent.first+2,m_closestOpponent.second+2))
        {
            localBoard -> updateBoard(m_closestOpponent.first+3, m_closestOpponent.second+3, m_closestOpponent.first+2,m_closestOpponent.second+2, m_color);
            showDefenseDecision(m_closestOpponent.first +3,m_closestOpponent.second+3,"northeast",m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }
        
        std::cout << 3 << std::endl;

        // Check if there is an available piece from the South.
        if(localBoard -> isValidPieceToMove(m_color,m_closestOpponent.first+3,m_closestOpponent.second+1) && localBoard -> isValidLocationToMove(m_closestOpponent.first+2,m_closestOpponent.second+2))
        //boardTable[m_closestOpponent.first-2][m_closestOpponent.second] == m_color
        {
            localBoard -> updateBoard(m_closestOpponent.first+3, m_closestOpponent.second+1, m_closestOpponent.first+2,m_closestOpponent.second+2, m_color); 
            showDefenseDecision(m_closestOpponent.first +3,m_closestOpponent.second +1,"southeast",m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }

        std::cout << 4 << std::endl;
        // Else report back that it could not be blocked from the west side.
        return false;   
    }
    
    
};



//Prioritize defense
void
computer::play(board &gameBoard)
{
    // Update the state of the board in order for the computer to make accurate decisions.
    localBoard = &gameBoard;

    updateState();

    // Begin iterator for the list of pieces availabe.
    availablePiecesIter availablePieces = (*m_availablePieces).begin();
    


    // Strategy if the computer is white.
    // White pieces play from top going down on board.
    if(m_color == 'W')
    {
        //IF - opponent's piece is close to home, check if that piece is blocked.
        if(m_closestOpponent.first <= std::sqrt(m_boardSize))
        {
            //IF - if the opponent's piece is already blocked, continue to play offensively.
            if( boardTable[m_closestOpponent.first-1][m_closestOpponent.second-1] == m_color && boardTable[m_closestOpponent.first-1][m_closestOpponent.second+1] == m_color)
            {   
                std::cout << "Piece is already blocked. " << boardTable[m_closestOpponent.first-1][m_closestOpponent.second-1] << boardTable[m_closestOpponent.first-1][m_closestOpponent.second+1] << " \n";
                playOffensively();      
            }                
            //ELSE - Check available pieces that can block opponent.
            else
            {   
                // Check if west side is blocked, if so, then prepare to block from east.
                if(!blockFromEast())
                {
                    if(!blockFromWest())
                    {
                        playOffensively();
                    }
                }
            }
        }
        else
        //ELSE - randomly move piece to opponent's end.
        {
            // Check capture strategy.

            // Check if all pieces are stuck and one must retreat.
            checkForRetreat();

            // Advance one piece forward.
            playOffensively();   
        }
    }

    // Computer is black
    else
    {
        if(m_closestOpponent.first+1 >= std::sqrt(m_boardSize))
        {
            //IF - if the opponent's piece is already blocked, continue to play offensively.
            if( localBoard -> isValidOpenLocation(m_closestOpponent.first+2,m_closestOpponent.second) && localBoard -> isValidOpenLocation(m_closestOpponent.first+2,m_closestOpponent.second+2))
            {   
                std::cout << "Piece is already blocked. " << boardTable[m_closestOpponent.first+2][m_closestOpponent.second] << boardTable[m_closestOpponent.first+2][m_closestOpponent.second+2] << " \n";
                playOffensively();      
            }                
            //ELSE - Check available pieces that can block opponent.
            else
            {
                //if(boardTable[m_closestOpponent.first-2][m_closestOpponent.second] == m_color)
                std::cout << "Moving to block piece at " << "(" << m_closestOpponent.first + 1<< "," << m_closestOpponent.second + 1 << "). \n";

                std::cout<<"moving piece to block it"<<std::endl;

                bool didBlock = false;
                
                // Check if west side is blocked, if so, then prepare to block from east.
                if(localBoard -> isValidOpenLocation(m_closestOpponent.first+2,m_closestOpponent.second))
                {
                    didBlock = blockFromEast();
                }
                if(localBoard -> isValidOpenLocation(m_closestOpponent.first+2,m_closestOpponent.second+2))
                {
                    didBlock = blockFromWest();
                }
                if(!didBlock)
                {
                    playOffensively();
                }
            }
        }
        else
        //ELSE - randomly move piece to opponent's end.
        {
            playOffensively();   
        }
    }
    
    delete m_availablePieces;
    
};

// Allows computer to recognize friendly and opponent pieces.
void computer::updateState()
{
    boardTable = localBoard -> getBoard();
    m_boardSize = localBoard -> getBoardSize();

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