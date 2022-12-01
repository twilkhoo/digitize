#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>

#include "board.h"
#include "graphicsobserver.h"
#include "player.h"
#include "textobserver.h"

class Controller {
  Board* board;
  Player* p1;
  Player* p2;
  TextObserver* textObserver;
  bool graphics;
  GraphicsObserver* graphicsObserver;

 public:
  Controller(std::string abilitiesP1, std::string abilitiesP2,
             std::string linksP1, std::string linksP2, bool graphics_);
  ~Controller();

  void runGame();

  void callBoard(Player* curPlayer);
};

#endif
