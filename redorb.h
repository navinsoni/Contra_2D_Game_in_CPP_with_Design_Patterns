#ifndef REDORB__H
#define REDORB__H

#include <string>
using std::string;
#include <iostream>

#include "singleframesprite.h"
#include "frame.h"
#include "framefactory.h"
#include "gamedata.h"

class Redorb : public SingleFrameSprite {
public:
  Redorb(const string& n,const string& no, const Vector2f& pos, const Vector2f& vel);
  Redorb(const Redorb& s);
  virtual ~Redorb() { } 
  Redorb& operator=(const Redorb&);
  virtual void update(Uint32 ticks);
private:
  Frame* frame;
};
#endif
