#include "stdafx.h"
#include "player.h"

player::player()
{
};

void player::play(std::vector< std::vector <char> > &boardTable)
{
    std::cout << "In player class - play()" << std::endl;

    unsigned short pieceToMove = 0;
    std::cout << "What piece do you want to move?" << std::endl;
    std::cin >> pieceToMove;

    unsigned short locationToMove = 0;
    std::cout << "Where do you want to move this piece to?" << std::endl;
    std::cin >> locationToMove;


    //when playing, must ask for piece to move. 
    //check if piece is valid to move
    //make move
    //check if move is valid
};

