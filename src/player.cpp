#include "stdafx.h"
#include "player.h"
#include "board.h"

player::player()
{
};

void player::play(std::vector< std::vector <char> > &boardTable)
{
};

/* ********************************************************************* 
Function Name: help 
Purpose: Provide help strategy to the player dependent on conditions of the board. 
    In the following order, block strategy, capture strategy, offensive strategy, and retreat strategy are prioritized.
Parameters: 
            gameBoard, pointer to an instantiated board object.
            a_color, color of the player asking for help.
            a_opponentColor, color of the opponent.
Return Value: none.
Local Variables: 
            none.
Algorithm: 
            1) Call updateState method to update the player's list of available pieces and positions of opponent pieces.
            2) Check the color of the player.
            3) If opponent piece is close to the home side, then attempt to block it.
            4) If blocked or cannot block, then continue.
            5) Check if player has any super pieces available, if so, then attempt to capture an opponent piece.
            6) If no super pieces are available or cannot capture opponent piece, then check if any pieces can advance forward to enemy side.
            7) If no pieces can advance, then retreat.
            8) If pieces available to move forward, then play offensively and move forward.
Assistance Received: none 
********************************************************************* */
void player::help(board &gameBoard,char a_color,char a_opponentColor)
{
    m_color = a_color;
    m_opponentColor = a_opponentColor;
    localBoard = &gameBoard;
    updateState(gameBoard, m_color, a_opponentColor);

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
Purpose: Suggest to user to play in defensive strategy (block).
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
Purpose: Suggest to user to play in offensive strategy.
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

/* ********************************************************************* 
Function Name: showRetreatDecision 
Purpose: Suggest to user to play in retreat strategy.
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
player::showRetreatDecision(int a_initialRow, int a_initialColumn,std::string a_direction, int a_finalRow, int a_finalColumn)
{
    std::cout << "It is suggested to move the piece at (" << a_initialRow << "," << a_initialColumn << ") " << a_direction << "." << std::endl;
    std::cout << "This will retreat the piece back to (" << a_finalRow << "," << a_finalColumn << ")" << std::endl;
}

/* ********************************************************************* 
Function Name: showCaptureDecision 
Purpose: Suggest to user to play in capture strategy.
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
player::showCaptureDecision(int a_initialRow, int a_initialColumn,std::string a_direction, int a_finalRow, int a_finalColumn)
{
    std::cout << "It is suggested to move the piece at (" << a_initialRow << "," << a_initialColumn << ") " << a_direction << "." << std::endl;
    std::cout << "This will capture the other piece at (" << a_finalRow << "," << a_finalColumn << ")" << std::endl;
}

/* ********************************************************************* 
Function Name: blockFromWest 
Purpose: Part of the player's strategy, check to see if a particular piece can be blocked from the west. 
    Check to see if there is a valid piece that can be moved from either southwest, north, south, southeast or northwest.
Parameters: 
            none.
Return Value: Boolean value confirming that the player was notified a suggestion to move a piece
Local Variables: 
            none.
Algorithm: 
            1) Depending on if the player is white or black, different piece positions will be checked.
            2) If computer is white do steps 3 - 5
            3) Check if a piece is located northwest of an opponent piece, if so, then suggest for player to block by moving there.
            4) Check if a piece is located southwest of an opponent piece, if so, then suggest for player to block by moving there.
            5) Check if a piece is located north of an opponent piece, if so, then suggest for player to block by moving there.
            6) If player is black do steps 7 - 9
            7) Check if a piece is located west of an opponent piece, if so, then suggest for player to block by moving there.
            8) Check if a piece is located southwest of an opponent piece, if so, then suggest for player to block by moving there.
            9) Check if a piece is located south of an opponent piece, if so, then suggest for player to block by moving there.
            10) If cannot find a valid piece to block with, then return false. If a piece blocked the opponent piece, then return true.
Assistance Received: none 
********************************************************************* */
bool
player::blockFromWest()
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

/* ********************************************************************* 
Function Name: blockFromEast 
Purpose: Part of the player's strategy, check to see if a particular piece can be blocked from the east. 
    Check to see if there is a valid piece that can be moved from either southwest, north, south, southeast, or northwest.
Parameters: 
            none.
Return Value: Boolean value confirming that a computer player was notified a suggestion to block.
Local Variables: 
            none.
Algorithm: 
            1) Depending on if the player is white or black, different piece positions will be checked.
            2) If player is white do steps 3 - 5
            3) Check if a piece is located northeast of an opponent piece, if so, then suggest for player to block by moving there.
            4) Check if a piece is located southwest of an opponent piece, if so, then suggest for player to block by moving there.
            5) Check if a piece is located north of an opponent piece, if so, then suggest for player to block by moving there.
            6) If player is black do steps 7 - 9
            7) Check if a piece is located east of an opponent piece, if so, then suggest for player to block by moving there.
            8) Check if a piece is located southeast of an opponent piece, if so, then suggest for player to block by moving there.
            9) Check if a piece is located south of an opponent piece, if so, then suggest for player to block by moving there.
            10) If cannot find a valid piece to block with, then return false. If a piece blocked the opponent piece, then return true.
Assistance Received: none 
********************************************************************* */
bool
player::blockFromEast()
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

/* ********************************************************************* 
Function Name: updateState 
Purpose: Check if the player has any super pieces that can capture a nearby oppponent piece. If it does, suggest to capture the piece.
Parameters: 
            gameBoard, pointer to an instantiated board object.
            a_color, color of the player asking for help.
            a_opponentColor, color of the opponent.
Return Value: none.
Local Variables: 
            friendlySide, iterator for moving down the board - relative to the color of the piece.
            oppositeSide, iteratore for moving down the board - relative to the color of the piece.
Algorithm: 
            1) Cycle through the board and load friendly pieces into m_availablePieces vector.
            2) Iterate through the board and find the opponent coordinates closest to home side.
            3) Iterate through the board and find the friendly piece coordinates closest to opponent side.
Assistance Received: none 
********************************************************************* */
void
player::updateState(board &a_gameBoard, char a_color,char a_opponentColor)
{
    localBoard = &a_gameBoard;
    m_color = a_color;
    m_opponentColor = a_opponentColor;
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
                m_furthestFriendly = std::make_pair(distance(boardTable.begin(),opponentSide), distance(opponentSide->begin(),col));
                break;
            }
        }
    }

};

