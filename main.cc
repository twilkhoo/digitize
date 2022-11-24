#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;

const string abilities = "LFDSP";
const vector<string> links{"V1", "V2", "V3", "V4", "D1", "D2", "D3", "D4"};

std::ostream& operator<<(std::ostream& out, const vector<string>& vec);
const string randomized_links(int player_seed);

int main(int argc, char* argv[]) {
  bool graphics = false;
  string abilities_p1 = "LFDSP";
  string abilities_p2 = "LFDSP";
  string links_p1 = randomized_links(1);
  string links_p2 = randomized_links(2);

  for (int i = 1; i < argc; ++i) {
    string arg = argv[i];

    if (arg == "-graphics") {
      graphics = true;
    }
  }

  if (graphics) cout << "Graphics enabled" << endl;
  cout << abilities_p1 << endl;
  cout << abilities_p2 << endl;
  cout << links_p1 << endl;
  cout << links_p2 << endl;
}

std::ostream& operator<<(std::ostream& out, const vector<string>& vec) {
  if (vec.size() == 0) return out;
  for (long unsigned int i = 0; i < vec.size() - 1; i++) {
    out << vec[i] << ", ";
  }
  out << vec.back();
  return out;
}

const string randomized_links(int player_seed) {
  player_seed == 1 ? srand((unsigned)time(0)) : srand((unsigned)time(0) + 1);

  vector<string> new_links(links);
  int random_int;
  string link_string = "";
  for (int i = 0; i < 8; i++) {
    random_int = (rand() % new_links.size());
    link_string += new_links[random_int] + " ";
    new_links.erase(new_links.begin() + random_int);
  }

  return link_string;
}
