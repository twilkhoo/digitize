#include "player.h"

#include <iostream>
#include <string>
#include <unordered_map>

#include "ability.h"
#include "link.h"
using std::cout;
using std::endl;
using std::string;

Player::Player(string linkString, string abilityString, int playerNum_)
    : playerNum{playerNum_} {
  cout << "Creating Player " << playerNum << endl;

  // Create the specified ability classes for the player.
  cout << "Creating abilities" << endl;
  int len = (int)abilityString.length();
  for (int i = 1; i <= len; i++) {
    if (abilityString[i - 1] == 'L') {
      LinkBoost* linkBoostObject = new LinkBoost(i);
      cout << "Creating a linkBoostObject: " << linkBoostObject << endl;
      cout << "Mapping: " << i << " => " << linkBoostObject << endl;
      intToAbility.insert(std::pair<int, Ability*>{i, linkBoostObject});
    }

    else if (abilityString[i - 1] == 'F') {
      Firewall* firewallObject = new Firewall(i);
      cout << "Creating a firewallObject: " << firewallObject << endl;
      cout << "Mapping: " << i << " => " << firewallObject << endl;
      intToAbility.insert(std::pair<int, Ability*>{i, firewallObject});
    }

    else if (abilityString[i - 1] == 'D') {
      Download* downloadObject = new Download(i);
      cout << "Creating a downloadObject: " << downloadObject << endl;
      cout << "Mapping: " << i << " => " << downloadObject << endl;
      intToAbility.insert(std::pair<int, Ability*>{i, downloadObject});
    }

    else if (abilityString[i - 1] == 'S') {
      Scan* scanObject = new Scan(i);
      cout << "Creating a scanObject: " << scanObject << endl;
      cout << "Mapping: " << i << " => " << scanObject << endl;
      intToAbility.insert(std::pair<int, Ability*>{i, scanObject});
    }

    else if (abilityString[i - 1] == 'P') {
      Polarize* polarizeObject = new Polarize(i);
      cout << "Creating a polarizeObject: " << polarizeObject << endl;
      cout << "Mapping: " << i << " => " << polarizeObject << endl;
      intToAbility.insert(std::pair<int, Ability*>{i, polarizeObject});
    }

    else if (abilityString[i - 1] == 'R') {
      LinkReborn* linkRebornObject = new LinkReborn(i);
      cout << "Creating a linkRebornObject: " << linkRebornObject << endl;
      cout << "Mapping: " << i << " => " << linkRebornObject << endl;
      intToAbility.insert(std::pair<int, Ability*>{i, linkRebornObject});
    }

    else if (abilityString[i - 1] == 'H') {
      HighGround* highGroundObject = new HighGround(i);
      cout << "Creating a highGroundObject: " << highGroundObject << endl;
      cout << "Mapping: " << i << " => " << highGroundObject << endl;
      intToAbility.insert(std::pair<int, Ability*>{i, highGroundObject});
    }

    else if (abilityString[i - 1] == 'O') {
      Portal* portalObject = new Portal(i);
      cout << "Creating a portalObject: " << portalObject << endl;
      cout << "Mapping: " << i << " => " << portalObject << endl;
      intToAbility.insert(std::pair<int, Ability*>{i, portalObject});
    }
  }

  cout << endl;

  // Create the specified link classes for the player.
  cout << "Creating link classes" << endl;
  char curLetter = 'a';
  if (playerNum == 2) curLetter = 'A';
  len = (int)linkString.length();
  for (int i = 0; i < len; i += 2) {
    if (linkString[i] == 'V') {  // Create a virus object.
      Virus* virusObject = new Virus(linkString[i + 1]);
      cout << "Creating virus: " << virusObject << endl;
      cout << "Mapping: " << curLetter << " => " << virusObject << endl;
      charToLink.insert(std::pair<char, Link*>{curLetter, virusObject});
    } else {  // Create a data object.
      Data* dataObject = new Data(linkString[i + 1]);
      cout << "Creating data: " << dataObject << endl;
      cout << "Mapping: " << curLetter << " => " << dataObject << endl;
      charToLink.insert(std::pair<char, Link*>{curLetter, dataObject});
    }
    curLetter++;
  }

  if (playerNum == 1) {
    Ability::setCharToLinkP1(&charToLink);
  } else {
    Ability::setCharToLinkP2(&charToLink);
  }
  cout << "----------------------------------------------------------" << endl;
}

Player::~Player() {
  for (std::unordered_map<int, Ability*>::iterator it = intToAbility.begin();
       it != intToAbility.end(); ++it) {
    delete it->second;
  }

  for (std::unordered_map<char, Link*>::iterator it = charToLink.begin();
       it != charToLink.end(); ++it) {
    delete it->second;
  }
}

int Player::getPlayerNum() { return playerNum; }
