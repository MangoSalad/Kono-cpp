#ifndef COMPUTER_H
#define COMPUTER_H

#include "player.h"
#include "board.h"

class computer: public player
{
 public:
  computer();
  virtual void play( board & gameboard );
  virtual unsigned short getLocation( board & gameboard );

 protected:

 private:


};

#endif