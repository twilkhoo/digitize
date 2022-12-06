#ifndef GRAPHICSOBSERVER_H
#define GRAPHICSOBSERVER_H

#include <memory>

#include "board.h"
#include "observer.h"
#include "xwindow.h"

class GraphicsObserver : public Observer {
  std::shared_ptr<Board> subject;
  int border = 10;
  int cellWidth = 50;
  int extraVerticalSpace = 200;
  int verticalOffset = extraVerticalSpace / 2;
  int displayWidth = cellWidth * 8 + border * 9;
  int displayHeight = displayWidth + extraVerticalSpace;
  int stringVerticalOffset = cellWidth / 2 + 4;
  int stringLeftMargin = 10;
  Xwindow w{displayWidth, displayHeight};

 public:
  GraphicsObserver(std::shared_ptr<Board> subject_);
  ~GraphicsObserver();
  void notify(const std::string& p1Summary, const std::string& p2Summary,
              const std::string& p1Downloaded, const std::string& p2Downloaded,
              std::unordered_map<char, std::string>& allLinkNames,
              const std::string& p1Abilities,
              const std::string& p2Abilities) override;
};
#endif
