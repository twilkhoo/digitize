#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <string>
#include <unordered_map>

class Observer {
 public:
  virtual void notify(const std::string& p1Summary,
                      const std::string& p2Summary,
                      const std::string& p1Downloaded,
                      const std::string& p2Downloaded,
                      std::unordered_map<char, std::string>& allLinkNames,
                      const std::string& p1Abilities,
                      const std::string& p2Abilities) = 0;
  virtual ~Observer() = default;
};
#endif
