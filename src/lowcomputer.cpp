#include "lowcomputer.h"
#include "board.h"

#include <iostream>
#include <cstdlib>

using namespace std;

lowcomputer::lowcomputer()
{
  name = "LowComputer";

  // Initialize to first location on the board
  nextLocation = 1;
}


// Plays randomly
void lowcomputer::play( board & gameboard )
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

  cout << "Lowcomputer played location " << location << endl;

  // Add neighbors to points
  points += neighbors;
  cout << name << " earned " << neighbors << " points and now has a score of " << points << endl;
}


// Plays randomly
unsigned short lowcomputer::getLocation( board & gameboard )
{
  // Get the size of the board
  int location = nextLocation;
  int size = gameboard.getSize();

  // Update for next call
  nextLocation++;
  if( nextLocation > size * size )
    nextLocation = 1;

  return location;
}