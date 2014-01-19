#ifndef FLAME__H
#define FLAME__H

#include <string>
using std::string;
#include <iostream>

#include "singleframesprite.h"
#include "frame.h"
#include "framefactory.h"
#include "gamedata.h"

class Flame : public SingleFrameSprite {
public:
  Flame(const string& n,const string& no);
  Flame(const Flame& s);
  virtual ~Flame() { } 
  Flame& operator=(const Flame&);
  virtual void update(Uint32 ticks);
private:
  Frame* frame;
  int Xi;
};
#endif
