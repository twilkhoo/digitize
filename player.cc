#include "player.h"

#include <iostream>
#include <string>
#include <unordered_map>

#include "ability.h"
#include "link.h"

// using std::cout;
// using std::endl;
using std::string;

bool Player::deletedCharMap = false;
std::unordered_map<char, Link*> Player::allCharToLink;

Player::Player(string linkString, string abilityString, int playerNum_,
               Board& board_)
    : playerNum{playerNum_}, board{board_} {
  // cout << "Creating Player " << playerNum << endl;

  // Create the specified ability classes for the player.
  // cout << "Creating abilities" << endl;
  int len = (int)abilityString.length();
  for (int i = 1; i <= len; i++) {
    if (abilityString[i - 1] == 'L') {
      LinkBoost* linkBoostObject = new LinkBoost(i, allCharToLink, board);
      // cout << "Creating a linkBoostObject: " << linkBoostObject << endl;
      // cout << "Mapping: " << i << " => " << linkBoostObject << endl;
      intToAbility.insert(std::pair<int, Ability*>{i, linkBoostObject});
    }

    else if (abilityString[i - 1] == 'F') {
      Firewall* firewallObject = new Firewall(i, allCharToLink, board);
      // cout << "Creating a firewallObject: " << firewallObject << endl;
      // cout << "Mapping: " << i << " => " << firewallObject << endl;
      intToAbility.insert(std::pair<int, Ability*>{i, firewallObject});
    }

    else if (abilityString[i - 1] == 'D') {
      Download* downloadObject = new Download(i, allCharToLink, board);
      // cout << "Creating a downloadObject: " << downloadObject << endl;
      // cout << "Mapping: " << i << " => " << downloadObject << endl;
      intToAbility.insert(std::pair<int, Ability*>{i, downloadObject});
    }

    else if (abilityString[i - 1] == 'S') {
      Scan* scanObject = new Scan(i, allCharToLink, board);
      // cout << "Creating a scanObject: " << scanObject << endl;
      // cout << "Mapping: " << i << " => " << scanObject << endl;
      intToAbility.insert(std::pair<int, Ability*>{i, scanObject});
    }

    else if (abilityString[i - 1] == 'P') {
      Polarize* polarizeObject = new Polarize(i, allCharToLink, board);
      // cout << "Creating a polarizeObject: " << polarizeObject << endl;
      // cout << "Mapping: " << i << " => " << polarizeObject << endl;
      intToAbility.insert(std::pair<int, Ability*>{i, polarizeObject});
    }

    else if (abilityString[i - 1] == 'R') {
      LinkReborn* linkRebornObject = new LinkReborn(i, allCharToLink, board);
      // cout << "Creating a linkRebornObject: " << linkRebornObject << endl;
      // cout << "Mapping: " << i << " => " << linkRebornObject << endl;
      intToAbility.insert(std::pair<int, Ability*>{i, linkRebornObject});
    }

    else if (abilityString[i - 1] == 'H') {
      HighGround* highGroundObject = new HighGround(i, allCharToLink, board);
      // cout << "Creating a highGroundObject: " << highGroundObject << endl;
      // cout << "Mapping: " << i << " => " << highGroundObject << endl;
      intToAbility.insert(std::pair<int, Ability*>{i, highGroundObject});
    }

    else if (abilityString[i - 1] == 'O') {
      Portal* portalObject = new Portal(i, allCharToLink, board);
      // cout << "Creating a portalObject: " << portalObject << endl;
      // cout << "Mapping: " << i << " => " << portalObject << endl;
      intToAbility.insert(std::pair<int, Ability*>{i, portalObject});
    }
  }

  // cout << endl;

  // Create the specified link classes for the player.
  // cout << "Creating link classes" << endl;
  char curLetter = 'a';
  if (playerNum == 2) curLetter = 'A';
  len = (int)linkString.length();
  for (int i = 0; i < len; i += 2) {
    if (linkString[i] == 'V') {  // Create a virus object.
      Virus* virusObject = new Virus(linkString[i + 1], board, playerNum,
                                     curLetter, false, allCharToLink);
      // cout << "Creating virus: " << virusObject << endl;
      // cout << "Mapping: " << curLetter << " => " << virusObject << endl;
      allCharToLink.insert(std::pair<char, Link*>{curLetter, virusObject});
    } else {  // Create a data object.
      Data* dataObject = new Data(linkString[i + 1], board, playerNum,
                                  curLetter, true, allCharToLink);
      // cout << "Creating data: " << dataObject << endl;
      // cout << "Mapping: " << curLetter << " => " << dataObject << endl;
      allCharToLink.insert(std::pair<char, Link*>{curLetter, dataObject});
    }
    curLetter++;
  }
}

void Player::increaseData() { dataCount++; }

void Player::increaseVirus() { virusCount++; }

void Player::resetData() { dataCount = 0; }

void Player::resetVirus() { virusCount = 0; }

Player::~Player() {
  for (std::unordered_map<int, Ability*>::iterator it = intToAbility.begin();
       it != intToAbility.end(); ++it) {
    delete it->second;
  }

  if (!deletedCharMap) {
    for (std::unordered_map<char, Link*>::iterator it = allCharToLink.begin();
         it != allCharToLink.end(); ++it) {
      delete it->second;
    }
    deletedCharMap = true;
  }
}

int Player::getPlayerNum() { return playerNum; }
int Player::getDataCount() { return dataCount; }
int Player::getVirusCount() { return virusCount; }
int Player::getAbilitiesCount() { return abilitiesCount; }
