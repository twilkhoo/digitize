#include "graphicsobserver.h"

#include "board.h"
#include "xwindow.h"

GraphicsObserver::GraphicsObserver(Board* subject_) : subject{subject_} {
  subject->attach(this);
}

GraphicsObserver::~GraphicsObserver() { subject->detach(this); }

void GraphicsObserver::notify(
    const std::string& p1Summary, const std::string& p2Summary,
    const std::string& p1Downloaded, const std::string& p2Downloaded,
    std::unordered_map<char, std::string>& allLinkNames,
    const std::string& p1Abilities, const std::string& p2Abilities) {
  w.drawString(20, 40, "Player 1:", Xwindow::White);
  w.drawString(20, 60, p1Downloaded, Xwindow::White);
  w.drawString(20, 80, "Abilities: " + p1Abilities, Xwindow::White);

  char curChar;
  std::string displayStr;
  for (int row = 0; row < subject->getLength(); row++) {
    for (int col = 0; col < subject->getLength(); col++) {
      curChar = subject->getState(col, row);

      if (curChar == '.') {
        w.fillRectangle(
            (row * cellWidth) + ((row + 1) * border),
            (col * cellWidth) + ((col + 1) * border) + verticalOffset,
            cellWidth, cellWidth, Xwindow::White);
      }

      else if (curChar == 's' || curChar == 'S') {
        displayStr = curChar;
        w.fillRectangle(
            (row * cellWidth) + ((row + 1) * border),
            (col * cellWidth) + ((col + 1) * border) + verticalOffset,
            cellWidth, cellWidth, Xwindow::Purple);
        w.drawString(
            (row * cellWidth) + ((row + 1) * border) + stringLeftMargin + 12,
            (col * cellWidth) + ((col + 1) * border) + verticalOffset +
                stringVerticalOffset,
            displayStr, Xwindow::White);
      }

      else if ((curChar >= 'a' && curChar <= 'h') ||
               (curChar >= 'A' && curChar <= 'H')) {
        if (allLinkNames[curChar][0] == 'D') {
          displayStr = curChar;
          displayStr += ": " + allLinkNames[curChar];
          w.fillRectangle(
              (row * cellWidth) + ((row + 1) * border),
              (col * cellWidth) + ((col + 1) * border) + verticalOffset,
              cellWidth, cellWidth, Xwindow::Green);
          w.drawString(
              (row * cellWidth) + ((row + 1) * border) + stringLeftMargin,
              (col * cellWidth) + ((col + 1) * border) + verticalOffset +
                  stringVerticalOffset,
              displayStr, Xwindow::White);
        } else if (allLinkNames[curChar][0] == 'V') {
          displayStr = curChar;
          displayStr += ": " + allLinkNames[curChar];
          w.fillRectangle(
              (row * cellWidth) + ((row + 1) * border),
              (col * cellWidth) + ((col + 1) * border) + verticalOffset,
              cellWidth, cellWidth, Xwindow::Red);
          w.drawString(
              (row * cellWidth) + ((row + 1) * border) + stringLeftMargin,
              (col * cellWidth) + ((col + 1) * border) + verticalOffset +
                  stringVerticalOffset,
              displayStr, Xwindow::White);
        } else if (allLinkNames[curChar][0] == '?') {
          displayStr = curChar;
          displayStr += ": ?";
          w.fillRectangle(
              (row * cellWidth) + ((row + 1) * border),
              (col * cellWidth) + ((col + 1) * border) + verticalOffset,
              cellWidth, cellWidth, Xwindow::Gray);
          w.drawString(
              (row * cellWidth) + ((row + 1) * border) + stringLeftMargin + 3,
              (col * cellWidth) + ((col + 1) * border) + verticalOffset +
                  stringVerticalOffset,
              displayStr, Xwindow::White);
        }
      }
    }
  }

  w.drawString(20, 620, "Player 2:", Xwindow::White);
  w.drawString(20, 640, p2Downloaded, Xwindow::White);
  w.drawString(20, 660, "Abilities: " + p2Abilities, Xwindow::White);
}
