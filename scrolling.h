#ifndef SCROLLING__H
#define SCROLLING__H

#include <vector>
#include <string>
#include "frame.h"
#include "ioManager.h"
#include "vector2f.h"
#include "intro.h"
#include "scrollingline.h"

class Scrolling : public Intro {
public:
  Scrolling();
  void draw() const;
  void update(Uint32);
  void increment() { nextIcon = (nextIcon + 1) % words.size(); }
  void decrement() { 
    nextIcon = (nextIcon + words.size()-1) % words.size(); 
  }
  const string& getIconClicked() const;
private:
  const IOManager& io;
  std::vector<std::string> words; 
  unsigned nextIcon;
  float time;
  std::vector<ScrollingLine> scroller;

  Scrolling(const Scrolling&);
  Scrolling& operator=(const Scrolling&);
};

#endif
