#include "graphicsobserver.h"

#include "board.h"
#include "xwindow.h"
#include <sstream>

GraphicsObserver::GraphicsObserver(Board* subject_) : subject{subject_} {
  subject->attach(this);
}

GraphicsObserver::~GraphicsObserver() { subject->detach(this); }

void GraphicsObserver::notify(
    const std::string& p1Summary, const std::string& p2Summary,
    const std::string& p1Downloaded, const std::string& p2Downloaded,
    std::unordered_map<char, std::string>& allLinkNames,
    const std::string& p1Abilities, const std::string& p2Abilities) {

  w.fillRectangle(20, 0, 400, 105, Xwindow::Black);
  w.drawString(20, 20, "Player 1:", Xwindow::White);
  w.drawString(20, 40, p1Downloaded, Xwindow::White);
  w.drawString(20, 60, "Abilities: " + p1Abilities, Xwindow::White);
  std::ostringstream summaryline1;
  std::ostringstream summaryline2;
  for (char ch = 'a'; ch <= 'd'; ch++) {
    summaryline1 << ch << ": " << allLinkNames[ch] << " ";
  }
  for (char ch = 'e'; ch <= 'h'; ch++) {
    summaryline2 << ch << ": " << allLinkNames[ch] << " ";
  }
  w.drawString(20, 80, summaryline1.str(), Xwindow::White);
  w.drawString(20, 100, summaryline2.str(), Xwindow::White);
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
  w.fillRectangle(20, 600, 400, 105, Xwindow::Black);
  w.drawString(20, 600, "Player 2:", Xwindow::White);
  w.drawString(20, 620, p2Downloaded, Xwindow::White);
  w.drawString(20, 640, "Abilities: " + p2Abilities, Xwindow::White);
  std::ostringstream summaryline1b;
  std::ostringstream summaryline2b;
  for (char ch = 'A'; ch <= 'D'; ch++) {
    summaryline1b << ch << ": " << allLinkNames[ch] << " ";
  }
  for (char ch = 'E'; ch <= 'H'; ch++) {
    summaryline2b << ch << ": " << allLinkNames[ch] << " ";
  }
  w.drawString(20, 660, summaryline1b.str(), Xwindow::White);
  w.drawString(20, 680, summaryline2b.str(), Xwindow::White);
}
