#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>

#include "subject.h"
#include "cell.h"

class Board : public Subject {
 private:
 int length = 8;

 public:
  std::vector<std::vector<Cell*>> grid;

  Board();
  ~Board();

  friend std::ostream& operator<<(std::ostream& out, Board& board);

  void render();

  int getLength();

  char getState(int row, int col) const;

};

#endif