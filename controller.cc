#include "controller.h"

#include <algorithm>
#include <iostream>
#include <string>

#include "player.h"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;

Controller::Controller(std::string abilitiesP1, std::string abilitiesP2,
                       std::string linksP1, std::string linksP2)
    : p1{new Player{linksP1, abilitiesP1, 1}},
      p2{new Player{linksP2, abilitiesP2, 2}} {}

Controller::~Controller() {
  delete p1;
  delete p2;
}

void removeWhitespace(string &str);

void Controller::runGame() {
  string command;
  bool readError = false;
  Player *curPlayer = p1;

  while (true) {
    cout << "curPlayer: " << curPlayer->getPlayerNum() << endl;

    // For organization, we will use getline instead of only cin. So, commands
    // must be entered all on the same line. This is made clear in -help.
    getline(cin, command);
    removeWhitespace(command);

    cout << "command given is: " << command << endl;  // Just to debug.

    cout << endl;

    if (command.substr(0, 4) == "move") {
      char link = command[4];
      char dir = command[5];
      if (command.length() != 6) {
        readError = true;
      } else {
        try {
          // Implement code here for move, which throws an exception (string) if
          // something goes wrong and the move is not completed.
          cout << "move link " << link << " in dir " << dir << endl;
          curPlayer == p1 ? curPlayer = p2 : curPlayer = p1;  // Switch players.
        } catch (string err) {
          cerr << err << endl;
          readError = true;
        }
      }
    }

    else if (command == "abilities") {
      for (int i = 1; i <= 5; i++) {
        cout << "Ability " << i << ": ";
        cout << curPlayer->intToAbility[i]->getName() << endl;
        cout << "Description: " << curPlayer->intToAbility[i]->getDescription()
             << endl;
        cout << "Usage: " << curPlayer->intToAbility[i]->getUsage() << endl;
        if (curPlayer->intToAbility[i]->getIsUsed()) cout << "USED" << endl;
        cout << endl;
      }

      cout << "display abilities for current player" << endl;
    }

    else if (command.substr(0, 7) == "ability") {
      int abilityNum = command[7] - '0';
      cout << abilityNum << endl;

      if ((command.length() != 9 && command.length() != 10) ||
          (abilityNum < 1 || abilityNum > 5))
        readError = 1;
      else {
        string requiredParams =
            curPlayer->intToAbility[abilityNum]->getParams();

        cout << requiredParams << endl;

        if (requiredParams == "char") {
          char linkChar = (command[8]);
          try {
            int playerNum = curPlayer->getPlayerNum();
            curPlayer->intToAbility[abilityNum]->useAbility(playerNum,
                                                            linkChar);
          } catch (string err) {
            cout << err << endl;
          }
        }

        if (requiredParams == "charchar") {
          char linkChar1 = (command[8]);
          char linkChar2 = (command[9]);
          try {
            int playerNum = curPlayer->getPlayerNum();
            curPlayer->intToAbility[abilityNum]->useAbility(
                playerNum, linkChar1, linkChar2);
          } catch (string err) {
            cerr << err << endl;
            readError = 1;
          }
        }

        if (requiredParams == "intint") {
          int int1 = (command[8]) - 'A';
          int int2 = (command[9]) - 'A';
          try {
            int playerNum = curPlayer->getPlayerNum();
            curPlayer->intToAbility[abilityNum]->useAbility(playerNum, int1,
                                                            int2);
          } catch (string err) {
            cerr << err << endl;
            readError = 1;
          }
        }
      }

      cout << "use ability" << endl;
    }

    else if (command == "board") {
      cout << "display board" << endl;
    }

    else if (command == "sequence") {
      // For this, consume a string which is a filename and execute the commands
      // in that file.
      cout << "sequence" << endl;
    }

    else if (command == "help") {
      cout << "help lol" << endl;
    }

    else if (command == "quit" || cin.eof()) {
      cout << "Ending abruptly, draw." << endl;
      break;
    }

    else {
      readError = true;
    }

    if (readError) {
      cerr << "There was an error reading your command, type help to get a "
              "list of valid commands."
           << endl;
      readError = false;
    }
  }
}

void removeWhitespace(string &str) {
  str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
}
