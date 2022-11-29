#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>

#include "cell.h"

class Board {
 private:
 int length = 8;

 public:
  std::vector<std::vector<Cell*>> grid;

  Board();
  ~Board();

  friend std::ostream& operator<<(std::ostream& out, Board& board);

};

#endif