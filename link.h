#ifndef LINK_H
#define LINK_H

#include <unordered_map>

#include "board.h"


class Link {
 protected:
  int strength;
  Board &board;
  int owner;
  char letter;
  int row;
  int col;
  bool isData;
  std::unordered_map<char, Link*>& allCharToLink;

  int speed = 1;

 public:
  virtual void move(char dir) = 0;
  void commonMove(char dir);
  void setLocation(int row_, int col_);

  Link(int strength_, Board& board_, int owner, char letter_, bool isData_, std::unordered_map<char, Link*>& allCharToLink_);
  virtual ~Link() = default;
};

class Data : public Link {
 public:
  Data(int strength_, Board& board_, int owner, char letter_, bool isData_, std::unordered_map<char, Link*>& allCharToLink_);
  void move(char dir);
};

class Virus : public Link {
 public:
  Virus(int strength_, Board& board_, int owner, char letter_, bool isData_, std::unordered_map<char, Link*>& allCharToLink_);
  void move(char dir);
};

#endif
