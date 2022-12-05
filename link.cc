#include "link.h"

#include <iostream>
#include <string>

#include "board.h"

using std::cout;
using std::endl;

// ----------------------------------------------------------------------------
// Parent Link class
// ----------------------------------------------------------------------------

Link::Link(int strength_, Board& board_, int owner_, char letter_, bool isData_,
           std::unordered_map<char, Link*>& allCharToLink_)
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
  board.grid[row][col]->setAppearance(letter);
  board.grid[row][col]->setOwner(owner);
}

void Link::setLocation(int row_, int col_) {
  row = row_;
  col = col_;
  board.grid[row][col]->setAppearance(letter);
}

void Link::boost() {
  speed = 2;
}

std::string Link::getName() {
  std::string str = "";
  isData ? str += "D" : str += "V";
  str += std::to_string(getStrength() - '0');
  return str;
}

int Link::getRow() { return row; }

int Link::getCol() { return col; }

char Link::getLetter() { return letter; }

bool Link::getIsHidden() {
  return isHidden;
}

// switches link from data to a virus or vice versa

void Link::linkSwitch() {
  if (isData) {
    isData = false;
  } else {
    isData = true;
  }
}

int Link::getOwner() {
	return owner;
}

// Battle Command

int Link::battle(Link & l2) {
  if (getIsHidden()) { reveal(); }
  if (l2.getIsHidden()) { l2.reveal(); }
  if (getStrength() >= l2.getStrength()) {
    return owner;
  } else {
    return l2.owner;
  }
}

void Link::download() { 
  Downloaded = true; reveal();
  board.grid[row][col]->setAppearance('.');
  board.grid[row][col]->setOwner(0);
  movingFromAbility();
}

void Link::setName(std::string s) {
  name = s;
}

bool Link::isVirus() { return !isData; }

bool Link::isDownloaded() { return Downloaded; }

void Link::reveal() {
  isHidden = false;
}

int Link::getStrength() { 
  if ((owner == 1 && board.grid[row][col]->getFirewall1()) ||
      (owner == 2 && board.grid[row][col]->getFirewall2())) {
    return strength + 1;
  }
  return strength;
}

bool Link::getSelfDownloaded() { return selfDownloaded; }

void Link::selfDownload() { selfDownloaded = true; }

void Link::movingFromAbility() {
  if (board.grid[row][col]->getFirewall1()) {
    board.grid[row][col]->setAppearance('m');
    board.grid[row][col]->setOwner(1);
  } 
  else if (board.grid[row][col]->getFirewall2()) {
    board.grid[row][col]->setAppearance('w');
    board.grid[row][col]->setOwner(2);
  }
  else if (board.grid[row][col]->getHighGround1()) {
    if (isVirus()) {
      setName("V" + std::to_string(strength));
    } else {
      setName("D" + std::to_string(strength));
    }
    board.grid[row][col]->setAppearance('z');
    board.grid[row][col]->setOwner(1);
  }
  else if (board.grid[row][col]->getHighGround2()) {
    if (isVirus()) {
      setName("V" + std::to_string(strength));
    } else {
      setName("D" + std::to_string(strength));
    }
    board.grid[row][col]->setAppearance('Z');
    board.grid[row][col]->setOwner(2);
  }
}

