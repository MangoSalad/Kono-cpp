#include "stdafx.h"
#include "human.h"
#include "board.h"

human::human(std::string inName)
{
  name = inName;
}


void human::play( board & gameboard )
{
  // Get the size of the board
  int size = gameboard.getSize();
  size *= size;

  std::cout << name << " playing" << std::endl;

  // While the location has already been played, repeat
  int location, neighbors;
  do
  {
    // Ask user for a location
    do
    {
      std::cout << name << ", please enter a location: 1 - " << size << std::endl;
      cin >> location;
    }while( location < 1 || location > size );

    // Set the location on the board 
    neighbors = gameboard.place( location );
  }while( -1 == neighbors );

  // Add neighbors to points
  points += neighbors;
  std::cout << name << " earned " << neighbors << " points and now has a score of " << points << std::endl;
}



unsigned short human::getLocation( board & gameboard )
{
  // Get the size of the board
  int location;
  int size = gameboard.getSize();
  size *= size;

  // Ask user for a location
  do
  {
    std::cout << name << ", please enter a location: 1 - " << size << std::endl;
    std::cin >> location;
  }while( location < 1 || location > size );
  
  // Return location
  return location;
}