#include "stdafx.h"
#include "tournament.h"
#include "game.h"

//g++ tournament.cpp game.cpp board.cpp boardview.cpp computer.cpp player.cpp human.cpp kono.cpp -o kono

int main(int argc, char * argv [])
{
    // Asks user for option to continue game from a previously saved state.
    char choice = ' ';
    std::string fileName;

    while(choice != 'y' && choice != 'n')
    {
        std::cout << "Do you want to start a game from a previously saved state? (y/n) ";
        std::cin >> choice;

        if(choice == 'y')
        {
            // Start game from existing save file.
            std::cout << "Enter the name of the saved file: ";
            std::cin >> fileName;
            tournament Kono(fileName);
        }
        else if(choice == 'n')
        {
            // Starts new game.
            tournament Kono;
        }
        else
        {
            std::cout << "You chose an incorrect option. Please try again." << std::endl;
        }    
    }
}