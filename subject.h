#ifndef SUBJECT_H
#define SUBJECT_H

#include <string>
#include <unordered_map>
#include <vector>

class Observer;

class Subject {
  std::vector<Observer*> observers;

 public:
  void attach(Observer* o);
  void detach(Observer* o);
  void notifyObservers(const std::string& p1Summary,
                       const std::string& p2Summary,
                       const std::string& p1Downloaded,
                       const std::string& p2Downloaded,
                       std::unordered_map<char, std::string>& allLinkNames,
                       const std::string& p1Abilities,
                       const std::string& p2Abilities);
  virtual char getState(int row, int col) const = 0;
  virtual ~Subject() = default;
};

#endif
