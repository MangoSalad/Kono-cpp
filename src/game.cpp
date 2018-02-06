#include "game.h"
#include "stdafx.h"

// Default constructor to start a new round.
game::game()
{
    // Initialize variables.
    m_humanScore = 0;
    m_computerScore = 0;
    m_gameBoardSize = 0;

    // Set Board.
    setBoardSize();
    gameBoard = new board(m_gameBoardSize);

    // Board View.
    display = new boardView();

    // Set logic for first player.
    calculateFirstPlayer();
    setFirstPlayerColor();

    // Instantiate Players.
    humanPlayer = new human(m_colorHumanPlayer);
    computerPlayer = new computer(m_colorComputerPlayer);
};

// Constructor for when winner from last round is first player this round.
game::game(char winnerFromLastGame)
{
    // Initialize variables.
    m_humanScore = 0;
    m_computerScore = 0;
    m_gameBoardSize = 0;

    // Set Board.
    setBoardSize();
    gameBoard = new board(m_gameBoardSize);

    // Board View.
    display = new boardView();

    // Set logic for first player.
    m_currentTurn = winnerFromLastGame;
    setFirstPlayerColor();

    // Instantiate Players.
    humanPlayer = new human(m_colorHumanPlayer);
    computerPlayer = new computer(m_colorComputerPlayer);

}

// Constructor to load an existing round from file.
game::game(char a_colorHumanPlayer, char a_colorComputerPlayer, char a_currentTurn,unsigned short a_boardSize, std::vector< std::vector <char> > &boardTable)
{
    // Initialize round score to zero.
    m_humanScore = 0;
    m_computerScore = 0;

    // Set Board.
    m_gameBoardSize = a_boardSize;
    gameBoard = new board(m_gameBoardSize, boardTable);

    // Board View.
    display = new boardView();

    // Colors of players.
    m_colorHumanPlayer = a_colorHumanPlayer;
    m_colorComputerPlayer = a_colorComputerPlayer;

    if(m_colorHumanPlayer == 'W')
    {
        std::cout << "You are playing white. Computer is playing black." << std::endl;
    }
    else
    {
        std::cout << "You are playing black. Computer is playing white." << std::endl;
    }
    
    // Current turn.
    m_currentTurn = a_currentTurn;
    
    // Instantiate Players.
    humanPlayer = new human(m_colorHumanPlayer);
    computerPlayer = new computer(m_colorComputerPlayer);
};

// Destructor , free up resources.
game::~game()
{
    delete gameBoard;
    delete humanPlayer;
    delete computerPlayer;
    delete display;
};

/* ********************************************************************* 
Function Name: setFirstPlayerColor 
Purpose: Asks the user for what color they will play. If first player is computer, computer will randomly pick the color.
Parameters: 
            none.
Return Value: none.
Local Variables: 
            choice, char holding the choice for what color the human will pick.
            randonChoice, a boolean for what color the computer iwll pick.
Algorithm: 
            1) If the current turn is the human, ask the human what color they will play as. Record this color into variable.
            2) If the current turn is the computer, computer will randomly pick the color and record it into a variable.
Assistance Received: none 
********************************************************************* */
void
game::setFirstPlayerColor()
{

    // First player is human, he/she chooses color.
    if(m_currentTurn == 'h')
    {
        char choice = ' ';

        // Ask user for choice.
        while(choice != 'b' && choice != 'w')
        {
            std::cout << "What color do you pick to play? (w/b): ";
            std::cin >> choice;
            
            // Assign human color to black.
            if(choice == 'b')
            {
                m_colorHumanPlayer = 'B';
                m_colorComputerPlayer = 'W';
                std::cout << "You will play as black." << std::endl;
            }

            // Assign human color to white.
            else if(choice == 'w')
            {
                m_colorHumanPlayer = 'W';
                m_colorComputerPlayer = 'B';
                std::cout << "You will play as white." << std::endl;
            }

            // Handle incorrect input.
            else
            {
                std::cout << "You chose an incorrect option. Please try again." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            }
        }
    }

    // Computer randomly chooses color.
    else
    {
        // Either 1 or 0.
        bool randomChoice = rand() % 2;

        // If 1, then computer will choice black.
        if(randomChoice)
        {
            std::cout << "Computer chose black. You will play as white." << std::endl;
            m_colorHumanPlayer = 'W';
            m_colorComputerPlayer = 'B';
        }
        
        // Else it will choose white.
        else
        {
            std::cout << "Computer chose white. You will play as black." << std::endl;
            m_colorHumanPlayer = 'B';
            m_colorComputerPlayer = 'W';
        }
    }
};

