#include "tournament.h"
#include "stdafx.h"

tournament::tournament()
{
    tournamentRound = 0;
    round = new game();
}

bool tournament::continueGame()
{
    std::string choice = "";
    while(choice != "Yes" || choice != "No")
    {
        std::cout << "Do you want to play another round? (Yes/No)";
        std::cin >> choice;

        if(choice == "Yes")
            return true;

        else if(choice == "No")
            return false;
        
        else
            continue;
    }    
}