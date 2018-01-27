#include "stdafx.h"
#include "computer.h"
#include "board.h"

computer::computer(char a_color)
{
    m_color = a_color;
};

void computer::play(board &gameBoard)
{
    // If opponent piece is close to home, play defensively.

    // Else, play offensively and aim for center end of opponent's home. 

};