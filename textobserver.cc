#include "textobserver.h"

TextObserver::TextObserver(Board* subject_) : subject{subject_} {
  subject->attach(this);
}

TextObserver::~TextObserver() { subject->detach(this); }

void TextObserver::notify(const std::string& p1Summary,
                          const std::string& p2Summary) {
  out << p1Summary << std::endl;

  for (int i = 0; i < subject->getLength(); i++) out << "=";
  out << std::endl;

  for (int i = 0; i < subject->getLength(); i++) {
    for (int j = 0; j < subject->getLength(); j++) {
      out << subject->getState(i, j);
    }
    out << std::endl;
  }

  for (int i = 0; i < subject->getLength(); i++) out << "=";
  out << std::endl;

  out << p2Summary << std::endl;
}
