#ifndef LINK_H
#define LINK_H

class Link {
 protected:
  int strength;

 public:
  Link(int strength_);
  virtual void move() = 0;
  virtual ~Link() = default;
};

class Data : public Link {
 public:
  Data(int strength_);
  void move();
};

class Virus : public Link {
 public:
  Virus(int strength_);
  void move();
};

#endif
