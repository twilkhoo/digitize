#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <string>

class Observer;

class Subject {
  std::vector<Observer*> observers;
 public:
  void attach(Observer *o);
  void detach(Observer *o);
  void notifyObservers(const std::string& p1Summary, const std::string& p2Summary);
  virtual char getState(int row, int col) const = 0;
  virtual ~Subject() = default;
};

#endif
