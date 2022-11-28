#include "ability.h"

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

// ----------------------------------------------------------------------------
// Parent Ability class
// ----------------------------------------------------------------------------

Ability::Ability(const string& name_, const string& params_,
                 const string& description_, const string& usage_,
                 const bool& isUsed_, const int& id_)
    : name{name_},
      params{params_},
      description{description_},
      usage{usage_},
      isUsed{isUsed_},
      id{id_} {}

std::unordered_map<char, Link*>* Ability::charToLinkP1;
void Ability::setCharToLinkP1(std::unordered_map<char, Link*>* charToLinkP1_) {
  Ability::charToLinkP1 = charToLinkP1_;
}

std::unordered_map<char, Link*>* Ability::charToLinkP2;
void Ability::setCharToLinkP2(std::unordered_map<char, Link*>* charToLinkP2_) {
  Ability::charToLinkP2 = charToLinkP2_;
}

string Ability::getName() { return name; }

string Ability::getParams() { return params; }

string Ability::getDescription() { return description; }

string Ability::getUsage() { return usage; }

bool Ability::getIsUsed() { return isUsed; }

int Ability::getId() { return id; }

void Ability::setId(const int& id_) { id = id_; }

// ----------------------------------------------------------------------------
// LinkBoost
// ----------------------------------------------------------------------------

LinkBoost::LinkBoost(int i)
    : Ability("LinkBoost", "char",
              "Allows one of your links to move two spaces at a time, being "
              "able to jump "
              "over obstacles.",
              "ability " + std::to_string(i) + " <personalLinkChar>") {
  setId(i);
}

void LinkBoost::useAbility(int player, char l) {
  cout << (*charToLinkP1)[l] << endl;
  cout << "Linkboost useability called with link char " << l << endl;
}

// ----------------------------------------------------------------------------
// Firewall
// ----------------------------------------------------------------------------

Firewall::Firewall(int i)
    : Ability("Firewall", "intint",
              "Places a firewall on an empty square. When an opponent's link "
              "passes through this square, the opponent link is revealed, and "
              "if it is a virus, it is downloaded by the opponent.",
              "ability " + std::to_string(i) + " <rowNum> <colNum>") {
  setId(i);
}

void Firewall::useAbility(int player, int x, int y) {
  cout << "Firewall useability called with int x " << x << " and y " << y
       << endl;
}

// ----------------------------------------------------------------------------
// Download
// ----------------------------------------------------------------------------

Download::Download(int i)
    : Ability("Download", "char", "Downloads an opponent's link.",
              "ability " + std::to_string(i) + " <opponentLinkChar>") {
  setId(i);
}
void Download::useAbility(int player, char l) {
  cout << "Download useability called with link char " << l << endl;
}

// ----------------------------------------------------------------------------
// Polarize
// ----------------------------------------------------------------------------

Polarize::Polarize(int i)
    : Ability("Polarize", "char",
              "Changes any link from a data to a virus of same strength, or "
              "vice versa.",
              "ability " + std::to_string(i) + " <linkChar>") {
  setId(i);
}

void Polarize::useAbility(int player, char l) {
  cout << "Polarize useability called with link char " << l << endl;
}

// ----------------------------------------------------------------------------
// Scan
// ----------------------------------------------------------------------------

Scan::Scan(int i)
    : Ability("Scan", "char", "Reveals the type of any link on the field.",
              "ability " + std::to_string(i) + " <linkChar>") {
  setId(i);
}

void Scan::useAbility(int player, char l) {
  cout << "Scan useability called with link char " << l << endl;
}

// ----------------------------------------------------------------------------
// LinkReborn
// ----------------------------------------------------------------------------

LinkReborn::LinkReborn(int i)
    : Ability(
          "LinkReborn", "char",
          "Revives any of your links that are currently not in play, placing "
          "it in the first open square closest to your starting edge.",
          "ability " + std::to_string(i) + " <personalLinkChar>") {
  setId(i);
}

void LinkReborn::useAbility(int player, char l) {
  cout << "LinkReborn useability called with link char " << l << endl;
}

// ----------------------------------------------------------------------------
// HighGround
// ----------------------------------------------------------------------------

HighGround::HighGround(int i)
    : Ability("HighGround", "intint",
              "Makes any empty square a high ground square, which opponent "
              "links cannot pass through, and your links gain one strength "
              "when on it. Opponents can only break the high ground square "
              "after winning a battle against a link on the high ground.",
              "ability " + std::to_string(i) +
                  " <rowNum> <colNum>, 2 <= rowNum <= 5") {
  setId(i);
}

void HighGround::useAbility(int player, int x, int y) {
  cout << "HighGround useability called with int x " << x << " and y " << y
       << endl;
}

// ----------------------------------------------------------------------------
// Portal
// ----------------------------------------------------------------------------

Portal::Portal(int i)
    : Ability("Portal", "charchar",
              "Swaps the positions of any two of your links.",
              "ability " + std::to_string(i) +
                  " <personalLinkChar1> <personalLinkChar2>") {
  setId(i);
}

void Portal::useAbility(int player, char l1, char l2) {
  cout << "Portal useability called with link char l1 " << l1 << " and l2 "
       << l2 << endl;
}
