#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H
#include "observer.h"
#include "board.h"
#include <iostream>

class TextObserver : public Observer {
  Board* subject;
  std::ostream &out = std::cout;

 public:
  TextObserver(Board* subject_);
  ~TextObserver();
  void notify() override;
};
#endif
