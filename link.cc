#include "link.h"

#include <iostream>
#include <memory>
#include <string>

#include "board.h"

using std::cout;
using std::endl;

// ----------------------------------------------------------------------------
// Parent Link class
// ----------------------------------------------------------------------------

Link::Link(int strength_, Board& board_, int owner_, char letter_, bool isData_,
           std::unordered_map<char, std::shared_ptr<Link>>& allCharToLink_)
    : strength{strength_},
      board{board_},
      owner{owner_},
      letter{letter_},
      isData{isData_},
      allCharToLink{allCharToLink_} {
  int rowToAdd;

  if (owner == 1) rowToAdd = 0;
  if (letter == 'd' || letter == 'e') rowToAdd = 1;

  if (owner == 2) rowToAdd = 7;
  if (letter == 'D' || letter == 'E') rowToAdd = 6;

  int colToAdd = toupper(letter) - 'A';

  row = rowToAdd;
  col = colToAdd;
  board.grid[row][col]->appearance = letter;
  board.grid[row][col]->setOwner(owner);
}

void Link::setLocation(int row_, int col_) {
  row = row_;
  col = col_;
  board.grid[row][col]->appearance = letter;
}

void Link::boost() { speed = 2; }

std::string Link::getName() {
  std::string str = "";
  isData ? str += "D" : str += "V";
  str += std::to_string(getStrength() - '0');
  return str;
}

int Link::getRow() { return row; }

int Link::getCol() { return col; }

char Link::getLetter() { return letter; }

bool Link::getIsHidden() { return isHidden; }

// Revives a link for link reborn ability

void Link::revive() {
  Downloaded = false;
  reborn = true;
  dead = false;
}

// Checks if link has been revived

bool Link::isReborn() { return reborn; }

// Switches link from data to a virus or vice versa.
void Link::linkSwitch() {
  if (isData) {
    isData = false;
  } else {
    isData = true;
  }
}

int Link::getOwner() { return owner; }

// Battle command.
int Link::battle(char l2) {
  std::shared_ptr<Link> opponentLink = allCharToLink[l2];
  if (getIsHidden()) {
    reveal();
  }
  if (opponentLink->getIsHidden()) {
    opponentLink->reveal();
  }
  if (getStrength() >= opponentLink->getStrength()) {
    return owner;
  } else {
    return opponentLink->owner;
  }
}

void Link::download() {
  Downloaded = true;
  reveal();
  dead = true;
  board.grid[row][col]->appearance = '.';
  board.grid[row][col]->setOwner(0);
  movingFromAbility();
}

void Link::setName(std::string s) { name = s; }

bool Link::isVirus() { return !isData; }

bool Link::isDownloaded() { return Downloaded; }

void Link::reveal() { isHidden = false; }

bool Link::isDead() { return dead; }

int Link::getStrength() {
  if ((owner == 1 && board.grid[row][col]->getHighGround1()) ||
      (owner == 2 && board.grid[row][col]->getHighGround2())) {
    return strength + 1;
  }
  return strength;
}

bool Link::getSelfDownloaded() { return selfDownloaded; }

void Link::selfDownload() { selfDownloaded = true; }

void Link::movingFromAbility() {
  if (board.grid[row][col]->getFirewall1()) {
    board.grid[row][col]->appearance = 'm';
    board.grid[row][col]->setOwner(1);
  } else if (board.grid[row][col]->getFirewall2()) {
    board.grid[row][col]->appearance = 'w';
    board.grid[row][col]->setOwner(2);
  } else if (board.grid[row][col]->getHighGround1()) {
    if (isVirus()) {
      setName("V" + std::to_string(strength));
    } else {
      setName("D" + std::to_string(strength));
    }
    board.grid[row][col]->appearance = 'z';
    board.grid[row][col]->setOwner(1);
  } else if (board.grid[row][col]->getHighGround2()) {
    if (isVirus()) {
      setName("V" + std::to_string(strength));
    } else {
      setName("D" + std::to_string(strength));
    }
    board.grid[row][col]->appearance = 'Z';
    board.grid[row][col]->setOwner(2);
  }
}

