#include "subject.h"
#include "observer.h"
#include <string>

void Subject::attach(Observer *o) { observers.emplace_back(o); }

void Subject::detach(Observer *o) {
  for (auto it = observers.begin(); it != observers.end(); ++it) {
    if (*it == o) {
      observers.erase(it);
      break;
    }
  }
}

void Subject::notifyObservers(const std::string& p1Summary, const std::string& p2Summary) {
  for (auto ob : observers) ob->notify(p1Summary, p2Summary);
}
