#include "subject.h"

#include <string>
#include <unordered_map>

#include "observer.h"

void Subject::attach(Observer* o) { observers.emplace_back(o); }

void Subject::detach(Observer* o) {
  for (auto it = observers.begin(); it != observers.end(); ++it) {
    if (*it == o) {
      observers.erase(it);
      break;
    }
  }
}

void Subject::notifyObservers(
    const std::string& p1Summary, const std::string& p2Summary,
    const std::string& p1Downloaded, const std::string& p2Downloaded,
    std::unordered_map<char, std::string>& allLinkNames,
    const std::string& p1Abilities, const std::string& p2Abilities) {
  for (auto ob : observers)
    ob->notify(p1Summary, p2Summary, p1Downloaded, p2Downloaded, allLinkNames,
               p1Abilities, p2Abilities);
}
