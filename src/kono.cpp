/************************************************************
* Name:  Philip Glazman                                    *
* Project:  Kono - C++ Implementation                      *
* Class:  CMPS 366 Organization of Programming Languages   *
* Date:  2/6/2018                                          *
************************************************************/
#include "stdafx.h"
#include "tournament.h"
#include "game.h"

//To compile the program from command-line: g++ tournament.cpp game.cpp board.cpp boardview.cpp computer.cpp player.cpp human.cpp kono.cpp -o kono

int main(int argc, char * argv [])
{
    tournament * Kono;

    srand (time(NULL));

    char choice = ' ';
    std::string fileName = "";

    while(choice != 'y' && choice != 'n')
    {
        // Asks user for option to continue game from a previously saved state.
        std::cout << "Do you want to start a game from a previously saved state? (y/n) ";
        std::cin >> choice;

        if(choice == 'y')
        {
            // Start game from existing save file.
            std::cout << "Enter the name of the saved file: ";
            std::cin >> fileName;
            Kono = new tournament(fileName);
        }
        else if(choice == 'n')
        {
            // Starts new game.
            Kono = new tournament;
        }
        else
        {
            std::cout << "You chose an incorrect option. Please try again." << std::endl;
        }    
    }

    int menuChoice = 0;
    while(menuChoice!=4)
    {
        Kono->showMenu();
        std::cin >> menuChoice;

        switch(menuChoice)
        {
            case 1:
                std::cout << "Please enter your desired filename: ";
                std::cin >> fileName;
                Kono -> saveGame(fileName);
                break;
            case 2:
                Kono -> playGame();
                break;
            case 3:
                Kono -> helpGame();
                break;
            case 4:
                std::cout << "Thanks for playing. Exiting game." << std::endl;
                delete Kono;
                return 1;
            default:
                std::cout << "Incorrect choice" << std::endl;
        }
    }

    delete Kono;
}