#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include <string>

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

  void render(const std::string& p1Summary, const std::string& p2Summary);

  int getLength();

  char getState(int row, int col) const;

};

#endif