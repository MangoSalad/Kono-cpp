#include "computer.h"
#include "board.h"

#include <iostream>
#include <cstdlib>

using namespace std;

computer::computer()
{
  name = "Computer";
}


// Plays randomly
void computer::play( board & gameboard )
{
  // Get the size of the board
  int size = gameboard.getSize();

  // While the location has already been played, repeat
  int location, neighbors;
  do
  {
    // Compute a random number in 0 - size * size - 1
    location = rand() % (size * size) + 1;

    // Set the location on the board 
    neighbors = gameboard.place( location );
  }while( -1 == neighbors );

  cout << "Computer played location " << location << endl;

  // Add neighbors to points
  points += neighbors;
  cout << name << " earned " << neighbors << " points and now has a score of " << points << endl;
}


// Plays randomly
unsigned short computer::getLocation( board & gameboard )
{
  // Get the size of the board
  int location;
  int size = gameboard.getSize();

  // Compute a random number in 0 - size * size - 1
  location = rand() % (size * size) + 1;

  // Return location
  return location;
}