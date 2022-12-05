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
  bool isFirewall1 = false;
  bool isFirewall2 = false;
  bool isHighGround1 = false;
  bool isHighGround2 = false;


 public:

  Cell(int x_, int y_, bool isPort1_, bool isPort2_);
  ~Cell() = default;

  char getAppearance();
  void setAppearance (char letter);
  bool getFirewall1();
  bool getFirewall2();
  int getOwner();
  void setOwner(int owner_);
  bool getPort1();
  bool getPort2();
  bool getHighGround1();
  bool getHighGround2();
  void setFirewall1();
  void setFirewall2();
  void setHighGround1();
  void setHighGround2();
  void destroyHighGround();
};

#endif
