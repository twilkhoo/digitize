#include "board.h"

#include <iostream>
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

int Board::getLength() { return length; }

char Board::getState(int row, int col) const {
  return grid[row][col]->getAppearance();
}

void Board::render(const std::string& p1Summary, const std::string& p2Summary,
                   const std::string& p1Downloaded,
                   const std::string& p2Downloaded,
                   std::unordered_map<char, std::string>& allLinkNames,
                   const std::string& p1Abilities,
                   const std::string& p2Abilities) {
  notifyObservers(p1Summary, p2Summary, p1Downloaded, p2Downloaded,
                  allLinkNames, p1Abilities, p2Abilities);
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
