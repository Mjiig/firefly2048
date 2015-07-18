#include "rand.h"

#ifndef BOARD_H
#define BOARD_H

class Board{
 private:
  const static int values[];

  int grid[4][4];
  int score;
  Rand r;

  int get_new_piece();
  bool move(int startx, int endx, int starty, int endy, int dx, int dy, int sx, int sy);

 public:
  Board();

  void add_piece();
  bool moveleft();
  bool moveright();
  bool moveup();
  bool movedown();
  void pretty_print();
  int getscore();

};

#endif
