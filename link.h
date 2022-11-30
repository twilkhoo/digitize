#ifndef LINK_H
#define LINK_H

#include <unordered_map>
#include <string>
#include "board.h"


class Link {
 protected:
  int strength;
  Board &board;
  int owner;
  char letter; // Identifier for the link, from a-h or A-H.
  bool isData;
  std::unordered_map<char, Link*>& allCharToLink;

  bool isHidden = true;
  int row;
  int col;
  int speed = 1;
  std::string name;

 public:
  virtual void move(char dir) = 0;
  void commonMove(char dir);
  void setLocation(int row_, int col_);
  std::string getName();
  bool getIsHidden();

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
