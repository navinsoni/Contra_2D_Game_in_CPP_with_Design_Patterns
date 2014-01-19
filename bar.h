#ifndef BAR__H
#define BAR__H

#include <string>
using std::string;
#include <iostream>

#include "singleframesprite.h"
#include "frame.h"
#include "framefactory.h"
#include "aaline.h"
#include "ioManager.h"
#include "gamedata.h"

class Bar : public SingleFrameSprite {
public:
  Bar(const string& n,const string& no);
  Bar(const Bar& s);
  virtual ~Bar() { } 
  Bar& operator=(const Bar&);
  virtual void draw() const;
  virtual void update(Uint32 ticks);
private:
  int value;
  std::vector<Frame*> frame;
  SDL_Surface* screen;
};
#endif
