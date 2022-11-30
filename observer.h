#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <string>

class Observer {
 public:
  virtual void notify(const std::string& p1Summary, const std::string& p2Summary) = 0;
  virtual ~Observer() = default;
};
#endif
