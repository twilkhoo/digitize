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

void LinkBoost::useAbility(int player, char l) {
  if (isUsed) throw "Ability already used.";
  if (tolower(l) < 'a' || tolower(l) > 'h') throw "Unknown link.";
  if (charToLink[l]->getOwner() != player) throw "You can only boost your own link.";
  charToLink[l]->boost();
  isUsed = true;
  cout << "LinkBoost used with link " << l << endl;
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

void Firewall::useAbility(int player, int x, int y) {
  if (isUsed) throw "Ability already used.";
  if (board.grid[x][y]->getPort1() ||
      board.grid[x][y]->getPort2() ||
      board.grid[x][y]->getHighGround1() ||
      board.grid[x][y]->getHighGround2() ||
      board.grid[x][y]->getFirewall1() ||
      board.grid[x][y]->getFirewall2()) {
        throw "You can't place your firewall on cells occupied by ports and other abilities.";
      }
  if (player == 1) {
    board.grid[x][y]->setFirewall1();
    board.grid[x][y]->setAppearance('m');
  } else {
    board.grid[x][y]->setFirewall2();
    board.grid[x][y]->setAppearance('w');
  }
  isUsed = true;
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

void Download::useAbility(int player, char l) {
  if (isUsed) throw "Ability already used.";
  if (charToLink[l]->getOwner() == player) throw "You can only download your opponent's link.";
  charToLink[l]->download();
  isUsed = true;
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

void Polarize::useAbility(int player, char l) {
  if (isUsed) throw "Ability already used.";
  charToLink[l]->linkSwitch();
  isUsed = true;
  cout << "Polarize useability called with link char " << l << endl;
}

// ----------------------------------------------------------------------------
// Scan
// ----------------------------------------------------------------------------

Scan::Scan(int i, std::unordered_map<char, Link*>& charToLink_, Board& board_)
    : Ability("Scan", "char", "Reveals the type of any link on the field.",
              "ability " + std::to_string(i) + " <linkChar>", i, charToLink_,
              board_){};

void Scan::useAbility(int player, char l) {
  if (isUsed) throw "Ability already used.";
  if (charToLink[l]->getOwner() == player) throw "You can only scan your opponent's link.";
  if (!(charToLink[l]->getIsHidden())) throw "This link has already been revealed.";
  charToLink[l]->reveal();
  isUsed = true;
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

void LinkReborn::useAbility(int player, char l) {
  if (isUsed) throw "Ability already used.";
  if (charToLink[l]->isReborn()) throw "This link has already been revived once.";
  if (charToLink[l]->getSelfDownloaded()) throw "You cannot revive a link you self-downloaded.";
  if (player != charToLink[l]->getOwner()) throw "Cannot cast on enemy link.";
  if (!(charToLink[l]->isDownloaded())) throw "Link is still alive.";
  cout << "LinkReborn useability called with link char " << l << endl;
  int originalCol;
  int originalRow;
  if ('a' <= l && l <= 'h') {
    originalCol = l - 97;
    originalRow = 0;
    if (originalCol == 3 || originalCol == 4) originalRow = 1;
  } 
  else if ('A' <= l && l <= 'H') {
    originalCol = l - 65;
    originalRow = 7;
    if (originalCol == 3 || originalCol == 4) originalRow = 6;
  }
  cout << originalRow << originalCol;
  if (board.grid[originalRow][originalCol]->getAppearance() != '.') throw "Original spawn position of link is not free.";
  board.grid[originalRow][originalCol]->setAppearance(l);
  board.grid[originalRow][originalCol]->setOwner(player);
  charToLink[l]->revive();
  charToLink[l]->setLocation(originalRow, originalCol);
  isUsed = true;
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

void HighGround::useAbility(int player, int x, int y) {
  if (isUsed) throw "Ability already used.";
  if (board.grid[x][y]->getAppearance() == '.') {
    if (player == 1) {
      board.grid[x][y]->setAppearance('z');
      board.grid[x][y]->setOwner(1);
      board.grid[x][y]->setHighGround1();
    }
    else if (player == 2) {
      board.grid[x][y]->setAppearance('Z');
      board.grid[x][y]->setOwner(2);
      board.grid[x][y]->setHighGround2();
    }
  } 
  else { throw "Ability used on top of link or existing ability, specify a blank position."; }
  isUsed = true;
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

void Portal::useAbility(int player, char l1, char l2) {
  if (isUsed) { throw "Ability already used."; }
  if (charToLink[l1]->getOwner() != player || charToLink[l2]->getOwner() != player) throw "Links are not both owned by player.";
  if (charToLink[l1]->isDead() || charToLink[l2]->isDead()) throw "Error: both links must be on the board.";
  char c1 = charToLink[l1]->getLetter();
  char c2 = charToLink[l2]->getLetter();
  int row1 = charToLink[l1]->getRow();
  int row2 = charToLink[l2]->getRow();
  int col1 = charToLink[l1]->getCol();
  int col2 = charToLink[l2]->getCol();
  board.grid[row1][col1]->setAppearance(c2) ;
  board.grid[row2][col2]->setAppearance(c1) ;
  charToLink[l1]->setLocation(row2, col2);
  charToLink[l2]->setLocation(row1, col1);
  cout << "Portal useability called with link char l1 " << l1 << " and l2 "
       << l2 << endl;
}
