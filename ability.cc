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
                 const int& id_, std::unordered_map<char, Link*>& charToLink_,
                 Board& board_)
    : name{name_},
      params{params_},
      description{description_},
      usage{usage_},
      id{id_},
      charToLink{charToLink_},
      board{board_} {}

string Ability::getName() { return name; }

string Ability::getParams() { return params; }

string Ability::getDescription() { return description; }

string Ability::getUsage() { return usage; }

bool Ability::getIsUsed() { return isUsed; }

int Ability::getId() { return id; }

// ----------------------------------------------------------------------------
// LinkBoost
// ----------------------------------------------------------------------------

LinkBoost::LinkBoost(int i, std::unordered_map<char, Link*>& charToLink_,
                     Board& board_)
    : Ability("LinkBoost", "char",
              "Allows one of your links to move two spaces at a time, being "
              "able to jump "
              "over obstacles.",
              "ability " + std::to_string(i) + " <personalLinkChar>", i,
              charToLink_, board_) {}

void LinkBoost::useAbility(char l) {
  cout << charToLink[l] << endl;
  cout << "Linkboost useability called with link char " << l << endl;
}

// ----------------------------------------------------------------------------
// Firewall
// ----------------------------------------------------------------------------

Firewall::Firewall(int i, std::unordered_map<char, Link*>& charToLink_,
                   Board& board_)
    : Ability("Firewall", "intint",
              "Places a firewall on an empty square. When an opponent's link "
              "passes through this square, the opponent link is revealed, and "
              "if it is a virus, it is downloaded by the opponent.",
              "ability " + std::to_string(i) + " <rowNum> <colNum>", i,
              charToLink_, board_){};

void Firewall::useAbility(int x, int y) {
  cout << "Firewall useability called with int x " << x << " and y " << y
       << endl;
}

// ----------------------------------------------------------------------------
// Download
// ----------------------------------------------------------------------------

Download::Download(int i, std::unordered_map<char, Link*>& charToLink_,
                   Board& board_)
    : Ability("Download", "char", "Downloads an opponent's link.",
              "ability " + std::to_string(i) + " <opponentLinkChar>", i,
              charToLink_, board_){};

void Download::useAbility(char l) {
  cout << "Download useability called with link char " << l << endl;
}

// ----------------------------------------------------------------------------
// Polarize
// ----------------------------------------------------------------------------

Polarize::Polarize(int i, std::unordered_map<char, Link*>& charToLink_,
                   Board& board_)
    : Ability("Polarize", "char",
              "Changes any link from a data to a virus of same strength, or "
              "vice versa.",
              "ability " + std::to_string(i) + " <linkChar>", i, charToLink_,
              board_){};

void Polarize::useAbility(char l) {
  cout << "Polarize useability called with link char " << l << endl;
}

// ----------------------------------------------------------------------------
// Scan
// ----------------------------------------------------------------------------

Scan::Scan(int i, std::unordered_map<char, Link*>& charToLink_, Board& board_)
    : Ability("Scan", "char", "Reveals the type of any link on the field.",
              "ability " + std::to_string(i) + " <linkChar>", i, charToLink_,
              board_){};

void Scan::useAbility(char l) {
  cout << "Scan useability called with link char " << l << endl;
}

// ----------------------------------------------------------------------------
// LinkReborn
// ----------------------------------------------------------------------------

LinkReborn::LinkReborn(int i, std::unordered_map<char, Link*>& charToLink_,
                       Board& board_)
    : Ability(
          "LinkReborn", "char",
          "Revives any of your links that are currently not in play, placing "
          "it in the first open square closest to your starting edge.",
          "ability " + std::to_string(i) + " <personalLinkChar>", i,
          charToLink_, board_){};

void LinkReborn::useAbility(char l) {
  cout << "LinkReborn useability called with link char " << l << endl;
}

// ----------------------------------------------------------------------------
// HighGround
// ----------------------------------------------------------------------------

HighGround::HighGround(int i, std::unordered_map<char, Link*>& charToLink_,
                       Board& board_)
    : Ability("HighGround", "intint",
              "Makes any empty square a high ground square, which opponent "
              "links cannot pass through, and your links gain one strength "
              "when on it. Opponents can only break the high ground square "
              "after winning a battle against a link on the high ground.",
              "ability " + std::to_string(i) +
                  " <rowNum> <colNum>, 2 <= rowNum <= 5",
              i, charToLink_, board_){};

void HighGround::useAbility(int x, int y) {
  cout << "HighGround useability called with int x " << x << " and y " << y
       << endl;
}

// ----------------------------------------------------------------------------
// Portal
// ----------------------------------------------------------------------------

Portal::Portal(int i, std::unordered_map<char, Link*>& charToLink_,
               Board& board_)
    : Ability("Portal", "charchar",
              "Swaps the positions of any two of your links.",
              "ability " + std::to_string(i) +
                  " <personalLinkChar1> <personalLinkChar2>",
              i, charToLink_, board_){};

void Portal::useAbility(char l1, char l2) {
  cout << "Portal useability called with link char l1 " << l1 << " and l2 "
       << l2 << endl;
}
