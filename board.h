#ifndef BOARD_H
#define BOARD_H

class board
{
 public:
  board( unsigned short inSize );
  short place( unsigned short location );
  void print();
  unsigned short getSize() const { return size; }
  bool filled() const { return filledCount == size * size; }

 protected:

 private:
  unsigned short size;
  bool **table;
  unsigned short filledCount;

  // utility function
  void drawLine( unsigned short size );
};

#endif