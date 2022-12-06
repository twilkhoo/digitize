#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <memory>

#include "board.h"
#include "graphicsobserver.h"
#include "player.h"
#include "textobserver.h"

class Controller {
  std::shared_ptr<Board> board;
  std::shared_ptr<Player> p1;
  std::shared_ptr<Player> p2;
  std::shared_ptr<TextObserver> textObserver;
  bool graphics;
  std::shared_ptr<GraphicsObserver> graphicsObserver;

 public:
  Controller(std::string abilitiesP1, std::string abilitiesP2,
             std::string linksP1, std::string linksP2, bool graphics_);

  void runGame();

  void callBoard(std::shared_ptr<Player> curPlayer);
};

#endif