/* ********************************************************************* 
Function Name: calculateFirstPlayer 
Purpose: Calculates the first player of the game either by random dice roll or by loading a dice file with preconfigured dice rolls.
Parameters: 
            none.
Return Value: none.
Local Variables: 
            diceFile, ifstream object. Used to open dice file if it exists.
            humanDice, an integer. Holds result of random dice toss for human.
            computerDice, an integer. Holds result of random dice toss for computer.
            buff, a string. Holds buffer from reading dice file.
            fileContents, a string stack. Holds contents from the dice file.
            line, an istringstream object. Used to parse the dice file.
Algorithm: 
            1) If there is a dice.txt file. Skip to step 5.
            2) If there is no dice.txt file, then call randomDice() method for human and computer to generate random dice rolls.
            3) If a dice pair is greater than the other, then the owner of the random dice pair is the first player.
            4) If both pairs are equal, then reroll.
            5) Open dice.txt and parse each line using istringstream.
            6) Load each number from file onto stack.
            7) If stack is size 4, then 2 numbers will be human rolls and 2 will be computer rolls.
            8) Depending which roll is greater, they will go first.
            9) If both are equal, then continue to read file for greater pairs.
            10) If file cannot provide a greater pair for dice roll, then exit game and inform user.

Assistance Received: none 
********************************************************************* */
void
game::calculateFirstPlayer()
{
    std::ifstream diceFile("dice.txt");

    // If Dice file is not in the project folder space, then generate dice randomly.
    int humanDice = 0;
    int computerDice = 1;

    if (diceFile.fail())
    {
        // Toss doss until one pair is greater than the other.
        while(humanDice != computerDice)
        {
            // Get random dice pairs.
            humanDice = randomDice();
            computerDice = randomDice();

            // Announce dice rolls.
            std::cout << "Computer rolls a pair of dice... " << computerDice << std::endl;
            std::cout << "Human rolls a pair of dice... " << humanDice << std::endl;

            // Human player won the dice roll. Human player is first.
            if(humanDice > computerDice)
            {
                std::cout << "Human is first player." << std::endl; 
                m_currentTurn = 'h';
                break;
            }

            // Computer player won the dice roll. Computer player is first.
            else if (humanDice < computerDice)
            {
                std::cout << "Computer is first player." << std::endl; 
                m_currentTurn = 'c';
                break;
            }

            // Annouce to player that dice will roll again.
            else
            {
                std::cout << "Rolling again.." << std::endl;
            }
        };
    }

    // Read dice file.
    else
    {
        // Buffer for lines from file.
        std::string buff;

        // Stack for holding lines from file.s
        std::stack<std::string> fileContents;

        // While the file is not empty, read each line.
        while(!diceFile.eof())
        {
            getline(diceFile, buff);
            std::istringstream line(buff);

            // For each line, push it onto the stack.
            while(line)
            {
                buff.clear();
                line >> buff;
                if(buff!="")
                {   
                    fileContents.push(buff);
                }
            };

            // If there are enough dice rolls on the stack, read them.
            if(fileContents.size()==4)
            {
                // Human roll #1
                humanDice = stoi(fileContents.top());
                fileContents.pop();

                // Human roll #2
                humanDice += stoi(fileContents.top());
                fileContents.pop();

                // Computer roll #1
                computerDice = stoi(fileContents.top());
                fileContents.pop();

                // Computer roll #2
                computerDice += stoi(fileContents.top());

                // Announce rolls to user.
                std::cout << "Computer rolls a pair of dice... " << computerDice << std::endl;
                std::cout << "Human rolls a pair of dice... " << humanDice << std::endl;

                // Announce human is first player.
                if(humanDice > computerDice)
                {
                    std::cout << "Human is first player." << std::endl; 
                    m_currentTurn = 'h';
                    break;
                }

                // Announce computer is first player.
                else if (humanDice < computerDice)
                {
                    std::cout << "Computer is first player." << std::endl; 
                    m_currentTurn = 'c';
                    break;
                }

                // Announce that the results are inconclusive.
                else
                {
                    std::cout << "Rolling again." <<std::endl;
                }
            }
        };
    };

    // If all the tosses were equal. The provided file cannot be used. Exit the game.
    if(humanDice == computerDice)
    {
        std::cout<<"Dice file provides poor results. Exiting game."<<std::endl;
        exit(1);
    };
};

