#include "cell.h"

Cell::Cell(int x_, int y_, bool isPort1_, bool isPort2_)
    : x{x_}, y{y_}, isPort1{isPort1_}, isPort2{isPort2_} {
  if (isPort1) appearance = 's';
  if (isPort2) appearance = 'S';
}

char Cell::getAppearance() { return appearance; }

void Cell::setAppearance(char letter) { appearance = letter; }

int Cell::getOwner() { return owner; };

void Cell::setOwner(int owner_) { owner = owner_; }