void Link::commonMove(char dir) {
  dir = tolower(dir);

  // Check if link is already downloaded

  if (Downloaded) { throw "Link already downloaded by enemy."; }
  if (selfDownloaded) { throw "Link already downloaded by you, due to firewall."; }
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

  cout << "Current: " << row << " " << col << endl;
  cout << "Desired: " << desiredRow << " " << desiredCol << endl;

  // Ensure desired location is in bounds.
  bool invalidDirection = false;
  if ((owner == 1 && desiredRow < 0) || (owner == 2 && desiredRow > 7) || (desiredCol > 7) || (desiredCol < 0))
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

  char desiredChar = board.grid[desiredRow][desiredCol]->getAppearance();

  // Ensure desired location is not onto your own link.
  if ((owner == 1 && board.grid[desiredRow][desiredCol]->getOwner() == 1 && desiredChar != 'm' && desiredChar != 'z') ||
      (owner == 2 && board.grid[desiredRow][desiredCol]->getOwner() == 2 && desiredChar != 'w' && desiredChar != 'Z'))
    throw "Invalid movement, link moves onto your own link.";

  // Moving into an opponent's server port.

  if (((desiredRow == 0 && (desiredCol == 3 || desiredCol == 4)) && (owner = 2)) || 
      ((desiredRow == 7 && (desiredCol == 3 || desiredCol == 4)) && (owner = 1))) {
    allCharToLink[board.grid[row][col]->getAppearance()]->download();
    return;
  } 


  // Moving onto an opponent firewall

  if ((owner == 1 && board.grid[desiredRow][desiredCol]->getFirewall2()) || 
      (owner == 2 && board.grid[desiredRow][desiredCol]->getFirewall1())) {
    reveal();
    if (allCharToLink[letter]->isVirus()) {
      selfDownload();
      board.grid[row][col]->setAppearance('.');
      board.grid[row][col]->setOwner(0);
      movingFromAbility();
      return;
    } else {
      board.grid[desiredRow][desiredCol]->setAppearance(letter);
      board.grid[desiredRow][desiredCol]->setOwner(owner);
      board.grid[row][col]->setAppearance('.');
      board.grid[row][col]->setOwner(0);
      movingFromAbility();
      setLocation(desiredRow, desiredCol);
      return;
    }
  }

  // Moving onto your own firewall.
  if ((owner == 1 && board.grid[desiredRow][desiredCol]->getFirewall1()) || 
      (owner == 2 && board.grid[desiredRow][desiredCol]->getFirewall2())) {
      board.grid[desiredRow][desiredCol]->setAppearance(letter);
      board.grid[desiredRow][desiredCol]->setOwner(owner);
      board.grid[row][col]->setAppearance('.');
      board.grid[row][col]->setOwner(0);
      movingFromAbility();
      setLocation(desiredRow, desiredCol);
    }

  // Moving onto your own high ground.
  if ((owner == 1 && board.grid[desiredRow][desiredCol]->getHighGround1()) || 
      (owner == 2 && board.grid[desiredRow][desiredCol]->getHighGround2())) {
    if (isVirus()) {
      name = "V";
    } else {
      name = "D";
    }
    name += std::to_string(allCharToLink[board.grid[row][col]->getAppearance()]->getStrength());
    allCharToLink[board.grid[row][col]->getAppearance()]->setName(name);
      board.grid[row][col]->setAppearance('.');
      board.grid[row][col]->setOwner(0);
      board.grid[desiredRow][desiredCol]->setAppearance(letter);
      board.grid[desiredRow][desiredCol]->setOwner(owner);
      movingFromAbility();
      setLocation(desiredRow, desiredCol);
      return;
  }

  // Moving onto an enemy link. (Battle)

  if (desiredChar != '.' && desiredChar!= 'm' && desiredChar != 'w' &&
      board.grid[desiredRow][desiredCol]->getOwner() != 0) {
    cout << "Battle initiated: " << letter << " vs. " << desiredChar << endl;
    int winner = battle(*allCharToLink[desiredChar]);
    if (winner == owner) {
      cout << "Player " << winner << " wins! Downloading enemy link: " << desiredChar << endl;
      allCharToLink[desiredChar]->download();
      board.grid[desiredRow][desiredCol]->setAppearance(letter);
      board.grid[row][col]->setAppearance('.');
      board.grid[row][col]->setOwner(0);
      movingFromAbility();
      setLocation(desiredRow, desiredCol);
      board.grid[desiredRow][desiredCol]->setOwner(winner);
      if (board.grid[desiredRow][desiredCol]->getFirewall1() || board.grid[desiredRow][desiredCol]->getFirewall2()) {
        
      }
    } else {
      cout << "Player " << winner << " wins! Link downloaded by enemy: " << letter << endl;
      download();
    }
    return;
  }
  
  // Moving onto an empty square.
  if (board.grid[desiredRow][desiredCol]->getOwner() == 0) {
    board.grid[row][col]->setAppearance('.');
    board.grid[row][col]->setOwner(0);
    board.grid[desiredRow][desiredCol]->setAppearance(letter);
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
           std::unordered_map<char, Link*>& allCharToLink_)
    : Link(strength_, board_, owner_, letter_, isData_, allCharToLink_) {}

void Data::move(char dir) { commonMove(dir); }


// ----------------------------------------------------------------------------
// Virus class
// ----------------------------------------------------------------------------

Virus::Virus(int strength_, Board& board_, int owner_, char letter_,
             bool isData_, std::unordered_map<char, Link*>& allCharToLink_)
    : Link(strength_, board_, owner_, letter_, isData_, allCharToLink_) {}

void Virus::move(char dir) { commonMove(dir); }
