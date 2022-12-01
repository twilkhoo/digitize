#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H
#include <iostream>

#include "board.h"
#include "observer.h"

class TextObserver : public Observer {
  Board* subject;
  std::ostream& out = std::cout;

 public:
  TextObserver(Board* subject_);
  ~TextObserver();
  void notify(const std::string& p1Summary, const std::string& p2Summary,
              const std::string& p1Downloaded, const std::string& p2Downloaded,
              std::unordered_map<char, std::string>& allLinkNames,
              const std::string& p1Abilities,
              const std::string& p2Abilities) override;
};
#endif
