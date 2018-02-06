#include "tournament.h"
#include "stdafx.h"

// Default constructor for loading new game.
tournament::tournament()
{
    m_tournamentRound = 0;
    m_computerScore = 0;
    m_humanScore = 0;
    round = new game();
};

// Constructor for loading existing game from file.
tournament::tournament(std::string a_savedGame)
{    
    // File successfully loaded and is valid.
    if(loadSavedFile(a_savedGame))
    {   
        round = new game(m_humanColorFromFile, m_computerColorFromFile, m_nextPlayerFromFile, m_boardSizeFromFile, *m_boardTableFromFile);
    }
    else
    {
        std::cout << "Exiting game now." << std::endl;
        exit(1);
    }
};

// Destructor announces the end of Kono and frees up objects.
tournament::~tournament()
{ 
    std::cout << "Thanks for playing. Exiting game." << std::endl;
    delete round;
};

/* ********************************************************************* 
Function Name: loadSavedFile 
Purpose: Load contents of a saved game file. (serialization)
Parameters: 
            a_savedGame, string passed by value. Holds the name of the file to load.
Return Value: boolean that confirms if the file successfully loaded and is valid.
Local Variables: 
            inFile, ifstream object holding file
            buff, string buffer for parsing lines
            fileContents, vector holding file contents
Algorithm: 
            1) Check if the provided filename is valid and can be found in the current working directory.
            2) Using istringstream, parse each line of the file and load into a buffer.
            3) Push each buffer into a vector.
            4) Each file contents should be in a particular index of the vector. Iterate through the vector and load file contents to local variables.
            5) If all the file contents are of the correct type and properly loaded, then return true. Else, return false.
Assistance Received: none 
********************************************************************* */
bool
tournament::loadSavedFile(std::string a_savedGame)
{
    std::ifstream inFile;
    std::string buff;
    std::vector<std::string> fileContents;

    // If file cannot be open, then cannot proceed.
    inFile.open(a_savedGame);

    if (!inFile)
    {   
        std::cout << "Cannot access file." << std::endl;
        return false;
    }

    // Read entire file line by line and parse line using istringstream.
    while(!inFile.eof())
    {
        getline(inFile, buff);
        std::istringstream line(buff);
        while(line)
        {
            buff.clear();
            line >> buff;
            if(buff!="")
            {    
                fileContents.push_back(buff);
            }
        }
    }

    // Validate each component of saved file and assign them to local variables.
    try
    {
        // Get round #.
        m_tournamentRound = stoi(fileContents[1]);

        // Get computer score.
        m_computerScore = stoi(fileContents[4]);

        // Get computer color.
        if(fileContents[6] == "Black")
        {
            m_computerColorFromFile = 'B';
        }
        else if(fileContents[6] == "White")
        {
            m_computerColorFromFile = 'W';
        }
        
        // Get Human score.
        m_humanScore = stoi(fileContents[9]);

        // Get Human color.
        if(fileContents[11] == "Black")
        {
            m_humanColorFromFile = 'B';
        }
        else if(fileContents[11] == "White")
        {
            m_humanColorFromFile = 'W';
        }

        // Get Board state.
        std::vector<std::string>::iterator first = find(fileContents.begin(),fileContents.end(),"Board:")+1;
        std::vector<std::string>::iterator last = find(fileContents.begin(),fileContents.end(),"Next");
        
        // Get Board size.
        m_boardSizeFromFile = std::sqrt(std::distance(first,last));

        // Initialize rows.
        std::vector <char> rows (m_boardSizeFromFile,'+');

        // Create vector to hold rows of board.
        m_boardTableFromFile = new std::vector < std::vector<char> > (m_boardSizeFromFile,rows);

        int startIndex = std::distance(fileContents.begin(),first);

        // For each item in the file, load it into the vector.
        for(int i = 0; i < m_boardSizeFromFile; i++)
        {
            for(int j = 0; j < m_boardSizeFromFile; j++)
            {
                if(fileContents[startIndex].c_str()[0] == 'O')
                {
                    (*m_boardTableFromFile)[i][j] = '+';
                }
                else
                {
                    if(fileContents[startIndex] == "W")
                    {
                        (*m_boardTableFromFile)[i][j] = 'W';
                    }
                    else if (fileContents[startIndex] == "B")
                    {
                        (*m_boardTableFromFile)[i][j] = 'B';
                    }
                    else if (fileContents[startIndex] == "WW")
                    {
                        (*m_boardTableFromFile)[i][j] = 'w';
                    }
                    else if (fileContents[startIndex] == "BB")
                    {
                        (*m_boardTableFromFile)[i][j] = 'b';
                    }
                    else
                    {
                        std::cout << "Error in file.." << std::endl;
                        exit(1);
                    }
                }
                startIndex++;
            }
        }

        //  Confirm board loaded correctly.
        if((*m_boardTableFromFile).size() != 5 && (*m_boardTableFromFile).size() != 7 && (*m_boardTableFromFile).size() != 9)
        {
            std::cout << "Error in file.." << std::endl;
            exit(1);
        }
            
        // Get next player.
        if(fileContents[40] == "Human")
        {
            m_nextPlayerFromFile = 'h';
        }
        else if(fileContents[40] == "Computer")
        {
            m_nextPlayerFromFile = 'c';
        }
    }
    catch (std::exception &e)
    {
        std::cout << "Invalid file format. Please check your file. " << std::endl;
        return false;
    }

    return true;
};

