#ifndef LOWCOMPUTER_H
#define LOWCOMPUTER_H

#include "computer.h"
#include "board.h"

class lowcomputer: public computer
{
 public:
  lowcomputer();
  virtual void play( board & gameboard );
  virtual unsigned short getLocation( board & gameboard );

 protected:
  short nextLocation;

 private:


};

#endif