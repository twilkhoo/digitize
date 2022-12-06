#ifndef LINK_H
#define LINK_H

#include <unordered_map>
#include <string>
#include <memory>

#include "board.h"

class Link {
 protected:
  int strength;
  Board &board;
  int owner;
  char letter; // Identifier for the link, from a-h or A-H.
  bool isData;
  std::unordered_map<char, std::shared_ptr<Link>>& allCharToLink;

  bool isHidden = true;
  bool Downloaded = false;
  bool selfDownloaded = false;
  bool reborn = false;
  bool dead = false;
  int row;
  int col;
  int speed = 1;
  std::string name;

 public:
  virtual void move(char dir) = 0;
  void commonMove(char dir);
  void setLocation(int row_, int col_);
  std::string getName();
  void setName(std::string s);
  bool getIsHidden();
	int getOwner();
  void boost();
  int battle(char l2);
  int getRow();
  int getCol();
  int getStrength();
  char getLetter();
  void download();
  void reveal();
  bool isVirus();
  bool isDownloaded();
  void selfDownload();
  bool getSelfDownloaded();
  void linkSwitch();
  void movingFromAbility(); // checks if moving off a firewall, set it back to firewall
  void revive();
  bool isDead();
  bool isReborn();

  Link(int strength_, Board& board_, int owner, char letter_, bool isData_, std::unordered_map<char, std::shared_ptr<Link>>& allCharToLink_);
  virtual ~Link() = default;
};

class Data : public Link {
 public:
  Data(int strength_, Board& board_, int owner, char letter_, bool isData_, std::unordered_map<char, std::shared_ptr<Link>>& allCharToLink_);
  void move(char dir);
};

class Virus : public Link {
 public:
  Virus(int strength_, Board& board_, int owner, char letter_, bool isData_, std::unordered_map<char, std::shared_ptr<Link>>& allCharToLink_);
  void move(char dir);
};

#endif
