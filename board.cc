#include "board.h"

#include <vector>
#include <iostream>

Board::Board() {
  std::cout << "creating board" << std::endl;

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
  std::cout << "deleting board" << std::endl;
  for (auto v : grid) {
    for (auto c : v) {
      delete c;
    }
  }
}

std::ostream& operator<<(std::ostream& out, Board& board) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      out << board.grid[i][j]->getAppearance();
    }
    out << std::endl;
  }
  return out;
}


