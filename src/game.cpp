#include "game.h"
#include "stdafx.h"

// Logic to start a round.
game::game()
{
    m_gameBoardSize = 0;

    // Set Board.
    setBoardSize();
    gameBoard = new board(m_gameBoardSize);

    // Display Display Board.
    display = new boardView();
    //display->showBoard(gameBoard -> getBoard());

    // Set Player.
    calculateFirstPlayer();
    setFirstPlayerColor();

    // Set Players.
    humanPlayer = new human(m_colorHumanPlayer);
    computerPlayer = new computer();
    
    // Initiate Game Logic.
    //continueGame();
};

// Loads game from file.
game::game(char a_colorHumanPlayer, char a_colorComputerPlayer, char a_currentTurn,unsigned short a_boardSize, std::vector< std::vector <char> > &boardTable)
{
    m_colorHumanPlayer = a_colorHumanPlayer;
    m_colorComputerPlayer = a_colorComputerPlayer;
    m_currentTurn = a_currentTurn;

    // Set Board.
    m_gameBoardSize = a_boardSize;
    gameBoard = new board(m_gameBoardSize, boardTable);

    // Set Display Board.
    display = new boardView();
    //display->showBoard(gameBoard -> getBoard());
}

game::~game()
{
    delete gameBoard;
    delete humanPlayer;
    delete computerPlayer;
    delete display;
}

void game::setFirstPlayer(char a_firstPlayer)
{
    m_firstPlayer=a_firstPlayer;
}

void game::setFirstPlayerColor()
{

    // human chooses color
    if(m_firstPlayer == 'h')
    {
        std::string choice = "";
        while(choice != "black" && choice != "white")
        {
            std::cout << "What color do you pick to play? (white/black): ";
            std::cin >> choice;
            
            if(choice == "black")
            {
                m_colorHumanPlayer = 'W';
                m_colorComputerPlayer = 'B';
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


void game::calculateFirstPlayer()
{
    int humanDice = 0;
    int computerDice = 1;
    while(humanDice != computerDice)
    {

        humanDice = randomDice();
        computerDice = randomDice();

        std::cout << "Computer rolls a pair of dice... " << computerDice << std::endl;
        std::cout << "Human rolls a pair of dice... " << humanDice << std::endl;

        if(humanDice > computerDice)
        {
            std::cout << "Human is first player." << std::endl; 
            m_firstPlayer = 'h';
            break;
        }
        else if (humanDice < computerDice)
        {
            std::cout << "Computer is first player." << std::endl; 
            m_firstPlayer = 'c';
            break;
        }
    
    };
}

void game::showMenu() const
{ 
    std::cout << "1. Save the game. " << std::endl;
    if(m_currentTurn=='h')
    {
        std::cout << "2. Make a move. " << std::endl;
    }
    std::cout << "3. Ask for help. " << std::endl;
    std::cout << "4. Quit the game. " << std::endl;
}

// Returns number between 2 and 12.
unsigned short game::randomDice()
{
    int dice = 0;
    srand (time(0));

    dice = rand() % 12 + 2;

    return dice;
}

void game::setBoardSize()
{
    unsigned short choice;
    do 
    {
        std::cout << "Please enter your game board size (5,7,9): ";
        std::cin >> choice;

        if(choice == 5 || choice == 7 || choice == 9)
        {
            m_gameBoardSize = choice;
        }
        else    
            std::cout << "Incorrect choice. Try again." << std::endl;

    }while(choice != 5 && choice != 7 && choice != 9);
};

unsigned short game::getBoardSize()
{
    return m_gameBoardSize;
};