void Link::commonMove(char dir) {
  dir = tolower(dir);

  // Check if link is already downloaded

  if (Downloaded) {
    throw "Link already downloaded by enemy.";
  }
  if (selfDownloaded) {
    throw "Link already downloaded by you, due to firewall.";
  }
  // Ensure the dir char is valid.
  if (dir != 'u' && dir != 'd' && dir != 'l' && dir != 'r')
    throw "Invalid direction given.";

  // Determine the desired location.
  int desiredRow = row;
  int desiredCol = col;
  if (dir == 'u') desiredRow = row - speed;
  if (dir == 'd') desiredRow = row + speed;
  if (dir == 'l') desiredCol = col - speed;
  if (dir == 'r') desiredCol = col + speed;

  // cout << "Current: " << row << " " << col << endl;
  // cout << "Desired: " << desiredRow << " " << desiredCol << endl;

  // Ensure desired location is in bounds.
  bool invalidDirection = false;
  if ((owner == 1 && desiredRow < 0) || (owner == 2 && desiredRow > 7) ||
      (desiredCol > 7) || (desiredCol < 0))
    invalidDirection = true;
  if (invalidDirection) throw "Invalid movement, link goes out of bounds.";

  // Moving across the opponent's edge.

  if ((owner == 1 && desiredRow > 7) || (owner == 2 && desiredRow < 0)) {
    download();
    cout << "Moved across edge, downloaded by opponent" << endl;
    return;
  }

  // Ensure desired location does not move onto one's own server ports.
  if ((owner == 1 && desiredRow == 0 && (desiredCol == 3 || desiredCol == 4)) ||
      (owner == 2 && desiredRow == 7 && (desiredCol == 3 || desiredCol == 4)))
    invalidDirection = true;
  if (invalidDirection)
    throw "Invalid movement, link moves onto your own server port.";

  // Appearance of desired position and current

  char desiredChar = board.grid[desiredRow][desiredCol]->appearance;

  // Ensure desired location is not onto your own link.
  if ((owner == 1 && board.grid[desiredRow][desiredCol]->getOwner() == 1 &&
       desiredChar != 'm' && desiredChar != 'z') ||
      (owner == 2 && board.grid[desiredRow][desiredCol]->getOwner() == 2 &&
       desiredChar != 'w' && desiredChar != 'Z'))
    throw "Invalid movement, link moves onto your own link.";

  // Moving into an opponent's server port.

  if (((desiredRow == 0 && (desiredCol == 3 || desiredCol == 4)) &&
       (owner = 2)) ||
      ((desiredRow == 7 && (desiredCol == 3 || desiredCol == 4)) &&
       (owner = 1))) {
    allCharToLink[board.grid[row][col]->appearance]->download();
    return;
  }

  // Moving onto an opponent firewall

  if ((owner == 1 && board.grid[desiredRow][desiredCol]->getFirewall2()) ||
      (owner == 2 && board.grid[desiredRow][desiredCol]->getFirewall1())) {
    reveal();
    if (allCharToLink[letter]->isVirus()) {
      selfDownload();
      board.grid[row][col]->appearance = '.';
      board.grid[row][col]->setOwner(0);
      movingFromAbility();
      return;
    } else {
      board.grid[desiredRow][desiredCol]->appearance = letter;
      board.grid[desiredRow][desiredCol]->setOwner(owner);
      board.grid[row][col]->appearance = '.';
      board.grid[row][col]->setOwner(0);
      movingFromAbility();
      setLocation(desiredRow, desiredCol);
      return;
    }
  }

  // Moving onto your own firewall.
  if ((owner == 1 && board.grid[desiredRow][desiredCol]->getFirewall1()) ||
      (owner == 2 && board.grid[desiredRow][desiredCol]->getFirewall2())) {
    board.grid[desiredRow][desiredCol]->appearance = letter;
    board.grid[desiredRow][desiredCol]->setOwner(owner);
    board.grid[row][col]->appearance = '.';
    board.grid[row][col]->setOwner(0);
    movingFromAbility();
    setLocation(desiredRow, desiredCol);
  }

  // Moving onto enemy high ground
  if ((owner == 1 && board.grid[desiredRow][desiredCol]->appearance == 'Z') ||
      (owner == 2 && board.grid[desiredRow][desiredCol]->appearance == 'z')) {
    throw "You cannot move onto high ground unless it is occupied by an opponent.";
  }

  // Moving onto your own high ground. This will update the link visually to
  // show its elevated strength due to the high ground.

  if ((owner == 1 && board.grid[desiredRow][desiredCol]->getHighGround1()) ||
      (owner == 2 && board.grid[desiredRow][desiredCol]->getHighGround2())) {
    if (isVirus()) {
      name = "V";
    } else {
      name = "D";
    }
    name += std::to_string(
        allCharToLink[board.grid[row][col]->appearance]->getStrength());
    allCharToLink[board.grid[row][col]->appearance]->setName(name);
    board.grid[row][col]->appearance = '.';
    board.grid[row][col]->setOwner(0);
    board.grid[desiredRow][desiredCol]->appearance = letter;
    board.grid[desiredRow][desiredCol]->setOwner(owner);
    movingFromAbility();
    setLocation(desiredRow, desiredCol);
    return;
  }

  // Moving onto an enemy link. (Battle)

  if (desiredChar != '.' && desiredChar != 'm' && desiredChar != 'w' &&
      board.grid[desiredRow][desiredCol]->getOwner() != 0) {
    cout << "Battle initiated: " << letter << " vs. " << desiredChar << endl;
    int winner = battle(desiredChar);
    if (winner == owner) {
      cout << "Player " << winner << " wins!" << endl;
      allCharToLink[desiredChar]->download();
      board.grid[desiredRow][desiredCol]->appearance = letter;
      board.grid[row][col]->appearance = '.';
      board.grid[row][col]->setOwner(0);
      movingFromAbility();
      setLocation(desiredRow, desiredCol);
      board.grid[desiredRow][desiredCol]->setOwner(winner);
      if (board.grid[desiredRow][desiredCol]->getHighGround1() ||
          board.grid[desiredRow][desiredCol]->getHighGround2()) {
        board.grid[desiredRow][desiredCol]->destroyHighGround();
      }
    } else {
      cout << "Player " << winner << " wins!" << endl;
      download();
    }
    return;
  }

  // Moving onto an empty square.
  if (board.grid[desiredRow][desiredCol]->getOwner() == 0) {
    board.grid[row][col]->appearance = '.';
    board.grid[row][col]->setOwner(0);
    board.grid[desiredRow][desiredCol]->appearance = letter;
    board.grid[desiredRow][desiredCol]->setOwner(owner);
    movingFromAbility();
  }

  // Moving onto an opponent HighGround (only if opponent link is present).

  // Update that link's position if the move was successful.
  setLocation(desiredRow, desiredCol);
}

// ----------------------------------------------------------------------------
// Data class
// ----------------------------------------------------------------------------

Data::Data(int strength_, Board& board_, int owner_, char letter_, bool isData_,
           std::unordered_map<char, std::shared_ptr<Link>>& allCharToLink_)
    : Link(strength_, board_, owner_, letter_, isData_, allCharToLink_) {}

void Data::move(char dir) { commonMove(dir); }

// ----------------------------------------------------------------------------
// Virus class
// ----------------------------------------------------------------------------

Virus::Virus(int strength_, Board& board_, int owner_, char letter_,
             bool isData_,
             std::unordered_map<char, std::shared_ptr<Link>>& allCharToLink_)
    : Link(strength_, board_, owner_, letter_, isData_, allCharToLink_) {}

void Virus::move(char dir) { commonMove(dir); }
