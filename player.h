#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <unordered_map>
#include <vector>

#include "ability.h"
#include "link.h"
#include "board.h"

class Player {
 private:
  int playerNum;
  Board& board;

 public:
  Player(std::string linkString, std::string abilityString, int playerNum_, Board& board_);
  ~Player();

  std::unordered_map<int, Ability*> intToAbility;
  std::unordered_map<char, Link*> charToLink;

  int getPlayerNum();
};

#endif