/* ********************************************************************* 
Function Name: showMenu 
Purpose: Shows menu to user playing.
Parameters: 
            none.
Return Value: none.
Local Variables: 
            none.
Algorithm: 
            1) Display the board by calling showBoard() method in boardview object.
            2) If the current turn is human, then provide option to ask for help.
Assistance Received: none 
********************************************************************* */
void
game::showMenu() const
{
    if(m_currentTurn == 'h')
    {
        std::cout<<"It is your turn." << std::endl;
    }
    else
    {
        std::cout << "It is the computer's turn." << std::endl;
    }
    // Display the board. 
    display->showBoard(gameBoard -> getBoard());

    // Show menu options.
    std::cout << "1. Save the game. " << std::endl;
    std::cout << "2. Make a move. " << std::endl;

    // If current turn is human, provide option to ask for help.
    if(m_currentTurn=='h')
    {
        std::cout << "3. Ask for help. " << std::endl;   
    }

    std::cout << "4. Quit the game. " << std::endl;
}

/* ********************************************************************* 
Function Name: randomDice 
Purpose: Generates a random number between 2 and 12 to simulate dice roll.
Parameters: 
            none.
Return Value: integer between 2 and 12.
Local Variables: 
            none.
Algorithm: 
            1) Call rand() to generate random number between 2 and 12.
Assistance Received: none 
********************************************************************* */
int
game::randomDice()
{
    return rand() % 11 + 2;
}

/* ********************************************************************* 
Function Name: setBoardSize 
Purpose: Asks user for the board size and sets it accordingly.
Parameters: 
            none.
Return Value: none.
Local Variables: 
            none.
Algorithm: 
            1) Ask user for their board size choice (5,7,9)
            2) Validate input.
            3) Set the board size to their input.
Assistance Received: none 
********************************************************************* */
void
game::setBoardSize()
{
    int choice;
    do 
    {
        std::cout << "Please enter your game board size (5,7,9): ";
        std::cin >> choice;

        if(choice == 5 || choice == 7 || choice == 9)
        {
            m_gameBoardSize = choice;
        }
        else
        {
            std::cout << "Incorrect choice. Try again." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }    
    }while(choice != 5 && choice != 7 && choice != 9);
};

/* ********************************************************************* 
Function Name: playRound 
Purpose: Calls the play() method for either human or computer depending on the current turn.
Parameters: 
            none.
Return Value: none.
Local Variables: 
            none.
Algorithm: 
            1) If current turn is human, human will play.
            2) Else, computer will play.
Assistance Received: none 
********************************************************************* */
void
game::playRound()
{
    if(m_currentTurn == 'h')
    {
        humanPlayer -> play(*gameBoard);
        m_currentTurn = 'c';
    }
    else
    {
        computerPlayer -> play(*gameBoard);
        m_currentTurn = 'h';
    }
}

/* ********************************************************************* 
Function Name: getHelp 
Purpose: Calls help() method in player class in order to provide help to the human.
Parameters: 
            none.
Return Value: none.
Local Variables: 
            none.
Algorithm: 
            1) Call help() method.
Assistance Received: none 
********************************************************************* */
void
game::getHelp()
{
    humanPlayer -> help(*gameBoard, m_colorHumanPlayer,m_colorComputerPlayer);
}

