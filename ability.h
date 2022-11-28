#ifndef ABILITY_H
#define ABILITY_H

#include <string>
#include <unordered_map>

#include "link.h"

class Ability {
 protected:
  std::string name;
  std::string params;
  std::string description;
  std::string usage;
  bool isUsed;
  int id;  // The id a player's ability has, from 1-5.

 public:
  bool getIsUsed();
  std::string getParams();
  std::string getName();
  std::string getDescription();
  std::string getUsage();
  int getId();
  void setId(const int& id_);

  static std::unordered_map<char, Link*>* charToLinkP1;
  static std::unordered_map<char, Link*>* charToLinkP2;
  static void setCharToLinkP1(std::unordered_map<char, Link*>* charToLinkP1_);
  static void setCharToLinkP2(std::unordered_map<char, Link*>* charToLinkP2_);

  virtual void useAbility(int player, char l) { return; };
  virtual void useAbility(int player, int x, int y) { return; };
  virtual void useAbility(int player, char l1, char l2) { return; };
  virtual void makeAbilityAbstract() = 0;

  // Ability(const std::unordered_map<char, Link*>& personalCharToLink_, const
  // std::string& name_, const std::string& params_,
  //         const std::string& description_, const std::string& usage_, const
  //         bool& isUsed_ = false, const int& id_ = 0);

  Ability(const std::string& name_, const std::string& params_,
          const std::string& description_, const std::string& usage_,
          const bool& isUsed_ = false, const int& id_ = 0);

  void setStaticLinkMap(std::unordered_map<char, Link*>&);

  virtual ~Ability() = default;
};

class LinkBoost : public Ability {
 private:
  void makeAbilityAbstract() { return; };

 public:
  LinkBoost(int i);
  void useAbility(int player, char l);
};

class Firewall : public Ability {
 private:
  void makeAbilityAbstract() { return; };

 public:
  Firewall(int i);
  void useAbility(int player, int x, int y);
};

class Download : public Ability {
 private:
  void makeAbilityAbstract() { return; };

 public:
  Download(int i);
  void useAbility(int player, char l);
};

class Polarize : public Ability {
 private:
  void makeAbilityAbstract() { return; };

 public:
  Polarize(int i);
  void useAbility(int player, char l);
};

class Scan : public Ability {
 private:
  void makeAbilityAbstract() { return; };

 public:
  Scan(int i);
  void useAbility(int player, char l);
};

class LinkReborn : public Ability {
 private:
  void makeAbilityAbstract() { return; };

 public:
  LinkReborn(int i);
  void useAbility(int player, char l);
};

class HighGround : public Ability {
 private:
  void makeAbilityAbstract() { return; };

 public:
  HighGround(int i);
  void useAbility(int player, int x, int y);
};

class Portal : public Ability {
 private:
  void makeAbilityAbstract() { return; };

 public:
  Portal(int i);
  void useAbility(int player, char l1, char l2);
};

#endif