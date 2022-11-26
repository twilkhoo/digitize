#include "controller.h"

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

Controller::Controller(){};

void Controller::runGame() {
  string command;
  bool readError = false;

  while (true) {
    cin >> command;
    cout << "command given is: " << command << endl;  // Just to debug.

    if (command == "move") {
      // For this, we additionally consume a link (from a-h) and a direction
      // (u/d/l/r), and must account for different and invalid letter cases.
      cout << "move link" << endl;
    }

    else if (command == "abilities") {
      cout << "display abilities for current player" << endl;
    }

    else if (command == "ability") {
      // For this, we will need to account for the fact that different abilities
      // will take in different parameters, so first check for what type of
      // ability the id is, then proceed.
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
      cout << "There was an error reading your command, type help to get a "
              "list of valid commands."
           << endl;
      readError = false;
    }
  }
}
