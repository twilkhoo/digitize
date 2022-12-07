#include "controller.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "player.h"

using std::cerr;
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
                       std::string linksP1, std::string linksP2, bool graphics_)
    : board{std::make_shared<Board>()},
      p1{std::make_shared<Player>(linksP1, abilitiesP1, 1, *board)},
      p2{std::make_shared<Player>(linksP2, abilitiesP2, 2, *board)},
      textObserver{std::make_shared<TextObserver>(board)},
      graphics{graphics_} {
  if (graphics) graphicsObserver = std::make_shared<GraphicsObserver>(board);
}

// ----------------------------------------------------------------------------
//
//  runGame().
//
// ----------------------------------------------------------------------------

void Controller::runGame() {
  string command;
  bool readError = false;
  auto curPlayer = p1;
  bool switchPlayers = false;

  bool useFile = false;
  std::unique_ptr<std::ifstream> fileIn;

  cout << endl;
  cout << "Welcome to..." << endl << endl;
  cout << "██████╗░░█████╗░██╗██╗███╗░░██╗███████╗████████╗\n██╔══██╗██╔══██╗█"
          "█║██║████╗░██║██╔════╝╚══██╔══╝\n██████╔╝███████║██║██║██╔██╗██║████"
          "█╗░░░░░██║░░░\n██╔══██╗██╔══██║██║██║██║╚████║██╔══╝░░░░░██║░░░\n██║"
          "░░██║██║░░██║██║██║██║░╚███║███████╗░░░██║░░░\n╚═╝░░╚═╝╚═╝░░╚═╝╚═╝╚═"
          "╝╚═╝░░╚══╝╚══════╝░░░╚═╝░░░\n";  // AsciiArt from
                                            // https://fsymbols.com/text-art/.

  while (true) {
    printLine();
    if (switchPlayers) {
      system("clear");
      switchPlayers = false;
    }

    // ------------------------------------------------------------------------
    //  Update downloads.
    // ------------------------------------------------------------------------

    p2->resetData();
    p2->resetVirus();
    p1->resetData();
    p1->resetVirus();
    for (char c = 'a'; c <= 'h'; c++) {
      if (Player::allCharToLink[c]->isDownloaded()) {
        if (Player::allCharToLink[c]->isVirus()) {
          p2->increaseVirus();
        } else {
          p2->increaseData();
        }
      }
      if (Player::allCharToLink[c]->isReborn()) {
        if (Player::allCharToLink[c]->isVirus()) {
          p2->increaseVirus();
        } else {
          p2->increaseData();
        }
      }
      if (Player::allCharToLink[c]->getSelfDownloaded()) {
        p1->increaseVirus();
      }
    }
    for (char c = 'A'; c <= 'H'; c++) {
      if (Player::allCharToLink[c]->isDownloaded()) {
        if (Player::allCharToLink[c]->isVirus()) {
          p1->increaseVirus();
        } else {
          p1->increaseData();
        }
      }
      if (Player::allCharToLink[c]->isReborn()) {
        if (Player::allCharToLink[c]->isVirus()) {
          p1->increaseVirus();
        } else {
          p1->increaseData();
        }
      }
      if (Player::allCharToLink[c]->getSelfDownloaded()) {
        p2->increaseVirus();
      }
    }

    // Update abilities
    p1->resetAbilities();
    p2->resetAbilities();
    for (int i = 1; i <= 5; i++) {
      if (p1->intToAbility[i]->getIsUsed()) p1->decreaseAbilities();
      if (p2->intToAbility[i]->getIsUsed()) p2->decreaseAbilities();
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
          << endl;  // AsciiArt from https://fsymbols.com/text-art/.
      cout << "Thanks for playing!\n" << endl;
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
          << endl;  // AsciiArt from https://fsymbols.com/text-art/.
      cout << "Thanks for playing!\n" << endl;
      break;
    }

    cout << "Player " << curPlayer->getPlayerNum() << "'s turn." << endl;
    cout << "Type help to see a list of available commands." << endl;
    callBoard(curPlayer);
    cout << endl;

    // For organization, we will use getline instead of only input stream. So,
    // commands must be entered on the same line. This is made clear in -help.
    if (useFile) {
      getline(*fileIn, command);
    } else {
      getline(std::cin, command);
    }

    removeWhitespace(command);

    // cout << "command given is: " << command << endl;  // Just to debug.
    // cout << endl;

    // ------------------------------------------------------------------------
    //  Move.
    // ------------------------------------------------------------------------
    if (command.substr(0, 4) == "move" || command.substr(0, 4) == "MOVE") {
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
    else if (command == "abilities" || command == "ABILITIES") {
      printLine();
      for (int i = 1; i <= 5; i++) {
        cout << "Ability " << i << ": ";
        cout << curPlayer->intToAbility[i]->getName();
        if (curPlayer->intToAbility[i]->getIsUsed()) cout << " (USED)";
        cout << endl
             << "Description: " << curPlayer->intToAbility[i]->getDescription()
             << endl;
        cout << "Usage: " << curPlayer->intToAbility[i]->getUsage() << endl;
        if (i != 5) cout << endl;
      }
    }

    // ------------------------------------------------------------------------
    //  Ability (use).
    // ------------------------------------------------------------------------
    else if (command.substr(0, 7) == "ability" ||
             command.substr(0, 7) == "ABILITY") {
      cout << endl;
      int abilityNum = command[7] - '0';
      // cout << abilityNum << endl;
      if ((command.length() != 9 && command.length() != 10) ||
          (abilityNum < 1 || abilityNum > 5))
        readError = 1;  // Prevents segmentation faults.
      else {
        string requiredParams =
            curPlayer->intToAbility[abilityNum]->getParams();
        // cout << requiredParams << endl;

        if (requiredParams == "char") {
          char linkChar = (command[8]);
          try {
            curPlayer->intToAbility[abilityNum]->useAbility(
                curPlayer->getPlayerNum(), linkChar);
          } catch (char const *err) {
            cout << err << endl;
            readError = 1;
          }
        }

        if (requiredParams == "charchar") {
          char linkChar1 = (command[8]);
          char linkChar2 = (command[9]);
          try {
          if (command.length() != 10) throw "Please specify two links.";
            curPlayer->intToAbility[abilityNum]->useAbility(
                curPlayer->getPlayerNum(), linkChar1, linkChar2);
          } catch (char const *err) {
            cerr << err << endl;
            readError = 1;
          }
        }

        if (requiredParams == "intint") {
          int row = (command[8]) - 48;
          cout << row << endl;
          int col = (command[9]) - 48;
          cout << col << endl;
          try {
          if (command.length() != 10) throw "Please specify two integers.";
            curPlayer->intToAbility[abilityNum]->useAbility(
                curPlayer->getPlayerNum(), row, col);
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
    else if (command == "board" || command == "BOARD") {
      callBoard(curPlayer);
    }

    // ------------------------------------------------------------------------
    //  Sequence.
    // ------------------------------------------------------------------------
    else if (command.substr(0, 8) == "sequence" ||
             command.substr(0, 8) == "SEQUENCE") {
      string file = command.substr(8, command.length() - 8);
      cout << file << endl;
      // Check if file exists and is readable.
      auto infile = std::make_unique<std::ifstream>(file);
      if (!infile->good()) {
        cerr << "No valid sequence file provided." << endl;
        readError = 1;
      } else {
        cout << "all good" << endl;
        useFile = true;
        fileIn = std::move(infile);
      }
    }

    // ------------------------------------------------------------------------
    //  Help.
    // ------------------------------------------------------------------------
    else if (command == "help" || command == "HELP") {
      printLine();
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
      cout << "ability <N>\nUses the ability card with ID N. Some abilities "
              "require extra information to be entered, type abilities to "
              "learn the correct usage of all of your abilities.\n"
           << endl;
      cout << "board\nDisplays the board along with your links, and the links "
              "that have been revealed by the opponent.\n"
           << endl;
      cout << "sequence <file>\nExecutes the sequence of commands found in "
              "file, then exits the game.\n"
           << endl;
      cout << "quit\nExits the game." << endl;
    }

    // ------------------------------------------------------------------------
    //  Quit.
    // ------------------------------------------------------------------------
    else if (command == "quit" || command == "QUIT" ||
             (!useFile && std::cin.eof()) || (useFile && fileIn->eof())) {
      cout << "Ending abruptly, " << endl << endl;

      cout << "████████╗██╗███████╗  ░██████╗░░█████╗░███╗░░░███╗███████╗\n╚══█"
              "█╔══╝██║██╔════╝  ██╔════╝░██╔══██╗████╗░████║██╔════╝\n░░░██║░░"
              "░██║█████╗░░  ██║░░██╗░███████║██╔████╔██║█████╗░░\n░░░██║░░░██║"
              "██╔══╝░░  ██║░░╚██╗██╔══██║██║╚██╔╝██║██╔══╝░░\n░░░██║░░░██║████"
              "███╗  ╚██████╔╝██║░░██║██║░╚═╝░██║███████╗\n░░░╚═╝░░░╚═╝╚══════╝"
              "  ░╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝╚══════╝\n"
           << endl;  // AsciiArt from https://fsymbols.com/text-art/.

      cout << "Thanks for playing!\n" << endl;
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
  cout << endl
       << "----------------------------------------------------------------\n"
       << endl;
}

void Controller::callBoard(std::shared_ptr<Player> curPlayer) {
  cout << endl;
  // Summary for player 1- textObserver.
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

  // Summary for player 2- textObserver.
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

  // Player 1 downloaded links summary- graphicsObserver.
  std::ostringstream p1DownloadedStream;
  p1DownloadedStream << "Downloaded: " << p1->getDataCount() << "D, "
                     << p1->getVirusCount() << "V";
  const string p1Downloaded{p1DownloadedStream.str()};

  // Player 2 downloaded links summary- graphicsObserver.
  std::ostringstream p2DownloadedStream;
  p2DownloadedStream << "Downloaded: " << p2->getDataCount() << "D, "
                     << p2->getVirusCount() << "V";
  const string p2Downloaded{p2DownloadedStream.str()};

  // Map to get link names from link characters- graphicsObserver.
  std::unordered_map<char, string> allLinkNames;
  std::unordered_map<char, Link *>::iterator it;

  for (auto it = Player::allCharToLink.begin();
       it != Player::allCharToLink.end(); it++) {
    string idStr;
    if ((curPlayer->getPlayerNum() == 1 && it->second->getOwner() == 2 &&
         it->second->getIsHidden()) ||
        (curPlayer->getPlayerNum() == 2 && it->second->getOwner() == 1 &&
         it->second->getIsHidden()))
      idStr = "?";
    else
      idStr = it->second->getName();
    allLinkNames.insert(std::pair<char, string>{it->first, idStr});
  }

  board->render(p1Summary, p2Summary, p1Downloaded, p2Downloaded, allLinkNames,
                std::to_string(p1->getAbilitiesCount()),
                std::to_string(p2->getAbilitiesCount()));
}
