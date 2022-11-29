#include "cell.h"

Cell::Cell(int x_, int y_, bool isPort1_, bool isPort2_)
    : x{x_}, y{y_}, isPort1{isPort1_}, isPort2{isPort2_} {}

char Cell::getAppearance() {
  return appearance;
}
