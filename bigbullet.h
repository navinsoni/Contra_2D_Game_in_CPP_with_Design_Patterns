#ifndef BIGBULLET__H
#define BIGBULLET__H

#include <string>
#include <iostream>

#include "multiframesprite.h"
#include "frame.h"
#include "framefactory.h"
#include "bullets.h"
#include "bullet.h"

using std::string;

class BigBullet : public MultiFrameSprite {
public:
  BigBullet(const string& n,const string& no);
  BigBullet(const BigBullet& s);
  virtual ~BigBullet() { } 
  BigBullet& operator=(const BigBullet&);
  virtual void update(Uint32 ticks);

private:
  float dt;
  int strength;
  string power;
  string offset;
  Vector2f bulletDirection;
  std::vector<Frame*> rnormal;
  std::vector<Frame*> lnormal;
  void normal(Uint32 ticks);
  void fire(string& power,string& offset);
};
#endif
