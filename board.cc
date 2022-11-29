#include "board.h"

#include <vector>

Board::Board() {
  for (int i = 0; i < length; i++) {
    std::vector<Cell*> curRow;
    for (int j = 0; j < length; j++) {
      bool isPort1 = false;
      bool isPort2 = false;
      if (i == 0 && (j == 3 || j == 4)) isPort1 = true;
      if (i == length - 1 && (j == 3 || j == 4)) isPort2 = true;

      curRow.push_back(new Cell(i, j, isPort1, isPort2));
    }
    grid.push_back(curRow);
  }
}

Board::~Board() {
  for (auto v : grid) {
    for (auto c : v) {
      delete c;
    }
  }
}

