#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"
#include <string>

using namespace std;

class player
{
 public:
  player();
  virtual void play( board & gameboard );
  unsigned short getPoints() const { return points; }
  string getName() const { return name; }

  void play2( board & gameboard );
  virtual unsigned short getLocation( board & gameboard ) = 0;

 protected:
  unsigned short points;
  string name;

 private:

};

#endif