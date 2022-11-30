#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>

#include "board.h"
#include "player.h"

class Controller {
  Board* board;
  Player* p1;
  Player* p2;

 public:
  Controller(std::string abilitiesP1, std::string abilitiesP2,
             std::string linksP1, std::string linksP2);
  ~Controller();

  void runGame();
};

#endif
