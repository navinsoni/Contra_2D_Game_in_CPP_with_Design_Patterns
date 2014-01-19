#ifndef NAME__H
#define NAME__H

#include <string>
using std::string;
#include <iostream>

#include "singleframesprite.h"
#include "frame.h"
#include "framefactory.h"
#include "gamedata.h"

class Name : public SingleFrameSprite {
public:
  Name(const string& n,const string& no);
  Name(const Name& s);
  virtual ~Name() { } 
  Name& operator=(const Name&);
  virtual void update(Uint32 ticks);
private:
  Frame* frame;
  int Xi;
};
#endif
