#ifndef ENEMYSTATIONARY__H
#define ENEMYSTATIONARY__H

#include <string>
#include <iostream>

#include "multiframesprite.h"
#include "frame.h"
#include "framefactory.h"
#include "bullets.h"
#include "bullet.h"

using std::string;

class EnemyStationary : public MultiFrameSprite {
public:
  EnemyStationary(const string& n,const string& no);
  EnemyStationary(const EnemyStationary& s);
  virtual ~EnemyStationary() { } 
  EnemyStationary& operator=(const EnemyStationary&);
  virtual void update(Uint32 ticks);
  void setUp(bool u) { upp = u; }
  bool getUp() const { return upp; }
  void setDown(bool d) { downn = d; }
  bool getDown() const { return downn; }

private:
  bool upp;
  bool downn;
  float dt;
  string power;
  string offset;
  Vector2f bulletDirection;
  std::vector<Frame*> rgundown;
  std::vector<Frame*> lgundown;
  std::vector<Frame*> rgunup;
  std::vector<Frame*> lgunup;
  std::vector<Frame*> rnormal;
  std::vector<Frame*> lnormal;
  void normal(Uint32 ticks);
  void up(Uint32 ticks);
  void down(Uint32 ticks);
  void fire(string& power,string& offset);
};
#endif
