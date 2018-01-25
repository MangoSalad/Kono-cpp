#include "game.h"
#include "stdafx.h"

// Logic to start a round.
game::game()
{
    gameBoardSize = 0;

    // Set Board Size.
    setBoardSize();
    gameBoard = new board(gameBoardSize);

    // Display Board.
    display = new boardView();
    display->showBoard(gameBoard -> getBoard());

    // Set Player.
    calculateFirstPlayer();
    setFirstPlayerColor();

    // Set Computer.

    humanPlayer = new human();
    computerPlayer = new computer();
    

    // Initiate Game Logic.
    continueGame();
};


// Calls menu, and determines what to do after menu
void game::continueGame()
{   
    unsigned short choice = displayMenu();

    if(choice == 1)
    {
        std::cout << "Saving game..." << std::endl;
    }
    else if(choice == 2)
    {
        if(m_currentTurn=='h')
        {
            humanPlayer -> play();
        }
        else
        {
            computerPlayer -> play();
        }
    }
    else if(choice == 3)
    {
        std::cout << "Help: ..." << std::endl;
    }
    else if(choice == 4)
    {
        std::cout << "Exiting..." << std::endl;
    }
    else
    {
        std::cout << "Error with choice" << std::endl;
    }

};

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
                m_colorHumanPlayer = true;
                std::cout << "You will play as black." << std::endl;
            }
            else if(choice == "white")
            {
                m_colorHumanPlayer = false;
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
        bool m_colorHumanPlayer = rand() % 2;
        if(m_colorHumanPlayer)
        {
            std::cout << "Computer chose black. You will play as white." << std::endl;
        }
        else
        {
            std::cout << "Computer chose white. You will play as black." << std::endl;
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

unsigned short game::displayMenu()
{
    unsigned short choice;
    
    while(choice < 1 || choice > 4)
    {
        std::cout << "1. Save the game. " << std::endl;
        std::cout << "2. Make a move. " << std::endl;
        std::cout << "3. Ask for help. " << std::endl;
        std::cout << "4. Quit the game. " << std::endl;
        
        std::cin >> choice;

        if(choice > 0 && choice < 5)
            return choice;
        else
            std::cout << "Incorrect choice. " << std::endl;
    }
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
            gameBoardSize = choice;
        }
        else    
            std::cout << "Incorrect choice. Try again." << std::endl;

    }while(choice != 5 && choice != 7 && choice != 9);
};

unsigned short game::getBoardSize()
{
    return gameBoardSize;
};