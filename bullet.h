#ifndef BULLET__H
#define BULLET__H

#include <string>
using std::string;
#include <iostream>

#include "singleframesprite.h"
#include "frame.h"
#include "framefactory.h"
#include "gamedata.h"

class Bullet : public SingleFrameSprite {
public:
  Bullet(const string& n,const string& no, const Vector2f& pos, const Vector2f& vel);
  Bullet(const Bullet& s);
  virtual ~Bullet() { } 
  Bullet& operator=(const Bullet&);
  virtual void update(Uint32 ticks);
private:
  Frame* frame;
  float time;
};
#endif
