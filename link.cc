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

std::string Link::getName() {
  std::string str = "";
  isData ? str += "D" : str += "V";
  str += std::to_string(strength - '0');
  return str;
}

bool Link::getIsHidden() {
  return isHidden;
}

void Link::commonMove(char dir) {
  dir = tolower(dir);

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
  if (desiredCol < 0 || desiredCol > 7) invalidDirection = true;
  if ((owner == 1 && desiredRow < 0) || (owner == 2 && desiredRow > 7))
    invalidDirection = true;
  if (invalidDirection) throw "Invalid movement, link goes out of bounds.";

  // Ensure desired location does not move onto one's own server ports.
  if ((owner == 1 && desiredRow == 0 && (desiredCol == 3 || desiredCol == 4)) ||
      (owner == 2 && desiredRow == 7 && (desiredCol == 3 || desiredCol == 4)))
    invalidDirection = true;
  if (invalidDirection)
    throw "Invalid movement, link moves onto your own server port.";

  // Ensure desired location is not onto your own link.
  if ((owner == 1 && board.grid[desiredRow][desiredCol]->getOwner() == 1) ||
      (owner == 2 && board.grid[desiredRow][desiredCol]->getOwner() == 2))
    throw "Invalid movement, link moves onto your own link.";

  // Moving onto an empty square.
  if (board.grid[desiredRow][desiredCol]->getOwner() == 0) {
    board.grid[row][col]->setAppearance('.');
    board.grid[row][col]->setOwner(0);
    board.grid[desiredRow][desiredCol]->setAppearance(letter);
    board.grid[desiredRow][desiredCol]->setOwner(1);
  }

  // Moving across the opponent's edge.

  // Moving into an opponent's server port.

  // Moving into an opponent firewall.

  // Moving onto an opponent HighGround (only if opponent link is present).
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
