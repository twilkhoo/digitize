#include "controller.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

#include "player.h"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;

void removeWhitespace(string &str);
void printLine();

// ----------------------------------------------------------------------------
//
//  Constructor.
//
// ----------------------------------------------------------------------------

Controller::Controller(std::string abilitiesP1, std::string abilitiesP2,
                       std::string linksP1, std::string linksP2, bool graphics)
    : board{new Board()},
      p1{new Player{linksP1, abilitiesP1, 1, *board}},
      p2{new Player{linksP2, abilitiesP2, 2, *board}},
      textObserver{new TextObserver(board)} {
  if (graphics) {
    cout << "Graphics enabled." << endl;
  }
}

// ----------------------------------------------------------------------------
//
//  Destructor.
//
// ----------------------------------------------------------------------------

Controller::~Controller() {
  delete textObserver;
  delete board;
  delete p1;
  delete p2;
}

// ----------------------------------------------------------------------------
//
//  runGame().
//
// ----------------------------------------------------------------------------

void Controller::runGame() {
  string command;
  bool readError = false;
  Player *curPlayer = p1;
  bool switchPlayers = false;

  cout << endl;
  cout << "Welcome to..." << endl << endl;
  cout << "██████╗░░█████╗░██╗██╗███╗░░██╗███████╗████████╗\n██╔══██╗██╔══██╗█"
          "█║██║████╗░██║██╔════╝╚══██╔══╝\n██████╔╝███████║██║██║██╔██╗██║████"
          "█╗░░░░░██║░░░\n██╔══██╗██╔══██║██║██║██║╚████║██╔══╝░░░░░██║░░░\n██║"
          "░░██║██║░░██║██║██║██║░╚███║███████╗░░░██║░░░\n╚═╝░░╚═╝╚═╝░░╚═╝╚═╝╚═"
          "╝╚═╝░░╚══╝╚══════╝░░░╚═╝░░░\n"
       << endl; // AsciiArt from https://fsymbols.com/text-art/.

  while (true) {
    printLine();
    if (switchPlayers) {
      system("clear");
      switchPlayers = false;
    }

    // ------------------------------------------------------------------------
    //  Check for wins.
    // ------------------------------------------------------------------------

    if (p1->getDataCount() == 4 || p2->getVirusCount() == 4) {  // P1 wins.
      cout << "Congratulations..." << endl << endl;

      cout
          << "██████╗░░░███╗░░  ░██╗░░░░░░░██╗██╗███╗░░██╗░██████╗\n██╔══██╗░██"
             "██║░░  ░██║░░██╗░░██║██║████╗░██║██╔════╝\n██████╔╝██╔██║░░  ░╚██"
             "╗████╗██╔╝██║██╔██╗██║╚█████╗░\n██╔═══╝░╚═╝██║░░  ░░████╔═████║░█"
             "█║██║╚████║░╚═══██╗\n██║░░░░░███████╗  ░░╚██╔╝░╚██╔╝░██║██║░╚███║"
             "██████╔╝\n╚═╝░░░░░╚══════╝  ░░░╚═╝░░░╚═╝░░╚═╝╚═╝░░╚══╝╚═════╝░\n"
          << endl; // AsciiArt from https://fsymbols.com/text-art/.
      cout << "Thanks for playing!" << endl;
      break;
    }

    else if (p2->getDataCount() == 4 || p1->getVirusCount() == 4) {  // P2 wins.
      cout << "Congratulations..." << endl;

      cout
          << "██████╗░██████╗░  ░██╗░░░░░░░██╗██╗███╗░░██╗░██████╗\n██╔══██╗╚══"
             "══██╗  ░██║░░██╗░░██║██║████╗░██║██╔════╝\n██████╔╝░░███╔═╝  ░╚██"
             "╗████╗██╔╝██║██╔██╗██║╚█████╗░\n██╔═══╝░██╔══╝░░  ░░████╔═████║░█"
             "█║██║╚████║░╚═══██╗\n██║░░░░░███████╗  ░░╚██╔╝░╚██╔╝░██║██║░╚███║"
             "██████╔╝\n╚═╝░░░░░╚══════╝  ░░░╚═╝░░░╚═╝░░╚═╝╚═╝░░╚══╝╚═════╝░\n"
          << endl; // AsciiArt from https://fsymbols.com/text-art/.
      cout << "Thanks for playing!" << endl;
      break;
    }

    cout << "Player " << curPlayer->getPlayerNum() << "'s turn." << endl;
    cout << "Type help to see a list of available commands.\n" << endl;

    // For organization, we will use getline instead of only cin. So, commands
    // must be entered all on the same line. This is made clear in -help.
    getline(cin, command);
    removeWhitespace(command);

    // cout << "command given is: " << command << endl;  // Just to debug.
    // cout << endl;

    // ------------------------------------------------------------------------
    //  Move.
    // ------------------------------------------------------------------------
    if (command.substr(0, 4) == "move") {
      cout << endl;
      char link = command[4];
      char dir = command[5];
      if (command.length() != 6) {
        readError = true;
      } else if ((curPlayer == p1 && !(link >= 'a' && link <= 'h')) ||
                 (curPlayer == p2 && !(link >= 'A' && link <= 'H'))) {
        cerr << "You can only move your own link." << endl;
        readError = true;  // Prevents segmentation faults.
      } else {
        try {
          // Implement code here for move, which throws an exception (string) if
          // something goes wrong and the move is not completed.

          curPlayer->allCharToLink[link]->move(dir);

          cout << "move link " << link << " in dir " << dir << endl;
          curPlayer == p1 ? curPlayer = p2 : curPlayer = p1;  // Switch players.
          switchPlayers = true;
        } catch (char const *err) {
          cerr << err << endl;
          readError = true;
        }
      }
    }

    // ------------------------------------------------------------------------
    //  Abilities (list all).
    // ------------------------------------------------------------------------
    else if (command == "abilities") {
      cout << endl;
      for (int i = 1; i <= 5; i++) {
        cout << "Ability " << i << ": ";
        cout << curPlayer->intToAbility[i]->getName();
        if (curPlayer->intToAbility[i]->getIsUsed()) cout << "USED";
        cout << endl
             << "Description: " << curPlayer->intToAbility[i]->getDescription()
             << endl;
        cout << "Usage: " << curPlayer->intToAbility[i]->getUsage() << endl;
        cout << endl;
      }
    }

    // ------------------------------------------------------------------------
    //  Ability (use).
    // ------------------------------------------------------------------------
    else if (command.substr(0, 7) == "ability") {
      cout << endl;
      int abilityNum = command[7] - '0';
      cout << abilityNum << endl;
      if ((command.length() != 9 && command.length() != 10) ||
          (abilityNum < 1 || abilityNum > 5))
        readError = 1;  // Prevents segmentation faults.
      else {
        string requiredParams =
            curPlayer->intToAbility[abilityNum]->getParams();
        cout << requiredParams << endl;

        if (requiredParams == "char") {
          char linkChar = (command[8]);
          try {
            curPlayer->intToAbility[abilityNum]->useAbility(linkChar);
          } catch (char const *err) {
            cout << err << endl;
            readError = 1;
          }
        }

        if (requiredParams == "charchar") {
          char linkChar1 = (command[8]);
          char linkChar2 = (command[9]);
          try {
            curPlayer->intToAbility[abilityNum]->useAbility(linkChar1,
                                                            linkChar2);
          } catch (char const *err) {
            cerr << err << endl;
            readError = 1;
          }
        }

        if (requiredParams == "intint") {
          int row = (command[8]) - 'A';
          int col = (command[9]) - 'A';
          try {
            curPlayer->intToAbility[abilityNum]->useAbility(row, col);
          } catch (char const *err) {
            cerr << err << endl;
            readError = 1;
          }
        }
      }
    }

    // ------------------------------------------------------------------------
    //  Board.
    // ------------------------------------------------------------------------
    else if (command == "board") {
      cout << endl;
      std::ostringstream p1SummaryStream;
      p1SummaryStream << "Player 1:" << endl
                      << "Downloaded: " << p1->getDataCount() << "D, "
                      << p1->getVirusCount() << "V" << endl
                      << "Abilities: " << p1->getAbilitiesCount() << endl;

      char curChar = 'a';
      for (int i = 0; i < 8; i++) {
        p1SummaryStream << curChar << ": ";
        if (curPlayer->getPlayerNum() == 2 &&
            Player::allCharToLink[curChar]->getIsHidden()) {
          p1SummaryStream << "? ";
        } else {
          p1SummaryStream << Player::allCharToLink[curChar]->getName() << " ";
        }
        if (i == 3) p1SummaryStream << endl;
        curChar++;
      }
      const string p1Summary{p1SummaryStream.str()};

      std::ostringstream p2SummaryStream;
      p2SummaryStream << "Player 2:" << endl
                      << "Downloaded: " << p2->getDataCount() << "D, "
                      << p2->getVirusCount() << "V" << endl
                      << "Abilities: " << p2->getAbilitiesCount() << endl;

      curChar = 'A';
      for (int i = 0; i < 8; i++) {
        p2SummaryStream << curChar << ": ";
        if (curPlayer->getPlayerNum() == 1 &&
            Player::allCharToLink[curChar]->getIsHidden()) {
          p2SummaryStream << "? ";
        } else {
          p2SummaryStream << Player::allCharToLink[curChar]->getName() << " ";
        }
        if (i == 3) p2SummaryStream << endl;
        curChar++;
      }
      const string p2Summary{p2SummaryStream.str()};

      board->render(p1Summary, p2Summary);
    }

    // ------------------------------------------------------------------------
    //  Sequence.
    // ------------------------------------------------------------------------
    else if (command == "sequence") {
      // For this, consume a string which is a filename and execute the commands
      // in that file.
      cout << "sequence" << endl;
    }

    // ------------------------------------------------------------------------
    //  Help.
    // ------------------------------------------------------------------------
    else if (command == "help") {
      cout << endl;
      cout << "All of the following commands must be entered on the same line. "
              "Pressing enter signifies using a command.\n"
           << endl;
      cout << "move <L> <dir>\nMoves the link L (where this can be any link "
              "you control) in the direction dir, which can be any one of u, "
              "d, l, r.\n"
           << endl;
      cout << "abilities\nDisplays the ability cards you have, with an ID "
              "(from 1-5), whether or not it has been used, and it's usage.\n"
           << endl;
      cout << "move <N>\nUses the ability card with ID N. Some abilities "
              "require extra information to be entered, type abilities to "
              "learn the correct usage of all of your abilities.\n"
           << endl;
      cout << "board\nDisplays the board along with your links, and the links "
              "that have been revealed by the opponent.\n"
           << endl;
      cout << "sequence <file>\nExecutes the sequence of commands found in "
              "file, then exits the game.\n"
           << endl;
      cout << "quit\nExits the game.\n" << endl;
    }

    // ------------------------------------------------------------------------
    //  Quit.
    // ------------------------------------------------------------------------
    else if (command == "quit" || cin.eof()) {
      cout << "Ending abruptly, " << endl << endl;

      cout << "████████╗██╗███████╗  ░██████╗░░█████╗░███╗░░░███╗███████╗\n╚══█"
              "█╔══╝██║██╔════╝  ██╔════╝░██╔══██╗████╗░████║██╔════╝\n░░░██║░░"
              "░██║█████╗░░  ██║░░██╗░███████║██╔████╔██║█████╗░░\n░░░██║░░░██║"
              "██╔══╝░░  ██║░░╚██╗██╔══██║██║╚██╔╝██║██╔══╝░░\n░░░██║░░░██║████"
              "███╗  ╚██████╔╝██║░░██║██║░╚═╝░██║███████╗\n░░░╚═╝░░░╚═╝╚══════╝"
              "  ░╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝╚══════╝\n"
           << endl; // AsciiArt from https://fsymbols.com/text-art/.

      cout << "Thanks for playing!" << endl;
      break;
    }

    // ------------------------------------------------------------------------
    //  Error in reading.
    // ------------------------------------------------------------------------
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

void printLine() {
  cout << "----------------------------------------------------------------\n";
}
