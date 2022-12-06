#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "controller.h"

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
using std::vector;

const string randomizedLinks(int playerSeed);
const bool validateAbilityString(const string &str);
const bool validateLinkString(const string &str);
const void toUpper(string &str);

const string abilities = "LFDSPRHO";      // All possible abilities.
const string defaultAbilities = "LFDSP";  // Default abilities.
const vector<string> links{"V1", "V2", "V3", "V4", "D1",
                           "D2", "D3", "D4"};  // All possible links/positions.

int main(int argc, char *argv[]) {
  // --------------------------------------------------------------------------
  //
  //  Command line argument setup.
  //
  // --------------------------------------------------------------------------

  bool graphics = false;
  string abilitiesP1 = defaultAbilities;
  string abilitiesP2 = defaultAbilities;
  string linksP1 = randomizedLinks(1);
  string linksP2 = randomizedLinks(2);

  for (int i = 1; i < argc; ++i) {
    string arg = argv[i];

    // ------------------------------------------------------------------------
    // Check for graphics.
    // ------------------------------------------------------------------------
    if (arg == "-graphics") graphics = true;

    // ------------------------------------------------------------------------
    // Check for placement.
    // ------------------------------------------------------------------------
    if ((arg == "-link1" || arg == "-link2")) {
      // Check if there is a following cl-arg.
      if (argc <= i + 1) {
        cerr << "No placement file provided for " << arg << endl;
        continue;
      }

      // Check if file exists and is readable.
      std::ifstream infile{argv[i + 1]};
      if (!infile.good()) {
        cerr << "No valid placement file provided for " << arg << endl;
        continue;
      }

      // Get the contents of the given file into an uppercase string.
      string curLink;
      string linkString;
      while (true) {
        infile >> curLink;
        if (infile.fail()) break;
        linkString += curLink;
      }
      toUpper(linkString);

      // Validate the string using a hashmap.
      if (!validateLinkString(linkString)) {
        cerr << "No valid placement file provided for " << arg << endl;
        continue;
      }
      arg == "-link1" ? linksP1 = linkString : linksP2 = linkString;
    }

    // ------------------------------------------------------------------------
    // Check for abilities.
    // ------------------------------------------------------------------------
    if ((arg == "-ability1" || arg == "-ability2")) {
      // Check if there is a following cl-arg.
      if (argc <= i + 1) {
        cerr << "No ability string provided for " << arg << endl;
        continue;
      }

      // Get the string and normalize it (convert to uppercase)
      string abilityString = argv[i + 1];
      toUpper(abilityString);

      // Validate the string using a hashmap.
      if (!validateAbilityString(abilityString)) {
        cerr << "Invalid ability string provided for " << arg << endl;
        continue;
      }
      arg == "-ability1" ? abilitiesP1 = abilityString
                         : abilitiesP2 = abilityString;
    }
  }

  system("clear");

  // if (graphics) cout << "Graphics enabled" << endl;
  // cout << abilitiesP1 << endl;
  // cout << abilitiesP2 << endl;
  // cout << linksP1 << endl;
  // cout << linksP2 << endl;
  cout << "----------------------------------------------------------------"
       << endl;

  // --------------------------------------------------------------------------
  //
  //  In-game interactions.
  //
  // --------------------------------------------------------------------------

  auto game = std::make_unique<Controller>(
      abilitiesP1, abilitiesP2, linksP1, linksP2, graphics);
  game->runGame();
}

// ----------------------------------------------------------------------------
//
//  Helper Functions.
//
// ----------------------------------------------------------------------------

// randomizedLinks returns a string representing the eight starting links in a
// random order.
const string randomizedLinks(int playerSeed) {
  playerSeed == 1 ? srand((unsigned)time(0)) : srand((unsigned)time(0) + 1);

  vector<string> myLinks(links);
  int randomInt;
  string linkString = "";
  for (int i = 0; i < 8; i++) {
    randomInt = (rand() % myLinks.size());
    linkString += myLinks[randomInt];
    myLinks.erase(myLinks.begin() + randomInt);
  }

  return linkString;
}

// validateAbilityString determines whether or not a string represents an
// ability string, in which every character must be one of the ability letters,
// appearing no more than twice.
const bool validateAbilityString(const string &str) {
  unordered_map<char, int> abilitiesCount;
  for (auto ability : abilities) {
    abilitiesCount.insert(std::pair<char, int>{ability, 0});
  }

  for (auto c : str) {
    if (!abilitiesCount.count(c)) return false;  // Key does not exist in map.
    abilitiesCount[c] += 1;
    if (abilitiesCount[c] > 2) return false;
  }
  return true;
}

// validateLinkString determines whether or not a string represents a link
// string, in which every string of length two must represent a unique link.
const bool validateLinkString(const string &str) {
  unordered_map<string, int> linksCount;
  for (auto link : links) {
    linksCount.insert(std::pair<string, int>{link, 0});
  }

  int linkStrLength = (int)str.size();
  for (int i = 0; i < linkStrLength; i += 2) {
    if (i == linkStrLength - 1) return false;

    string subStr = str.substr(i, 2);
    if (!linksCount.count(subStr)) return false;  // Key does not exist in map.
    linksCount[subStr] += 1;
    if (linksCount[subStr] > 1) return false;
  }

  return true;
}

// toUpper modifies the given string by making lower case letters uppercase.
const void toUpper(string &str) {
  int strLength = (int)str.length();
  for (int i = 0; i < strLength; i++) {
    if (str[i] >= 'a' && str[i] <= 'z') str[i] -= 'a' - 'A';
  }
}
