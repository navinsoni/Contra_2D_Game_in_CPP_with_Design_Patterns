#ifndef ENEMYFINAL1__H
#define ENEMYFINAL1__H

#include <string>
#include <iostream>
#include <math.h>

#include "multiframesprite.h"
#include "frame.h"
#include "framefactory.h"
#include "bullets.h"
#include "bullet.h"

using std::string;

class EnemyFinal1 : public MultiFrameSprite {
public:
  EnemyFinal1(const string& n,const string& no);
  EnemyFinal1(const EnemyFinal1& s);
  virtual ~EnemyFinal1() { } 
  EnemyFinal1& operator=(const EnemyFinal1&);
  void draw() const;
  virtual void update(Uint32 ticks);

private:
  int strength;
  float dt;
  Vector2f bulletDirection;
  string power;
  string offset;
  std::vector<Frame*> rnormal;
  Frame* enemyFrame;
  void fire(string& power,string& offset);
};
#endif
