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

void player::help(board &gameBoard,char a_color,char a_opponentColor)
{
    m_color = a_color;
    m_opponentColor = a_opponentColor;
    localBoard = &gameBoard;
    updateState();

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
                if(!playCapture())
                {
                    if(checkForRetreat())
                    {
                        playRetreat();
                    }
                    else
                    {
                        playOffensively();
                    }
                }
            }                
            //ELSE - Check available pieces that can block opponent.
            else
            {   
                // Check if west side is blocked, if so, then prepare to block from east.
                if(!blockFromEast())
                {
                    if(!blockFromWest())
                    {
                        if(!playCapture())
                        {
                            if(checkForRetreat())
                            {
                                playRetreat();
                            }
                            else
                            {
                                playOffensively();
                            }
                        }
                    }
                }
            }
        }
        else
        //ELSE - randomly move piece to opponent's end.
        {
            if(!playCapture())
            {
                if(checkForRetreat())
                {
                    playRetreat();
                }
                else
                {
                    playOffensively();
                }
            }
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
                if(!playCapture())
                {
                    if(checkForRetreat())
                    {
                        playRetreat();
                    }
                    else
                    {
                        playOffensively();
                    }
                }
            }                
            //ELSE - Check available pieces that can block opponent.
            else
            {
                // Check if west side is blocked, if so, then prepare to block from east.
                if(!blockFromEast())
                {
                    if(!blockFromWest())
                    {
                        if(!playCapture())
                        {
                            if(checkForRetreat())
                            {
                                playRetreat();
                            }
                            else
                            {
                                playOffensively();
                            }
                        }
                    }
                }
            }
        }
        else
        //ELSE - randomly move piece to opponent's end.
        {
            if(!playCapture())
            {
                if(checkForRetreat())
                {
                    playRetreat();
                }
                else
                {
                    playOffensively();
                }
            }
        }
    }
    
    delete m_availablePieces;
    
};

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
player::showDefenseDecision(int a_initialRow, int a_initialColumn,std::string a_direction, int a_finalRow, int a_finalColumn)
{
    std::cout << "It is suggested to move the piece at (" << a_initialRow << "," << a_initialColumn << ") " << a_direction << "." << std::endl;
    std::cout << "This will block the piece at ("<< a_finalRow <<","<<a_finalColumn <<")." << std::endl;
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
player::showOffenseDecision(int a_initialRow, int a_initialColumn,std::string a_direction, int a_finalRow, int a_finalColumn)
{
    std::cout << "It is suggested to move the piece at (" << a_initialRow << "," << a_initialColumn << ") " << a_direction << "." << std::endl;
    std::cout << "This will advance the piece to (" << a_finalRow << "," << a_finalColumn << ")" << std::endl;
}

void
player::showRetreatDecision(int a_initialRow, int a_initialColumn,std::string a_direction, int a_finalRow, int a_finalColumn)
{
    std::cout << "It is suggested to move the piece at (" << a_initialRow << "," << a_initialColumn << ") " << a_direction << "." << std::endl;
    std::cout << "This will retreat the piece back to (" << a_finalRow << "," << a_finalColumn << ")" << std::endl;
}

void
player::showCaptureDecision(int a_initialRow, int a_initialColumn,std::string a_direction, int a_finalRow, int a_finalColumn)
{
    std::cout << "It is suggested to move the piece at (" << a_initialRow << "," << a_initialColumn << ") " << a_direction << "." << std::endl;
    std::cout << "This will capture the other piece at (" << a_finalRow << "," << a_finalColumn << ")" << std::endl;
}


bool player::blockFromWest()
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
            showDefenseDecision(m_closestOpponent.first-1,m_closestOpponent.second-1,"southeast",m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }

        // MAYBE first -1 ???
        // If a there is an available piece located SW, move to block the oppponent piece.
        else if(localBoard -> isValidPieceToMove(m_color,m_closestOpponent.first,m_closestOpponent.second-1) && localBoard -> isValidLocationToMove(m_closestOpponent.first,m_closestOpponent.second))
        //boardTable[m_closestOpponent.first][m_closestOpponent.second-2] == m_color
        {
            showDefenseDecision(m_closestOpponent.first,m_closestOpponent.second-1,"northeast",m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }
        // If a there is an available piece located N, move to block the oppponent piece.
        else if(localBoard -> isValidPieceToMove(m_color,m_closestOpponent.first-1,m_closestOpponent.second) && localBoard -> isValidLocationToMove(m_closestOpponent.first,m_closestOpponent.second))
        //boardTable[m_closestOpponent.first-2][m_closestOpponent.second] == m_color
        {
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
            showDefenseDecision(m_closestOpponent.first+1,m_closestOpponent.second-1,"southeast",m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }

        // MAYBE first -1 ???
        // Check if there is an available piece from the Southwest.
        else if(localBoard -> isValidPieceToMove(m_color,m_closestOpponent.first+3,m_closestOpponent.second-1) && localBoard -> isValidLocationToMove(m_closestOpponent.first+2,m_closestOpponent.second))
        //boardTable[m_closestOpponent.first][m_closestOpponent.second-2] == m_color
        {
            showDefenseDecision(m_closestOpponent.first+3,m_closestOpponent.second-1,"northeast",m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }

        // Check if there is an available piece from the South.
        else if(localBoard -> isValidPieceToMove(m_color,m_closestOpponent.first+3,m_closestOpponent.second+1) && localBoard -> isValidLocationToMove(m_closestOpponent.first+2,m_closestOpponent.second))
        //boardTable[m_closestOpponent.first-2][m_closestOpponent.second] == m_color
        {
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

bool player::blockFromEast()
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
            showDefenseDecision(m_closestOpponent.first-1,m_closestOpponent.second+3,"southwest",m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }
        std::cout << 2 << std::endl;
        // If a there is an available piece located E, move to block the oppponent piece.
        if(localBoard -> isValidPieceToMove(m_color,m_closestOpponent.first+1,m_closestOpponent.second+3) && localBoard -> isValidLocationToMove(m_closestOpponent.first,m_closestOpponent.second+2))
        {
            showDefenseDecision(m_closestOpponent.first +1,m_closestOpponent.second+3,"northeast",m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }
        // If a there is an available piece located N, move to block the oppponent piece.
        std::cout << 3 << std::endl;

        if(localBoard -> isValidPieceToMove(m_color,m_closestOpponent.first-1,m_closestOpponent.second+1) && localBoard -> isValidLocationToMove(m_closestOpponent.first,m_closestOpponent.second+2))
        //boardTable[m_closestOpponent.first-2][m_closestOpponent.second] == m_color
        {
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
            showDefenseDecision(m_closestOpponent.first+1,m_closestOpponent.second+3,"southwest",m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }
        std::cout << 2 << std::endl;
        
        // Check if there is an available piece from the Southeast.
        if(localBoard -> isValidPieceToMove(m_color,m_closestOpponent.first+3,m_closestOpponent.second+3) && localBoard -> isValidLocationToMove(m_closestOpponent.first+2,m_closestOpponent.second+2))
        {
            showDefenseDecision(m_closestOpponent.first +3,m_closestOpponent.second+3,"northeast",m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }
        
        std::cout << 3 << std::endl;

        // Check if there is an available piece from the South.
        if(localBoard -> isValidPieceToMove(m_color,m_closestOpponent.first+3,m_closestOpponent.second+1) && localBoard -> isValidLocationToMove(m_closestOpponent.first+2,m_closestOpponent.second+2))
        //boardTable[m_closestOpponent.first-2][m_closestOpponent.second] == m_color
        {
            showDefenseDecision(m_closestOpponent.first +3,m_closestOpponent.second +1,"southeast",m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }

        std::cout << 4 << std::endl;
        // Else report back that it could not be blocked from the west side.
        return false;   
    }
    
    
};


// Allows computer to recognize friendly and opponent pieces.
void player::updateState()
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

bool player::playCapture()
{
    for( std::pair<int,int> eachPiece : (*m_availablePieces))
    {
        // Check if piece is a super piece.
        if(localBoard -> getPieceAtLocation(eachPiece.first+1,eachPiece.second+1) == tolower(m_color,std::locale()))
        {
            std::cout << "found super piece\n";
            // Check if opponent is located southeast.
            if(localBoard->getPieceAtLocation(eachPiece.first+2,eachPiece.second+2) == m_opponentColor || localBoard->getPieceAtLocation(eachPiece.first+2,eachPiece.second+2) == tolower(m_opponentColor,std::locale()) )
            {
                // Check if piece can move Southeast.
                if(localBoard -> isValidLocationToMove(eachPiece.first+2,eachPiece.second+2,true))
                {
                    showCaptureDecision( eachPiece.first + 1,eachPiece.second + 1,"southeast",eachPiece.first+2,eachPiece.second+2);
                    return true;
                }
            }
            // Check if opponent is located Southwest.
            else if(localBoard->getPieceAtLocation(eachPiece.first+2,eachPiece.second) == m_opponentColor || localBoard->getPieceAtLocation(eachPiece.first+2,eachPiece.second) == tolower(m_opponentColor,std::locale()) )
            {
                // Check if piece can move Southwest.
                if(localBoard -> isValidLocationToMove(eachPiece.first+2,eachPiece.second,true))
                {
                    showCaptureDecision( eachPiece.first + 1,eachPiece.second + 1,"southwest",eachPiece.first+2,eachPiece.second);
                    return true;
                }
            }
            // Check if opponent is located Northwest.
            else if(localBoard->getPieceAtLocation(eachPiece.first,eachPiece.second) == m_opponentColor || localBoard->getPieceAtLocation(eachPiece.first,eachPiece.second) == tolower(m_opponentColor,std::locale()) )
            {
                // Check if piece can move Northwest.
                if(localBoard -> isValidLocationToMove(eachPiece.first,eachPiece.second,true))
                {
                    showCaptureDecision( eachPiece.first + 1,eachPiece.second + 1,"northwest",eachPiece.first,eachPiece.second);
                    return true;
                }
            }
            // Check if opponent is located Northeast.
            else if(localBoard->getPieceAtLocation(eachPiece.first,eachPiece.second+2) == m_opponentColor || localBoard->getPieceAtLocation(eachPiece.first,eachPiece.second+2) == tolower(m_opponentColor,std::locale()) )
            {
                // Check if piece can move Northeast.
                if(localBoard -> isValidLocationToMove(eachPiece.first,eachPiece.second+2,true))
                {
                    showCaptureDecision( eachPiece.first + 1,eachPiece.second + 1,"northeast",eachPiece.first,eachPiece.second+2);
                    return true;
                }
            }               
        }
    }
    // No available moves that can capture pieces.
    return false;    
}


bool player::checkForRetreat()
{
    if(m_color == 'W')
    {
        for( std::pair<int,int> eachPiece : (*m_availablePieces))
        {
            // Check if piece can move Southeast.
            if(localBoard -> isValidLocationToMove(eachPiece.first+2,eachPiece.second+2))
            {
                return false;
            }
            // Check if piece can move Southwest.
            else if(localBoard -> isValidLocationToMove(eachPiece.first+2,eachPiece.second))
            {
                return false;
            }
        }
        // There are no available pieces that can move forward.
        return true;
    }

    if(m_color == 'B')
    {
        for( std::pair<int,int> eachPiece : (*m_availablePieces))
        {
            // Check if piece can move Northeast.
            if(localBoard -> isValidLocationToMove(eachPiece.first,eachPiece.second+2))
            {
                return false;
            }
            // Check if piece can move Northwest.
            else if(localBoard -> isValidLocationToMove(eachPiece.first,eachPiece.second))
            {
                return false;
            }
        }
        // There are no available pieces that can move forward.
        return true;
    }
};

void 
player::playRetreat()
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
                // Retreat Northwest.
                if(localBoard -> isValidLocationToMove(pieceToMove.first,pieceToMove.second))
                {
                    showRetreatDecision( pieceToMove.first + 1,pieceToMove.second + 1,"northwest",pieceToMove.first,pieceToMove.second);
                    didMove = false;
                }
                // Retreat Northeast
                else if(localBoard -> isValidLocationToMove(pieceToMove.first,pieceToMove.second+2))
                {
                    showRetreatDecision(pieceToMove.first + 1,pieceToMove.second + 1,"northeast",pieceToMove.first, pieceToMove.second+2);
                    didMove = false;
                }
            }
        }  
    }
    else
    {
        bool didMove = true;
        while(didMove)
        {
            std::pair<int,int> pieceToMove = pickRandomPiece();

            if(localBoard -> isValidPieceToMove(m_color,pieceToMove.first+1,pieceToMove.second+1))
            {
                // Retreat Southeast.
                if(localBoard -> isValidLocationToMove(pieceToMove.first+2,pieceToMove.second+2))
                {
                    showRetreatDecision( pieceToMove.first + 1,pieceToMove.second + 1,"southeast",pieceToMove.first + 2,pieceToMove.second + 2);
                    didMove = false;
                }
                // Retreat Southwest.
                else if(localBoard -> isValidLocationToMove(pieceToMove.first+2,pieceToMove.second))
                {
                    showRetreatDecision(pieceToMove.first + 1,pieceToMove.second + 1,"southwest",pieceToMove.first + 2, pieceToMove.second);
                    didMove = false;
                }
            }
        } 
    }  
};

void
player::playOffensively()
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
                    showOffenseDecision( pieceToMove.first + 1,pieceToMove.second + 1,"southeast",pieceToMove.first + 2,pieceToMove.second + 2);
                    didMove = false;
                }
                else if(localBoard -> isValidLocationToMove(pieceToMove.first+2,pieceToMove.second))
                {
                    showOffenseDecision(pieceToMove.first + 1,pieceToMove.second + 1,"southwest",pieceToMove.first + 2, pieceToMove.second);
                    didMove = false;
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
                    showOffenseDecision(pieceToMove.first + 1,pieceToMove.second + 1,"northeast",pieceToMove.first,pieceToMove.second + 2);
                    didMove = false;
                }
                else if(localBoard -> isValidLocationToMove(pieceToMove.first,pieceToMove.second))
                {
                    showOffenseDecision(pieceToMove.first + 1,pieceToMove.second + 1,"northwest",pieceToMove.first,pieceToMove.second);
                    didMove = false;
                }
            }
        }
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
player::pickRandomPiece()
{
    return (*m_availablePieces)[rand() % (m_availablePieces->size()-1)];
}