#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include "cell.h"

class Board {
 private:
 int length = 8;

 public:
  std::vector<std::vector<Cell*>> grid;

  Board();
  ~Board();

};

#endif