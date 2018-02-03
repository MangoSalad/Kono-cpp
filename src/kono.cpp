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

    // Seed random number for dice throwing.
    srand (time(NULL));

    // Variables for user input.
    char choice = ' ';
    std::string fileName = "";
    int menuChoice = 0;

    // Give user choice to load game from file or create a new game.
    while(choice != 'y' && choice != 'n')
    {
        std::cout << "Do you want to start a game from a previously saved state? (y/n) ";
        std::cin >> choice;

        // Start game from existing save file.
        if(choice == 'y')
        {
            std::cout << "Enter the name of the saved file: ";
            std::cin >> fileName;
            Kono = new tournament(fileName);
        }

        // Start new game.
        else if(choice == 'n')
        {
            Kono = new tournament;
        }
        // Incorrect option handling.
        else
        {
            std::cout << "You chose an incorrect option. Please try again." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }    
    }

    // Show menu options until player decides to exit game.
    while(menuChoice!=4)
    {
        Kono->showMenu();
        std::cin >> menuChoice;

        switch(menuChoice)
        {
            // Save game.
            case 1:
                std::cout << "Please enter your desired filename: ";
                std::cin >> fileName;
                Kono -> saveGame(fileName);
                // Exit upon serialization.
                delete Kono;
                return EXIT_SUCCESS;

            // Play game.
            case 2:
                Kono -> playGame();
                break;
            
            // Enter help mode. Menu only shows this option when turn is human's.
            case 3:
                Kono -> helpGame();
                break;

            // Exits game.
            case 4:
                delete Kono;
                return EXIT_SUCCESS;

            // Incorrect choice.
            default:
                std::cout << "Incorrect choice" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
    }

    delete Kono;
    return EXIT_SUCCESS;
}