void game::calculateScore()
{
    std::vector <std::vector <char> > board = gameBoard -> getBoard();

    // # of pieces each player starts with.
    int numberOfPieces = gameBoard -> getBoardSize() + 2;

    // Get the total number of black pieces.
    int numberOfBlack = gameBoard -> getNumberOfBlackPieces();

    // Get the total number of white pieces.
    int numberOfWhite = gameBoard -> getNumberOfWhitePieces();




    // Make everything uppercase.
    for( int i = 0; i < gameBoard -> getBoardSize(); i++ )
    {
        for( int j = 0; j < gameBoard -> getBoardSize(); j++ )
        {
            if(board[i][j] =='w')
            {
                board[i][j] = 'W';
            }
            else if(board[i][j] == 'b')
            {
                board[i][j] = 'B';
            }
        }
    }

    // Calculate Score if player is White
    if(m_colorHumanPlayer == 'W')
    {
        // Deduct capture pieces.
        m_humanScore +=  (numberOfPieces - numberOfBlack) * 5;

        //calculate human score
        if(board[m_gameBoardSize-1][0] == m_colorHumanPlayer)
        {
            m_humanScore+=3;
        }
        if(board[m_gameBoardSize-1][1] == m_colorHumanPlayer)
        {
            m_humanScore+=1;
        }
        if(board[m_gameBoardSize-1][2] == m_colorHumanPlayer)
        {
            m_humanScore+=5;
        }
        //board is 7x7
        if(m_gameBoardSize == 7)
        {
            if(board[m_gameBoardSize-1][3] == m_colorHumanPlayer)
            {
                m_humanScore+=7;
            }
            if(board[m_gameBoardSize-1][4] == m_colorHumanPlayer)
            {
                m_humanScore+=5;
            }
            
        }
        // board is 9x9
        if(m_gameBoardSize == 9)
        {
            if(board[m_gameBoardSize-1][3] == m_colorHumanPlayer)
            {
                m_humanScore+=7;
            }
            if(board[m_gameBoardSize-1][4] == m_colorHumanPlayer)
            {
                m_humanScore+=9;
            }
            if(board[m_gameBoardSize-1][5] == m_colorHumanPlayer)
            {
                m_humanScore+=7;
            }
            if(board[m_gameBoardSize-1][6] == m_colorHumanPlayer)
            {
                m_humanScore+=5;
            }
        }

        if(board[m_gameBoardSize-1][m_gameBoardSize-2] == m_colorHumanPlayer)
        {
            m_humanScore+=1;
        }
        if(board[m_gameBoardSize-1][m_gameBoardSize-1] == m_colorHumanPlayer)
        {
            m_humanScore+=3;
        }

        if(board[m_gameBoardSize-2][0] == m_colorHumanPlayer)
        {
            m_humanScore+=1;
        }
        if(board[m_gameBoardSize-2][m_gameBoardSize-1] == m_colorHumanPlayer)
        {
            m_humanScore+=1;
        }
    }


    if(m_colorComputerPlayer == 'W')
    {
        m_computerScore +=  (numberOfPieces - numberOfBlack) * 5;

        //calculate human score
        if(board[m_gameBoardSize-1][0] == m_colorComputerPlayer)
        {
            m_computerScore+=3;
        }
        if(board[m_gameBoardSize-1][1] == m_colorComputerPlayer)
        {
            m_computerScore+=1;
        }
        if(board[m_gameBoardSize-1][2] == m_colorComputerPlayer)
        {
            m_computerScore+=5;
        }
        //board is 7x7
        if(m_gameBoardSize == 7)
        {
            if(board[m_gameBoardSize-1][3] == m_colorComputerPlayer)
            {
                m_computerScore+=7;
            }
            if(board[m_gameBoardSize-1][4] == m_colorComputerPlayer)
            {
                m_computerScore+=5;
            }
            
        }
        // board is 9x9
        if(m_gameBoardSize == 9)
        {
            if(board[m_gameBoardSize-1][3] == m_colorComputerPlayer)
            {
                m_computerScore+=7;
            }
            if(board[m_gameBoardSize-1][4] == m_colorComputerPlayer)
            {
                m_computerScore+=9;
            }
            if(board[m_gameBoardSize-1][5] == m_colorComputerPlayer)
            {
                m_computerScore+=7;
            }
            if(board[m_gameBoardSize-1][6] == m_colorComputerPlayer)
            {
                m_computerScore+=5;
            }
        }

        if(board[m_gameBoardSize-1][m_gameBoardSize-2] == m_colorComputerPlayer)
        {
            m_computerScore+=1;
        }
        if(board[m_gameBoardSize-1][m_gameBoardSize-1] == m_colorComputerPlayer)
        {
            m_computerScore+=3;
        }

        if(board[m_gameBoardSize-2][0] == m_colorComputerPlayer)
        {
            m_computerScore+=1;
        }
        if(board[m_gameBoardSize-2][m_gameBoardSize-1] == m_colorComputerPlayer)
        {
            m_computerScore+=1;
        }
    }
    
    
    if(m_colorHumanPlayer == 'B')
    {
        m_humanScore +=  (numberOfPieces - numberOfWhite) * 5;

        //calculate human score
        if(board[0][0] == m_colorHumanPlayer)
        {
            m_humanScore+=3;
        }
        if(board[0][1] == m_colorHumanPlayer)
        {
            m_humanScore+=1;
        }
        if(board[0][2] == m_colorHumanPlayer)
        {
            m_humanScore+=5;
        }
        //board is 7x7
        if(m_gameBoardSize == 7)
        {
            if(board[0][3] == m_colorHumanPlayer)
            {
                m_humanScore+=7;
            }
            if(board[0][4] == m_colorHumanPlayer)
            {
                m_humanScore+=5;
            }
            
        }
        // board is 9x9
        if(m_gameBoardSize == 9)
        {
            if(board[0][3] == m_colorHumanPlayer)
            {
                m_humanScore+=7;
            }
            if(board[0][4] == m_colorHumanPlayer)
            {
                m_humanScore+=9;
            }
            if(board[0][5] == m_colorHumanPlayer)
            {
                m_humanScore+=7;
            }
            if(board[0][6] == m_colorHumanPlayer)
            {
                m_humanScore+=5;
            }
        }

        if(board[0][m_gameBoardSize-2] == m_colorHumanPlayer)
        {
            m_humanScore+=1;
        }
        if(board[0][m_gameBoardSize-1] == m_colorHumanPlayer)
        {
            m_humanScore+=3;
        }

        if(board[1][0] == m_colorHumanPlayer)
        {
            m_humanScore+=1;
        }
        if(board[1][m_gameBoardSize-1] == m_colorHumanPlayer)
        {
            m_humanScore+=1;
        }
    } 



    if(m_colorComputerPlayer == 'B')
    {
        m_computerScore +=  (numberOfPieces - numberOfWhite) * 5;

        //calculate human score
        if(board[0][0] == m_colorComputerPlayer)
        {
            m_computerScore+=3;
        }
        if(board[0][1] == m_colorComputerPlayer)
        {
            m_computerScore+=1;
        }
        if(board[0][2] == m_colorComputerPlayer)
        {
            m_computerScore+=5;
        }
        //board is 7x7
        if(m_gameBoardSize == 7)
        {
            if(board[0][3] == m_colorComputerPlayer)
            {
                m_computerScore+=7;
            }
            if(board[0][4] == m_colorComputerPlayer)
            {
                m_computerScore+=5;
            }
            
        }
        // board is 9x9
        if(m_gameBoardSize == 9)
        {
            if(board[0][3] == m_colorComputerPlayer)
            {
                m_computerScore+=7;
            }
            if(board[0][4] == m_colorComputerPlayer)
            {
                m_computerScore+=9;
            }
            if(board[0][5] == m_colorComputerPlayer)
            {
                m_computerScore+=7;
            }
            if(board[0][6] == m_colorComputerPlayer)
            {
                m_computerScore+=5;
            }
        }

        if(board[0][m_gameBoardSize-2] == m_colorComputerPlayer)
        {
            m_computerScore+=1;
        }
        if(board[0][m_gameBoardSize-1] == m_colorComputerPlayer)
        {
            m_computerScore+=3;
        }

        if(board[1][0] == m_colorComputerPlayer)
        {
            m_computerScore+=1;
        }
        if(board[1][m_gameBoardSize-1] == m_colorComputerPlayer)
        {
            m_computerScore+=1;
        }
    }
}

