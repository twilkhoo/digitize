#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

#include "cell.h"
#include "subject.h"

class Board : public Subject {
 private:
  int length = 8;

 public:
  std::vector<std::vector<std::unique_ptr<Cell>>> grid;

  Board();
  ~Board() = default;

  friend std::ostream& operator<<(std::ostream& out, Board& board);

  void render(const std::string& p1Summary, const std::string& p2Summary,
              const std::string& p1Downloaded, const std::string& p2Downloaded,
              std::unordered_map<char, std::string>& allLinkNames,
              const std::string& p1Abilities, const std::string& p2Abilities);

  int getLength();

  char getState(int row, int col) const;
};

#endif