/* ********************************************************************* 
Function Name: showMenu 
Purpose: Calls the Game object to show the menu to the user.
Parameters: 
            none.
Return Value: none.
Local Variables: 
            none.
Algorithm: 
            1) Call showMenu() method in Game object.
Assistance Received: none 
********************************************************************* */
void
tournament::showMenu() const
{
    round -> showMenu();
};

/* ********************************************************************* 
Function Name: saveGame 
Purpose: Save contents of game to file. (serialization)
Parameters: 
            a_fileName, string passed by value. Holds the name of the file to save to.
Return Value: none.
Local Variables: 
            outFile, ofstream object holding file
            boardSize, unsigned short that has the size of the board
            boardTable, vector of vector char holding the state of the board.
Algorithm: 
            1) Open file.
            2) Using ofstream, write each piece of content to file.
            3) Call Game object to get board size and board state.
            4) Write the rest of the contents to file.
            5) close file.
Assistance Received: none 
********************************************************************* */
void
tournament::saveGame(std::string a_fileName) const
{
    // File to write to.
    std::ofstream outFile(a_fileName,std::ofstream::out);

    // Write to file.
    outFile << "Round: " << m_tournamentRound << "\n";
    outFile << "Computer:\n";
    outFile << "Score: " << round -> getComputerScore() << "\n";
    outFile << "Color: " << round -> getComputerColor() << "\n";
    outFile << "Human:\n";
    outFile << "Score: " << round -> getHumanScore() << "\n";
    outFile << "Color: " << round -> getHumanColor() << "\n";
    outFile << "Board:\n";

    // Get the board size and state.
    unsigned short boardSize = round -> getBoardSize();
    std::vector< std::vector <char> > boardTable = round ->getBoardState();
    
    // Write the state of the board to file.
    for( int row = 0; row < boardSize; row++ )
    {
        for( int col = 0; col < boardSize; col++ )
        {
            if(boardTable[row][col] == '+')
            {
                outFile << "O  ";
            }
            else if(boardTable[row][col] == 'W')
            {
                outFile << "W  ";
            }
            else if(boardTable[row][col] == 'B')
            {
                outFile << "B  ";
            }
            else if(boardTable[row][col] == 'w')
            {
                outFile << "WW  ";
            }
            else if(boardTable[row][col] == 'b')
            {
                outFile << "BB  ";
            }
        }

        outFile <<"\n";
    }
    
    outFile << "Next Player: " << round -> getNextPlayer();

    outFile.close();
};

/* ********************************************************************* 
Function Name: playGame 
Purpose: Calls the Game object to play turn.
Parameters: 
            none.
Return Value: none.
Local Variables: 
            none.
Algorithm: 
            1) Call Game object for playRound() method.
Assistance Received: none 
********************************************************************* */
void
tournament::playGame() const
{
    round -> playRound();
};

/* ********************************************************************* 
Function Name: helpGame 
Purpose: Calls the Game object to ask for help.
Parameters: 
            none.
Return Value: none.
Local Variables: 
            none.
Algorithm: 
            1) Call Game object for helpGame() method.
Assistance Received: none 
********************************************************************* */
void
tournament::helpGame() const
{
    round -> getHelp();
};

/* ********************************************************************* 
Function Name: newRound 
Purpose: Deletes old Game object and creates new one in order to start a new round.
Parameters: 
            winnerFromGame, char that represents the winner from the last game.
Return Value: none.
Local Variables: 
            none.
Algorithm: 
            1) Delete instantiation of Game object.
            2) Check if the winner from last game was undetermined, then create new  game object.
            3) Create new instantiation of Game Object that makes the first player the winner from last round.
Assistance Received: none 
********************************************************************* */
void
tournament::newRound(char winnerFromGame)
{
    delete round;
    // Winner from last game is inconclusive.
    if(winnerFromGame == ' ')
    {
        round = new game();
    }
    // Winner from last round is first player.
    else
    {
        round = new game(winnerFromGame);
    }
};

