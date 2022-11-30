#ifndef CELL_H
#define CELL_H

class Cell {
 private:
  int x;
  int y;
  
  char appearance = '.';

  int owner = 0;

  bool isPort1;
  bool isPort2;
  bool isFirewall1;
  bool isFirewall2;
  bool isHighGround1;
  bool isHighGround2;


 public:

  Cell(int x_, int y_, bool isPort1_, bool isPort2_);
  ~Cell() = default;

  char getAppearance();
  void setAppearance (char letter);


  int getOwner();
  void setOwner(int owner_);
};

#endif