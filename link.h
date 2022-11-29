#ifndef LINK_H
#define LINK_H

#include "board.h"

class Link {
 protected:
  int strength;
  Board board;

 public:
  Link(int strength_, Board board_);
  virtual void move() = 0;
  virtual ~Link() = default;
};

class Data : public Link {
 public:
  Data(int strength_, Board board_);
  void move();
};

class Virus : public Link {
 public:
  Virus(int strength_, Board board_);
  void move();
};

#endif