/* ********************************************************************* 
Function Name: showWinner 
Purpose: Outputs the winner of the game as well as each player score to console.
Parameters: 
            none.
Return Value: none.
Local Variables: 
            none.
Algorithm: 
            1) Output human player score.
            2) Output computer player score.
            3) If player scores are equal, then output that there is no clear winner.
            4) If human score greater than computer score, output that the human player is the winner.
            5) Else, output that the computer player is the winner. 
Assistance Received: none 
********************************************************************* */
void
tournament::showWinner() const
{
    std::cout << "==========" << std::endl;
    std::cout << "Round Scores: " << std::endl;
    std::cout << "Human: " << round -> getHumanScore() << std::endl;
    std::cout << "Computer: " << round -> getComputerScore() << std::endl;
    std::cout << "==========" << std::endl;
    std::cout << "Tournament Scores: " << std::endl;
    std::cout << "Human: " << m_humanScore << std::endl;
    std::cout << "Computer: " << m_computerScore << std::endl;
    std::cout << "==========" << std::endl;
    if(m_humanScore == m_computerScore)
    {
        std::cout << "There is no clear winner. It is a draw." << std::endl;
    }
    else if(m_humanScore > m_computerScore)
    {
        std::cout << "Human is the winner!" << std::endl;
    }
    else
    {
        std::cout << "Computer is the winner!" << std::endl;
    }
};

/* ********************************************************************* 
Function Name: calculateScores 
Purpose: Add the total points from the round to the existing tournament scores.
Parameters: 
            none.
Return Value: none.
Local Variables: 
            none.
Algorithm: 
            1) Call Game object's calculateScores() method to add up points from the round.
            2) Call Game object to get human score and add it to existing human tournament score.
            3) Call Game object to get computer score and add it to existing computer tournament score.
Assistance Received: none 
********************************************************************* */
void
tournament::calculateScores()
{
    round ->calculateScore();
    if(round -> getHumanScore() > round -> getComputerScore())
    {
        // Awarded difference.
        m_humanScore += ( round -> getHumanScore() - round -> getComputerScore());
        std::cout << "Awarding you " << round -> getHumanScore() - round -> getComputerScore() << " points!" <<std::endl;
    }
    else if (round -> getComputerScore() > round -> getHumanScore())
    {
        m_computerScore += (round -> getComputerScore() - round -> getHumanScore());
        std::cout << "Awarding computer " << round -> getComputerScore() - round -> getHumanScore() << " points!" << std::endl;
    }
    else
    {   
        std::cout << "No points awarded." << std::endl;    
    }
};

/* ********************************************************************* 
Function Name: isGameWon 
Purpose: Checks if the game is won by calling Game object's isHomeSideCaptured() method. That method checks to see if pieces occupy opponent side.
Parameters: 
            none.
Return Value: boolean value that confirms if the round is complete.
Local Variables: 
            none.
Algorithm: 
            1) Call isHomeSideCapture() method in Game object to check if pieces occupy opponent side.
            2) Call Game object to get computer score and add it to existing computer tournament score.
            3) Return boolean value.
Assistance Received: none 
********************************************************************* */
bool
tournament::isGameWon()
{
    return (round -> isHomeSideCapture()) ? true : false;
};

/* ********************************************************************* 
Function Name: quitGamePenalty 
Purpose: Deducts 5 points from player for quiting game.
Parameters: 
            none.
Return Value: none.
Local Variables: 
            none.
Algorithm: 
            1) Notify user.
            2) Subtract 5 from human score.
Assistance Received: none 
********************************************************************* */
void
tournament::quitGamePenalty() 
{
    std::cout << "Deducting 5 points from tournament score for quiting game." << std::endl;
    m_humanScore-=5;
};

/* ********************************************************************* 
Function Name: getWinner 
Purpose: Deducts Returns the winner of the round.
Parameters: 
            none.
Return Value: char holding either 'h' for human or 'c' for computer.
Local Variables: 
            none.
Algorithm: 
            1) Check the scores from the previous round.
Assistance Received: none 
********************************************************************* */
char
tournament::getWinner() const
{
    if(round -> getHumanScore() == round -> getComputerScore())
    {
        return ' ';
    }
    else if(round -> getHumanScore() > round -> getComputerScore())
    {
        return 'h';
    }
    else
    {
        return 'c';
    }
};