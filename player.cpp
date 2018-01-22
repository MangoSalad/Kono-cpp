#include "player.h"
#include "board.h"
#include <iostream>

using namespace std;

player:: player()
{
  // Initialize points
  points = 0;
}

void player::play( board & gameboard )
{

}


void player::play2( board & gameboard )
{
  cout << name << " PLAYING" << endl;

  // While the location has already been played, repeat
  int location, neighbors;
  do
  {
    // Ask user for a location
    location = getLocation( gameboard );

    // Set the location on the board 
    neighbors = gameboard.place( location );
  }while( -1 == neighbors );

  // Add neighbors to points
  points += neighbors;
  cout << name << " EARNED " << neighbors << " points and now has a score of " << points << endl;
}
