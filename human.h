#ifndef HUMAN_H
#define HUMAN_H

#include "player.h"
#include "board.h"
#include <string>

using namespace std;

class human: public player
{
 public:
  human(string inName);
  virtual void play( board & gameboard );
  virtual unsigned short getLocation( board & gameboard );

 protected:

 private:


};

#endif