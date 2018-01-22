#include "board.h"
#include <iostream>

using namespace std;

board:: board( unsigned short inSize )
{
  // Save size locally 
  size = inSize;

  // Initialize the entire table to false
  table = new bool*[size];
  for( int row = 0; row < size; row++ )
  {
    // Allocate to the row
    table[row] = new bool[size];

    for( int col = 0; col < size; col++ )
      table[row][col] = false;
  }

  // Initialize filledCount
  filledCount = 0;
}

/*
  If location already occupied, return -1
  Else
     Set location to true
     Return the number of 8-neighbors already true
*/
short board::place( unsigned short location )
{
  // Subtract 1 since array subscripts start at 0
  location--;

  // Computer row and column
  unsigned short row = location / size;
  unsigned short col = location % size;

  // If the location is already occupied, return -1
  if( table[row][col] == true )
    return -1;

  // Otherwise, set the location to true
  table[row][col] = true;

  // Update filledCount
  filledCount++;

  // Count the number of true neighbors
  unsigned short neighbors = 0;

  // Top neighbor
  if( row > 0 && table[row - 1][col] )
    neighbors++;

  // left neighbor
  if( col > 0 && table[row][col - 1] )
    neighbors++;

  // right neighbor
  if( col < size - 1 && table[row][col + 1] )
    neighbors++;

  // bottom neighbor
  if( row < size - 1 && table[row + 1][col] )
    neighbors++;

  // Top left neighbor 
  if( row > 0 && col > 0 && table[row - 1][col - 1] )
    neighbors++;

  // Top right neighbor
  if( row > 0 && col < size - 1 && table[row - 1][col + 1] )
    neighbors++;

  // Bottom left neighbor
  if( row < size - 1 && col > 0 && table[row + 1][col - 1] )
    neighbors++;

  // Nottom right neighbor
  if( row < size - 1 && col < size - 1 && table[row + 1][col + 1] )
    neighbors++;

  // Print the board
  print();

  // Return the number of neighbors
  return neighbors;
}

void board::print()
{
  drawLine( size );
  for( int row = 0; row < size; row++ )
  {
    for( int col = 0; col < size; col++ )
    {
      if( table[row][col] )
	cout << "|  1  ";
      else
	cout << "|     ";
    }
    cout << "| " << (row + 1) << endl;
  }
  drawLine( size );
}

void board::drawLine( unsigned short size )
{
  for( int count = 0; count < size; count++ )
    cout << "--" << (count + 1) << "---";
  cout << "-" << endl;
}