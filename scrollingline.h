#ifndef SCROLLINGLINE__H
#define SCROLLINGLINE__H

#include <vector>
#include <string>
#include "frame.h"
#include "ioManager.h"
#include "vector2f.h"
#include "intro.h"

class ScrollingLine : public Intro {
public:
  ScrollingLine(std::string w);
  ScrollingLine(const ScrollingLine&);
  ScrollingLine& operator=(const ScrollingLine&);
  void draw() const;
  void update(Uint32);
private:
  std::string words; 
  Vector2f position;

};

#endif
