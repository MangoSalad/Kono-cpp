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

/* ********************************************************************* 
Function Name: showRetreatDecision 
Purpose: Shows the computer's decision to play in retreat.
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
computer::showRetreatDecision(int a_initialRow, int a_initialColumn,std::string a_direction, int a_finalRow, int a_finalColumn)
{
    std::cout << "The computer moved the piece at (" << a_initialRow << "," << a_initialColumn << ") " << a_direction << "." << std::endl;
    std::cout << "It wanted to retreat its piece to (" << a_finalRow << "," << a_finalColumn << ")" << std::endl;
}

/* ********************************************************************* 
Function Name: showCaptureDecision 
Purpose: Shows the computer's decision to capture a piece.
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
computer::showCaptureDecision(int a_initialRow, int a_initialColumn,std::string a_direction, int a_finalRow, int a_finalColumn)
{
    std::cout << "The computer moved the piece at (" << a_initialRow << "," << a_initialColumn << ") " << a_direction << "." << std::endl;
    std::cout << "It wanted to capture the human piece at (" << a_finalRow << "," << a_finalColumn << ")" << std::endl;
}

/* ********************************************************************* 
Function Name: blockFromWest 
Purpose: Part of the computer's strategy, check to see if a particular piece can be blocked from the west. 
    Check to see if there is a valid piece that can be moved from either southwest, north, south, southeast or northwest.
Parameters: 
            none.
Return Value: Boolean value confirming that a computer piece was moved in order to block an opponent piece.
Local Variables: 
            none.
Algorithm: 
            1) Depending on if the computer is white or black, different piece positions will be checked.
            2) If computer is white do steps 3 - 5
            3) Check if a piece is located northwest of an opponent piece, if so, then move the computer piece southeast to block it.
            4) Check if a piece is located southwest of an opponent piece, if so, then move the computer piece northeast to block it.
            5) Check if a piece is located north of an opponent piece, if so, then move the computer piece southwest to block it.
            6) If computer is black do steps 7 - 9
            7) Check if a piece is located west of an opponent piece, if so, then move the computer piece southwest to block it.
            8) Check if a piece is located southwest of an opponent piece, if so, then move the computer piece northeast to block it.
            9) Check if a piece is located south of an opponent piece, if so, then move the computer piece northwest to block it.
            10) If cannot find a valid piece to block with, then return false. If a piece blocked the opponent piece, then return true.
Assistance Received: none 
********************************************************************* */
bool
computer::blockFromWest()
{
    // Computer color is white.
    if(m_color == 'W')
    {
        // If a there is an available piece located NW, move to block the oppponent piece.
        if(localBoard -> isValidPieceToMove(m_color,m_closestOpponent.first-1,m_closestOpponent.second-1) && localBoard -> isValidLocationToMove(m_closestOpponent.first,m_closestOpponent.second))
        {
            localBoard -> updateBoard(m_closestOpponent.first-1, m_closestOpponent.second-1, m_closestOpponent.first,m_closestOpponent.second, m_color); 
            showDefenseDecision(m_closestOpponent.first-1,m_closestOpponent.second-1,"southeast",m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }

        // If a there is an available piece located SW, move to block the oppponent piece.
        else if(localBoard -> isValidPieceToMove(m_color,m_closestOpponent.first,m_closestOpponent.second-1) && localBoard -> isValidLocationToMove(m_closestOpponent.first,m_closestOpponent.second))
        {
            localBoard -> updateBoard(m_closestOpponent.first, m_closestOpponent.second-1, m_closestOpponent.first,m_closestOpponent.second, m_color); 
            showDefenseDecision(m_closestOpponent.first,m_closestOpponent.second-1,"northeast",m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }
        // If a there is an available piece located N, move to block the oppponent piece.
        else if(localBoard -> isValidPieceToMove(m_color,m_closestOpponent.first-1,m_closestOpponent.second) && localBoard -> isValidLocationToMove(m_closestOpponent.first,m_closestOpponent.second))
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
        {
            localBoard -> updateBoard(m_closestOpponent.first+1, m_closestOpponent.second-1, m_closestOpponent.first+2,m_closestOpponent.second, m_color); 
            showDefenseDecision(m_closestOpponent.first+1,m_closestOpponent.second-1,"southeast",m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }
        
        // Check if there is an available piece from the Southwest.
        else if(localBoard -> isValidPieceToMove(m_color,m_closestOpponent.first+3,m_closestOpponent.second-1) && localBoard -> isValidLocationToMove(m_closestOpponent.first+2,m_closestOpponent.second))
        {
            localBoard -> updateBoard(m_closestOpponent.first+3, m_closestOpponent.second-1, m_closestOpponent.first+2,m_closestOpponent.second, m_color); 
            showDefenseDecision(m_closestOpponent.first+3,m_closestOpponent.second-1,"northeast",m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }

        // Check if there is an available piece from the South.
        else if(localBoard -> isValidPieceToMove(m_color,m_closestOpponent.first+3,m_closestOpponent.second+1) && localBoard -> isValidLocationToMove(m_closestOpponent.first+2,m_closestOpponent.second))
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

/* ********************************************************************* 
Function Name: blockFromEast 
Purpose: Part of the computer's strategy, check to see if a particular piece can be blocked from the east. 
    Check to see if there is a valid piece that can be moved from either southwest, north, south, southeast, or northwest.
Parameters: 
            none.
Return Value: Boolean value confirming that a computer piece was moved in order to block an opponent piece.
Local Variables: 
            none.
Algorithm: 
            1) Depending on if the computer is white or black, different piece positions will be checked.
            2) If computer is white do steps 3 - 5
            3) Check if a piece is located northeast of an opponent piece, if so, then move the computer piece southwest to block it.
            4) Check if a piece is located southwest of an opponent piece, if so, then move the computer piece northeast to block it.
            5) Check if a piece is located north of an opponent piece, if so, then move the computer piece southeast to block it.
            6) If computer is black do steps 7 - 9
            7) Check if a piece is located east of an opponent piece, if so, then move the computer piece southwest to block it.
            8) Check if a piece is located southeast of an opponent piece, if so, then move the computer piece northeast to block it.
            9) Check if a piece is located south of an opponent piece, if so, then move the computer piece southeast to block it.
            10) If cannot find a valid piece to block with, then return false. If a piece blocked the opponent piece, then return true.
Assistance Received: none 
********************************************************************* */
bool
computer::blockFromEast()
{   
    if(m_color == 'W')
    {
        // If a there is an available piece located NE, move to block the oppponent piece.
        if(localBoard -> isValidPieceToMove(m_color,m_closestOpponent.first-1,m_closestOpponent.second+3) && localBoard -> isValidLocationToMove(m_closestOpponent.first,m_closestOpponent.second+2))
        //boardTable[m_closestOpponent.first-2][m_closestOpponent.second+2] == m_color
        {
            localBoard -> updateBoard(m_closestOpponent.first-1, m_closestOpponent.second+3, m_closestOpponent.first,m_closestOpponent.second+2, m_color);
            showDefenseDecision(m_closestOpponent.first-1,m_closestOpponent.second+3,"southwest",m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }
        // If a there is an available piece located E, move to block the oppponent piece.
        if(localBoard -> isValidPieceToMove(m_color,m_closestOpponent.first+1,m_closestOpponent.second+3) && localBoard -> isValidLocationToMove(m_closestOpponent.first,m_closestOpponent.second+2))
        {
            localBoard -> updateBoard(m_closestOpponent.first+1, m_closestOpponent.second+3, m_closestOpponent.first,m_closestOpponent.second+2, m_color); 
            showDefenseDecision(m_closestOpponent.first +1,m_closestOpponent.second+3,"northeast",m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }
        // If a there is an available piece located N, move to block the oppponent piece.

        if(localBoard -> isValidPieceToMove(m_color,m_closestOpponent.first-1,m_closestOpponent.second+1) && localBoard -> isValidLocationToMove(m_closestOpponent.first,m_closestOpponent.second+2))
        //boardTable[m_closestOpponent.first-2][m_closestOpponent.second] == m_color
        {
            localBoard -> updateBoard(m_closestOpponent.first-1, m_closestOpponent.second+1, m_closestOpponent.first,m_closestOpponent.second+2, m_color);
            showDefenseDecision(m_closestOpponent.first -1,m_closestOpponent.second,"southeast",m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }

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
        
        // Check if there is an available piece from the Southeast.
        if(localBoard -> isValidPieceToMove(m_color,m_closestOpponent.first+3,m_closestOpponent.second+3) && localBoard -> isValidLocationToMove(m_closestOpponent.first+2,m_closestOpponent.second+2))
        {
            localBoard -> updateBoard(m_closestOpponent.first+3, m_closestOpponent.second+3, m_closestOpponent.first+2,m_closestOpponent.second+2, m_color);
            showDefenseDecision(m_closestOpponent.first +3,m_closestOpponent.second+3,"northeast",m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }
        

        // Check if there is an available piece from the South.
        if(localBoard -> isValidPieceToMove(m_color,m_closestOpponent.first+3,m_closestOpponent.second+1) && localBoard -> isValidLocationToMove(m_closestOpponent.first+2,m_closestOpponent.second+2))
        //boardTable[m_closestOpponent.first-2][m_closestOpponent.second] == m_color
        {
            localBoard -> updateBoard(m_closestOpponent.first+3, m_closestOpponent.second+1, m_closestOpponent.first+2,m_closestOpponent.second+2, m_color); 
            showDefenseDecision(m_closestOpponent.first +3,m_closestOpponent.second +1,"southeast",m_closestOpponent.first+1,m_closestOpponent.second+1);
            return true;
        }

        // Else report back that it could not be blocked from the west side.
        return false;   
    } 
};


/* ********************************************************************* 
Function Name: play 
Purpose: Main function that controls the computer strategy. Depending on the positions of pieces, play will delegate the computer to do a certain strategy.
Parameters: 
            gameBoard, pointer to an instantiated board object.
Return Value: none.
Local Variables: 
            none.
Algorithm: 
            1) Call updateState method to update the computer's list of available pieces and positions of opponent pieces.
            2) Check the color of the computer.
            3) If opponent piece is close to the home side, then attempt to block it.
            4) If blocked or cannot block, then continue.
            5) Check if computer has any super pieces available, if so, then attempt to capture an opponent piece.
            6) If no super pieces are available or cannot capture opponent piece, then check if any pieces can advance forward to enemy side.
            7) If no pieces can advance, then retreat.
            8) If pieces available to move forward, then play offensively and move forward.
Assistance Received: none 
********************************************************************* */
void
computer::play(board &gameBoard)
{
    // Update state of the board for computer.
    updateState(gameBoard, m_color,m_opponentColor);

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
                // Check if any available super pieces can capture. 
                if(!playCapture())
                {
                    if(checkForRetreat())
                    {
                        playRetreat();
                    }
                    // Move a piece forward.
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
                        // Check if any available super pieces can capture.
                        if(!playCapture())
                        {
                            if(checkForRetreat())
                            {
                                playRetreat();
                            }
                            // Move a piece forward.
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
            // Check if any available super pieces can capture.
            if(!playCapture())
            {
                if(checkForRetreat())
                {
                    playRetreat();
                }
                // Move a piece forward.
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
                // Check if any available super pieces can capture.
                if(!playCapture())
                {
                    if(checkForRetreat())
                    {
                        playRetreat();
                    }
                    // Move a piece forward.
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
                        // Check if any available super pieces can capture.
                        if(!playCapture())
                        {
                            if(checkForRetreat())
                            {
                                playRetreat();
                            }
                            // Move a piece forward.
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
            // Check if any available super pieces can capture.
            if(!playCapture())
            {
                if(checkForRetreat())
                {
                    playRetreat();
                }
                // Move a piece forward.
                else
                {
                    playOffensively();
                }
            }
        }
    }   

    // Free space.
    delete m_availablePieces;
};

/* ********************************************************************* 
Function Name: playCapture 
Purpose: Check if the computer has any super pieces that can capture a nearby oppponent piece.
Parameters: 
            none.
Return Value: Boolean value for it there was a super piece that captured an opponent piece.
Local Variables: 
            eachPiece, a pair of integers holding the coordinates of a computer piece.
Algorithm: 
            1) Cycle through available pieces and see if the piece is a super piece.
            2) If there is a super piece, then do steps 3 - 6, else return false.
            3) Check if opponent is located in southeast, if so then capture. And return true.
            4) Check if opponent is located in southwest, if so then capture. And return true.
            5) Check if opponent is located in northwest, if so then capture. And return true.
            6) Check if opponent is located in northeast, if so then capture. And return true.
            7) If no pieces can capture, then return false.
Assistance Received: none 
********************************************************************* */
bool
computer::playCapture()
{
    for( std::pair<int,int> eachPiece : (*m_availablePieces))
    {
        // Check if piece is a super piece.
        if(localBoard -> getPieceAtLocation(eachPiece.first+1,eachPiece.second+1) == tolower(m_color,std::locale()))
        {
            // Check if opponent is located southeast.
            if(localBoard->getPieceAtLocation(eachPiece.first+2,eachPiece.second+2) == m_opponentColor || localBoard->getPieceAtLocation(eachPiece.first+2,eachPiece.second+2) == tolower(m_opponentColor,std::locale()) )
            {
                // Check if piece can move Southeast.
                if(localBoard -> isValidLocationToMove(eachPiece.first+2,eachPiece.second+2,true))
                {
                    localBoard -> updateBoard(eachPiece.first+1, eachPiece.second+1, eachPiece.first+2,eachPiece.second+2, m_color);
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
                    localBoard -> updateBoard(eachPiece.first+1, eachPiece.second+1, eachPiece.first+2,eachPiece.second, m_color);
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
                    localBoard -> updateBoard(eachPiece.first+1, eachPiece.second+1, eachPiece.first,eachPiece.second, m_color);
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
                    localBoard -> updateBoard(eachPiece.first+1, eachPiece.second+1, eachPiece.first,eachPiece.second+2, m_color);
                    showCaptureDecision( eachPiece.first + 1,eachPiece.second + 1,"northeast",eachPiece.first,eachPiece.second+2);
                    return true;
                }
            }               
        }
    }

    // No available moves that can capture pieces.
    return false;    
};

/* ********************************************************************* 
Function Name: playRetreat 
Purpose: Called when a piece must be sent in retreat. It randomly picks a piece and sends it the opposite direction of the opponent's home side.
Parameters: 
            none.
Return Value: none.
Local Variables: 
            didMove, boolean holding if computer made move.
            pieceToMove, a pair of integers holding the coordinates of a computer piece.
Algorithm: 
            1) Cycle through available pieces.
            2) If white, do steps 3-4 
            3) Check if piece can move northwest, if so then move northwest.
            4) Check if piece can move northeast, if so then move northeast.
            5) If black, do steps 6-7
            6) Check if piece can move southeast, if so then move southeast.
            7) Check if piece can move southwest, if so then move southwest.
Assistance Received: none 
********************************************************************* */
void 
computer::playRetreat()
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
                    localBoard -> updateBoard(pieceToMove.first+1, pieceToMove.second+1, pieceToMove.first,pieceToMove.second, m_color);
                    showRetreatDecision( pieceToMove.first + 1,pieceToMove.second + 1,"northwest",pieceToMove.first,pieceToMove.second);
                    didMove = false;
                }
                // Retreat Northeast
                else if(localBoard -> isValidLocationToMove(pieceToMove.first,pieceToMove.second+2))
                {
                    localBoard -> updateBoard(pieceToMove.first+1, pieceToMove.second+1, pieceToMove.first,pieceToMove.second+2, m_color);
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
                    localBoard -> updateBoard(pieceToMove.first+1, pieceToMove.second+1, pieceToMove.first+2,pieceToMove.second+2, m_color);
                    showRetreatDecision( pieceToMove.first + 1,pieceToMove.second + 1,"southeast",pieceToMove.first + 2,pieceToMove.second + 2);
                    didMove = false;
                }
                // Retreat Southwest.
                else if(localBoard -> isValidLocationToMove(pieceToMove.first+2,pieceToMove.second))
                {
                    localBoard -> updateBoard(pieceToMove.first+1, pieceToMove.second+1, pieceToMove.first+2,pieceToMove.second, m_color);
                    showRetreatDecision(pieceToMove.first + 1,pieceToMove.second + 1,"southwest",pieceToMove.first + 2, pieceToMove.second);
                    didMove = false;
                }
            }
        } 
    }  
};

/* ********************************************************************* 
Function Name: playOffensively 
Purpose: Called when computer strategy must be offensive. Function picks a random piece to move forward towards the opponent's home side.
Parameters: 
            none.
Return Value: none.
Local Variables: 
            didMove, boolean holding if computer made move.
Algorithm:            
            1) If white, do steps 2-3
            2) Check if piece can move southeast, if so then move southeast.
            3) Check if piece can move southwest, if so then move southwest. 
            4) If black, do steps 5-6
            5) Check if piece can move northwest, if so then move northwest.
            6) Check if piece can move northeast, if so then move northeast.
Assistance Received: none 
********************************************************************* */
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
            // Check if can be moved southeast, then move there.
            if(localBoard -> isValidPieceToMove(m_color,pieceToMove.first+1,pieceToMove.second+1))
            {
                if(localBoard -> isValidLocationToMove(pieceToMove.first+2,pieceToMove.second+2))
                {
                    localBoard -> updateBoard(pieceToMove.first+1, pieceToMove.second+1, pieceToMove.first+2,pieceToMove.second+2, m_color);
                    showOffenseDecision( pieceToMove.first + 1,pieceToMove.second + 1,"southeast",pieceToMove.first + 2,pieceToMove.second + 2);
                    didMove = false;
                }
                // Check if can be moved southwest, then move there.
                else if(localBoard -> isValidLocationToMove(pieceToMove.first+2,pieceToMove.second))
                {
                    localBoard -> updateBoard(pieceToMove.first+1, pieceToMove.second+1, pieceToMove.first+2,pieceToMove.second, m_color);
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
                // Check if can be moved northeast, then move there.
                if(localBoard -> isValidLocationToMove(pieceToMove.first,pieceToMove.second+2))
                {
                    localBoard -> updateBoard(pieceToMove.first+1, pieceToMove.second+1, pieceToMove.first,pieceToMove.second+2, m_color);
                    showOffenseDecision(pieceToMove.first + 1,pieceToMove.second + 1,"northeast",pieceToMove.first,pieceToMove.second + 2);
                    didMove = false;
                }
                // Check if can be moved northwest, then move there.
                else if(localBoard -> isValidLocationToMove(pieceToMove.first,pieceToMove.second))
                {
                    localBoard -> updateBoard(pieceToMove.first+1, pieceToMove.second+1, pieceToMove.first,pieceToMove.second, m_color);
                    showOffenseDecision(pieceToMove.first + 1,pieceToMove.second + 1,"northwest",pieceToMove.first,pieceToMove.second);
                    didMove = false;
                }
            }
        }
    }
};
