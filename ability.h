#ifndef ABILITY_H
#define ABILITY_H

#include <string>
#include <unordered_map>

#include "link.h"
#include "board.h"

// ----------------------------------------------------------------------------
// Parent Ability class
// ----------------------------------------------------------------------------

class Ability {
 private:
  virtual void makeAbilityAbstract() = 0;

 protected:
  std::string name;
  std::string params;
  std::string description;
  std::string usage;
  int id;  // The id a player's ability has, from 1-5.
  std::unordered_map<char, Link*> &charToLink;
  Board &board;
  bool isUsed = false;

 public:
  std::string getName();
  std::string getParams();
  std::string getDescription();
  std::string getUsage();
  int getId();
  bool getIsUsed();

  virtual void useAbility(int player, char l) { return; };
  virtual void useAbility(int player, int x, int y) { return; };
  virtual void useAbility(int player, char l1, char l2) { return; };

  Ability(const std::string& name_, const std::string& params_,
          const std::string& description_, const std::string& usage_,
          const int& id_, std::unordered_map<char, Link*> &charToLink_, Board& board_);

  virtual ~Ability() = default;
};

// ----------------------------------------------------------------------------
// LinkBoost
// ----------------------------------------------------------------------------

class LinkBoost : public Ability {
 private:
  void makeAbilityAbstract() { return; };

 public:
  LinkBoost(int i, std::unordered_map<char, Link*> &charToLink_, Board& board_);
  void useAbility(int player, char l);
};

// ----------------------------------------------------------------------------
// Firewall
// ----------------------------------------------------------------------------

class Firewall : public Ability {
 private:
  void makeAbilityAbstract() { return; };

 public:
  Firewall(int i, std::unordered_map<char, Link*> &charToLink_, Board& board_);
  void useAbility(int player, int x, int y);
};

// ----------------------------------------------------------------------------
// Download
// ----------------------------------------------------------------------------

class Download : public Ability {
 private:
  void makeAbilityAbstract() { return; };

 public:
  Download(int i, std::unordered_map<char, Link*> &charToLink_, Board& board_);
  void useAbility(int player, char l);
};

// ----------------------------------------------------------------------------
// Polarize
// ----------------------------------------------------------------------------

class Polarize : public Ability {
 private:
  void makeAbilityAbstract() { return; };

 public:
  Polarize(int i, std::unordered_map<char, Link*> &charToLink_, Board& board_);
  void useAbility(int player, char l);
};

// ----------------------------------------------------------------------------
// Scan
// ----------------------------------------------------------------------------

class Scan : public Ability {
 private:
  void makeAbilityAbstract() { return; };

 public:
  Scan(int i, std::unordered_map<char, Link*> &charToLink_, Board& board_);
  void useAbility(int player, char l);
};

// ----------------------------------------------------------------------------
// LinkReborn
// ----------------------------------------------------------------------------

class LinkReborn : public Ability {
 private:
  void makeAbilityAbstract() { return; };

 public:
  LinkReborn(int i, std::unordered_map<char, Link*> &charToLink_, Board& board_);
  void useAbility(int player, char l);
};

// ----------------------------------------------------------------------------
// HighGround
// ----------------------------------------------------------------------------

class HighGround : public Ability {
 private:
  void makeAbilityAbstract() { return; };

 public:
  HighGround(int i, std::unordered_map<char, Link*> &charToLink_, Board& board_);
  void useAbility(int player, int x, int y);
};

// ----------------------------------------------------------------------------
// Portal
// ----------------------------------------------------------------------------

class Portal : public Ability {
 private:
  void makeAbilityAbstract() { return; };

 public:
  Portal(int i, std::unordered_map<char, Link*> &charToLink_, Board& board_);
  void useAbility(int player, char l1, char l2);
};

#endif
