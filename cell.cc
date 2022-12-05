#include "cell.h"

Cell::Cell(int x_, int y_, bool isPort1_, bool isPort2_)
    : x{x_}, y{y_}, isPort1{isPort1_}, isPort2{isPort2_} {
  if (isPort1) appearance = 's';
  if (isPort2) appearance = 'S';
}

bool Cell::getFirewall1() { return isFirewall1; }

bool Cell::getFirewall2() { return isFirewall2; }

bool Cell::getHighGround1() { return isHighGround1; }

bool Cell::getHighGround2() { return isHighGround2; }

bool Cell::getPort1() { return isPort1; }

bool Cell::getPort2() { return isPort2; }

void Cell::setFirewall1() { isFirewall1 = true; }

void Cell::setFirewall2() { isFirewall2 = true; }

void Cell::setHighGround1() { isHighGround1 = true; }

void Cell::setHighGround2() { isHighGround2 = true; }

char Cell::getAppearance() { return appearance; }

void Cell::setAppearance(char letter) { appearance = letter; }

int Cell::getOwner() { return owner; };

void Cell::setOwner(int owner_) { owner = owner_; }

void Cell::destroyHighGround() { isHighGround1 = false; isHighGround2 = false; }
