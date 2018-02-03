#include "game.h"
#include "stdafx.h"

// Logic to start a round.
game::game()
{
    m_humanScore = 0;
    m_computerScore = 0;

    m_gameBoardSize = 0;

    // Set Board.
    setBoardSize();
    gameBoard = new board(m_gameBoardSize);

    // Display Display Board.
    display = new boardView();

    // Set Player.
    calculateFirstPlayer();
    setFirstPlayerColor();

    // Set Players.
    humanPlayer = new human(m_colorHumanPlayer);
    computerPlayer = new computer(m_colorComputerPlayer);
};

// Loads game from file.
game::game(char a_colorHumanPlayer, char a_colorComputerPlayer, char a_currentTurn,unsigned short a_boardSize, std::vector< std::vector <char> > &boardTable)
{

    m_humanScore = 0;
    m_computerScore = 0;

    m_gameBoardSize = a_boardSize;

    // Set Board.
    gameBoard = new board(m_gameBoardSize, boardTable);

    // Set Display Board.
    display = new boardView();

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
    
    m_currentTurn = a_currentTurn;
    if(m_currentTurn == 'h')
    {
        std::cout << "It is your turn." << std::endl;
    }
    else
    {
        std::cout << "It is the computer's turn." << std::endl;
    }

    humanPlayer = new human(m_colorHumanPlayer);
    computerPlayer = new computer(m_colorComputerPlayer);
}

game::~game()
{
    delete gameBoard;
    delete humanPlayer;
    delete computerPlayer;
    delete display;
}

void game::setFirstPlayerColor()
{

    // human chooses color
    if(m_currentTurn == 'h')
    {
        std::string choice = "";
        while(choice != "black" && choice != "white")
        {
            std::cout << "What color do you pick to play? (white/black): ";
            std::cin >> choice;
            
            if(choice == "black")
            {
                m_colorHumanPlayer = 'B';
                m_colorComputerPlayer = 'W';
                std::cout << "You will play as black." << std::endl;
            }
            else if(choice == "white")
            {
                m_colorHumanPlayer = 'W';
                m_colorComputerPlayer = 'B';
                std::cout << "You will play as white." << std::endl;
            }
            else
            {
                std::cout << "Incorrect choice." << std::endl;
            }
        }
    }
    // Computer randomly chooses color.
    else
    {
        bool randomChoice = rand() % 2;
        if(randomChoice)
        {
            std::cout << "Computer chose black. You will play as white." << std::endl;
            m_colorHumanPlayer = 'W';
            m_colorComputerPlayer = 'B';
        }
        else
        {
            std::cout << "Computer chose white. You will play as black." << std::endl;
            m_colorHumanPlayer = 'B';
            m_colorComputerPlayer = 'W';
        }
    }

}

// Calculates the first player by calling random dice.
void game::calculateFirstPlayer()
{
    std::ifstream diceFile("dice.txt");

    // If Dice file is not in the project folder space, then generate dice randomly.
    int humanDice = 0;
    int computerDice = 1;

    if (!diceFile)
    {
        while(humanDice != computerDice)
        {

            humanDice = randomDice();
            computerDice = randomDice();

            std::cout << "Computer rolls a pair of dice... " << computerDice << std::endl;
            std::cout << "Human rolls a pair of dice... " << humanDice << std::endl;

            if(humanDice > computerDice)
            {
                std::cout << "Human is first player." << std::endl; 
                m_currentTurn = 'h';
                break;
            }
            else if (humanDice < computerDice)
            {
                std::cout << "Computer is first player." << std::endl; 
                m_currentTurn = 'c';
                break;
            }
        
        };
    }

    // Read dice file.
    else
    {
        std::string buff;
        std::stack<std::string> fileContents;
        while(!diceFile.eof())
        {
            getline(diceFile, buff);
            std::istringstream line(buff);
            while(line)
            {
                buff.clear();
                line >> buff;
                if(buff!="")
                {   
                    std::cout << buff;
                    fileContents.push(buff);
                }
            }
            if(fileContents.size()==4)
            {
                humanDice = stoi(fileContents.top());
                fileContents.pop();
                humanDice += stoi(fileContents.top());
                fileContents.pop();
                computerDice = stoi(fileContents.top());
                fileContents.pop();
                computerDice += stoi(fileContents.top());

                std::cout << "Computer rolls a pair of dice... " << computerDice << std::endl;
                std::cout << "Human rolls a pair of dice... " << humanDice << std::endl;

                if(humanDice > computerDice)
                {
                    std::cout << "Human is first player." << std::endl; 
                    m_currentTurn = 'h';
                    break;
                }
                else if (humanDice < computerDice)
                {
                    std::cout << "Computer is first player." << std::endl; 
                    m_currentTurn = 'c';
                    break;
                }
                else
                {
                    std::cout << "Rolling again." <<std::endl;
                }
            }
        }

        if(humanDice == computerDice)
        {
            std::cout<<"Dice file provides poor results. Exiting game."<<std::endl;
            exit(1);
        }

    }
}

// Shows the available menu.
void game::showMenu() const
{ 
    display->showBoard(gameBoard -> getBoard());

    std::cout << "1. Save the game. " << std::endl;
    std::cout << "2. Make a move. " << std::endl;
    if(m_currentTurn=='h')
    {
        std::cout << "3. Ask for help. " << std::endl;   
    }
    std::cout << "4. Quit the game. " << std::endl;
}

// Returns number between 2 and 12.
int game::randomDice()
{
    return rand() % 12 + 2;
}

// Sets the board size for the round
void game::setBoardSize()
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

void game::playRound()
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

void game::getHelp()
{
    //Which piece to play
    //The direction in which to play it (northwest, northeast...)
    //Why: To advance (toward which home point); to retreat; to block (which piece); or to capture (which piece). 
}

void game::calculateScore()
{
    std::vector <std::vector <char> > board = gameBoard -> getBoard();

    // Calculate Score if player is White
    if(m_colorHumanPlayer == 'W')
    {
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

bool game::isHomeSideCapture()
{
    std::cout << "in isHomeSideCapture()\n";
    // Check if black pieces occupy white spaces.
    std::vector <char> blackSide = gameBoard -> getBlackSide();
    // Get all remaining black pieces.
    int numberOfBlack = gameBoard -> getNumberOfBlackPieces();

    // Check if white pieces occupy black spaces;
    std::vector <char> whiteSide = gameBoard -> getWhiteSide();
    // Get all remaining black pieces.
    int numberOfWhite = gameBoard -> getNumberOfWhitePieces();

    std::cout << "Black: ";
    for(int i = 0; i < blackSide.size(); i++)
    {
        std::cout<<blackSide[i] <<" ";
        if(blackSide[i]=='W' || blackSide[i]=='w')
        {
            numberOfWhite--;
        }
    }

    std::cout << "\nWhite: ";
    for(int i = 0; i < whiteSide.size(); i++)
    {
        std::cout<<whiteSide[i] <<" ";
        if(whiteSide[i]=='B' || whiteSide[i]=='b')
        {
            numberOfBlack--;
        }
    }

    std::cout <<"B: "<<numberOfBlack << " W: " << numberOfWhite << std::endl;

    if(numberOfWhite == 0 || numberOfBlack == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}