/* ********************************************************************* 
Function Name: isHomeSideCapture 
Purpose: Checks if the a side's pieces have captured the opponent's home spaces.
Parameters: 
            none.
Return Value: Boolean value confirming if a side has captured the other side's spaces.
Local Variables: 
            blackSide, char vector. Holds the black side.
            numberOfBlack, integer. The number of remaining black pieces.
            whiteSide, char vector. Holds the white side.
            numberOfWhite, integer. The number of remaining white pieces.
Algorithm: 
            1) Get a vector holding the pieces of the black side.
            2) Get a count of how many black pieces there are left.
            3) Get a vector holding the pieces of the white side.
            4) Get a count of how many white pieces there are left.
            5) Iterate through the black side vector and get a count of how many remaining white pieces have not captured the black side.
            6) Iterate through the white side vector and get a count of how many remaining black pieces have not captured the white side.
            7) If all the pieces of one side have captured the other side, return true. This means that this is a winning condition.
Assistance Received: none 
********************************************************************* */
bool
game::isHomeSideCapture()
{
    // Get a vector of the entire home space of the black side.
    std::vector <char> blackSide = gameBoard -> getBlackSide();
    
    // Get the total number of black pieces.
    int numberOfBlack = gameBoard -> getNumberOfBlackPieces();

    // Get a vector of the entire home space of the white side.
    std::vector <char> whiteSide = gameBoard -> getWhiteSide();

    // Get the total number of white pieces.
    int numberOfWhite = gameBoard -> getNumberOfWhitePieces();

    // Get a count of the remaining # of white pieces have occupied the black side.
    numberOfWhite -= count(blackSide.begin(),blackSide.end(),'W');
    numberOfWhite -= count(blackSide.begin(),blackSide.end(),'w');

    // Get a count of the remaining # of black pieces have occupied the white side.
    numberOfBlack -= count(whiteSide.begin(),whiteSide.end(),'B');
    numberOfBlack -= count(whiteSide.begin(),whiteSide.end(),'b');

    // If either all white pieces are on the black side, or all black pieces are on the white side - then a home side has been captured.
    // This is a winning condition.
    if(numberOfWhite == 0 || numberOfBlack == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}