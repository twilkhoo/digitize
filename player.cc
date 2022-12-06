#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

#include "player.h"
#include "ability.h"
#include "link.h"

// using std::cout;
// using std::endl;
using std::string;

bool Player::deletedCharMap = false;
std::unordered_map<char, std::shared_ptr<Link>> Player::allCharToLink;

Player::Player(string linkString, string abilityString, int playerNum_,
               Board& board_)
    : playerNum{playerNum_}, board{board_} {

  // Create the specified ability classes for the player.
  int len = (int)abilityString.length();
  for (int i = 1; i <= len; i++) {
    if (abilityString[i - 1] == 'L') {
      auto linkBoostObject = std::make_shared<LinkBoost>(i, allCharToLink, board);
      intToAbility.insert(std::pair<int, std::shared_ptr<Ability>>{i, linkBoostObject});
    }

    else if (abilityString[i - 1] == 'F') {
      auto firewallObject = std::make_shared<Firewall>(i, allCharToLink, board);
      intToAbility.insert(std::pair<int, std::shared_ptr<Ability>>{i, firewallObject});
    }

    else if (abilityString[i - 1] == 'D') {
      auto downloadObject = std::make_shared<Download>(i, allCharToLink, board);
      intToAbility.insert(std::pair<int, std::shared_ptr<Ability>>{i, downloadObject});
    }

    else if (abilityString[i - 1] == 'S') {
      auto scanObject = std::make_shared<Scan>(i, allCharToLink, board);
      intToAbility.insert(std::pair<int, std::shared_ptr<Ability>>{i, scanObject});
    }

    else if (abilityString[i - 1] == 'P') {
      auto polarizeObject = std::make_shared<Polarize>(i, allCharToLink, board);
      intToAbility.insert(std::pair<int, std::shared_ptr<Ability>>{i, polarizeObject});
    }

    else if (abilityString[i - 1] == 'R') {
      auto linkRebornObject = std::make_shared<LinkReborn>(i, allCharToLink, board);
      intToAbility.insert(std::pair<int, std::shared_ptr<Ability>>{i, linkRebornObject});
    }

    else if (abilityString[i - 1] == 'H') {
      auto highGroundObject = std::make_shared<HighGround>(i, allCharToLink, board);
      intToAbility.insert(std::pair<int, std::shared_ptr<Ability>>{i, highGroundObject});
    }

    else if (abilityString[i - 1] == 'O') {
      auto portalObject = std::make_shared<Portal>(i, allCharToLink, board);
      intToAbility.insert(std::pair<int, std::shared_ptr<Ability>>{i, portalObject});
    }
  }

  // Create the specified link classes for the player.
  // cout << "Creating link classes" << endl;
  char curLetter = 'a';
  if (playerNum == 2) curLetter = 'A';
  len = (int)linkString.length();
  for (int i = 0; i < len; i += 2) {
    if (linkString[i] == 'V') {  // Create a virus object.
      auto virusObject = std::make_shared<Virus>(linkString[i + 1], board, playerNum,
                                     curLetter, false, allCharToLink);
      allCharToLink.insert(std::pair<char, std::shared_ptr<Link>>{curLetter, virusObject});
    } else {  // Create a data object.
      auto dataObject = std::make_shared<Data>(linkString[i + 1], board, playerNum,
                                  curLetter, true, allCharToLink);
      allCharToLink.insert(std::pair<char, std::shared_ptr<Link>>{curLetter, dataObject});
    }
    curLetter++;
  }
}

void Player::increaseData() { dataCount++; }

void Player::increaseVirus() { virusCount++; }

void Player::resetData() { dataCount = 0; }

void Player::resetVirus() { virusCount = 0; }

void Player::decreaseAbilities() { abilitiesCount--; }

void Player::resetAbilities() { abilitiesCount = 5; }

int Player::getPlayerNum() { return playerNum; }
int Player::getDataCount() { return dataCount; }
int Player::getVirusCount() { return virusCount; }
int Player::getAbilitiesCount() { return abilitiesCount; }