/* ********************************************************************* 
Function Name: playCapture 
Purpose: Check if the player has any super pieces that can capture a nearby oppponent piece. If it does, suggest to capture the piece.
Parameters: 
            none.
Return Value: Boolean value for it there was a super piece that can capture an opponent.
Local Variables: 
            eachPiece, a pair of integers holding the coordinates of a player piece.
Algorithm: 
            1) Cycle through available pieces and see if the piece is a super piece.
            2) If there is a super piece, then do steps 3 - 6, else return false.
            3) Check if opponent is located in southeast, if so then suggest to play that they capture it. And return true.
            4) Check if opponent is located in southwest, if so then suggest to play that they capture it. And return true.
            5) Check if opponent is located in northwest, if so then suggest to play that they capture it. And return true.
            6) Check if opponent is located in northeast, if so then suggest to play that they capture it. And return true.
            7) If no pieces can capture, then return false.
Assistance Received: none 
********************************************************************* */
bool
player::playCapture()
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

/* ********************************************************************* 
Function Name: checkForRetreat 
Purpose: Check if any piece can move forward. If it cannot, then it lets the computer know that it must retreat one piece.
Parameters: 
            none.
Return Value: Boolean value to notify computer strategy that it must retreat a piece.
Local Variables: 
            eachPiece, a pair of integers holding the coordinates of a computer piece.
Algorithm: 
            1) Cycle through available pieces.
            2) If white, do steps 3-5 
            3) Check if piece can move southwest, if so return false.
            4) Check if piece can move southeast, if so return false.
            5) If cannot move south, then return true. A piece must be sent in retreat.
            6) If black, do steps 7-9
            7) Check if piece can move northeast, if so return false.
            8) Check if piece can move northwest, if so return false.
            9) If cannot move north, then return true. A piece must be sent in retreat.
Assistance Received: none 
********************************************************************* */
bool
player::checkForRetreat()
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

/* ********************************************************************* 
Function Name: playRetreat 
Purpose: Called when a piece must be sent in retreat. It randomly picks a piece and suggest that the player moves that piece in the direction of home side.
Parameters: 
            none.
Return Value: none.
Local Variables: 
            didMove, boolean holding if player made move.
            pieceToMove, a pair of integers holding the coordinates of a player piece.
Algorithm: 
            1) Cycle through available pieces.
            2) If white, do steps 3-4 
            3) Check if piece can move northwest, if so then suggest that the player move it northwest.
            4) Check if piece can move northeast, if so then suggest that the player move it northeast.
            5) If black, do steps 6-7
            6) Check if piece can move southeast, if so then suggest that the player move it southeast.
            7) Check if piece can move southwest, if so then suggest that the player move it southwest.
Assistance Received: none 
********************************************************************* */
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

/* ********************************************************************* 
Function Name: playOffensively 
Purpose: Called when player strategy must be offensive. Function picks a random piece and suggests player movevs it to opponent's side.
Parameters: 
            none.
Return Value: none.
Local Variables: 
            didMove, boolean holding if computer made move.
Algorithm:            
            1) If white, do steps 2-3
            2) Check if piece can move southeast, if so then suggest that the player move it southeast.
            3) Check if piece can move southwest, if so then suggest that the player move it southwest. 
            4) If black, do steps 5-6
            5) Check if piece can move northwest, if so then suggest that the player move it northwest.
            6) Check if piece can move northeast, if so then suggest that the player move it northeast.
Assistance Received: none 
********************************************************************* */
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
    return (*m_availablePieces)[rand() % (m_availablePieces->size())];
}