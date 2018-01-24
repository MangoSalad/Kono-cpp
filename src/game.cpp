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

    // Set Computer.

    // Initiate Game Logic.
};

bool game::calculateFirstPlayer()
{
    int humanDice = randomDice();
    int computerDice = randomDice();

    std::cout << "Computer rolls a pair of dice... " << computerDice << std::endl;
    std::cout << "Human rolls a pair of dice... " << humanDice << std::endl;

    return (humanDice > computerDice) ? true : false;
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

        if(choice > 5 && choice < 5)
            return choice;
        else
            std::cout << "Incorrect choice. " << std::endl;
    }
}

// Returns number between 2 and 12.
unsigned short game::randomDice()
{
    int dice = 0;
    srand (time(NULL));

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