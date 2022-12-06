#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

#include "ability.h"
#include "link.h"
#include "board.h"

class Player {
 private:
  int playerNum;
  Board& board;
  static bool deletedCharMap;
  int dataCount = 0;
  int virusCount = 0;
  int abilitiesCount = 5;

 public:
  Player(std::string linkString, std::string abilityString, int playerNum_, Board& board_);

  std::unordered_map<int, std::shared_ptr<Ability>> intToAbility;
  static std::unordered_map<char, std::shared_ptr<Link>> allCharToLink;

  int getPlayerNum();
  int getDataCount();
  int getVirusCount();
  int getAbilitiesCount();
  void increaseData();
  void increaseVirus();
  void resetData();
  void resetVirus();
  void decreaseAbilities();
  void resetAbilities();
  
};

#endif
