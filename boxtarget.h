#ifndef BOXTARGET__H
#define BOXTARGET__H

#include <string>
#include <iostream>

#include "multiframesprite.h"
#include "frame.h"
#include "framefactory.h"
#include "bullets.h"
#include "bullet.h"

using std::string;

class BoxTarget : public MultiFrameSprite {
public:
  BoxTarget(const string& n,const string& no);
  BoxTarget(const BoxTarget& s);
  virtual ~BoxTarget() { } 
  BoxTarget& operator=(const BoxTarget&);
  virtual void update(Uint32 ticks);
  void setUp(bool u) { upp = u; }
  bool getUp() const { return upp; }
  void setDown(bool d) { downn = d; }
  bool getDown() const { return downn; }

private:
  bool upp;
  bool downn;
  float dt;
  int strength;
  string power;
  string offset;
  Vector2f bulletDirection;
  std::vector<Frame*> up;
  std::vector<Frame*> rup30;
  std::vector<Frame*> lup30;
  std::vector<Frame*> rup60;
  std::vector<Frame*> lup60;
  std::vector<Frame*> rnormal;
  std::vector<Frame*> lnormal;
  std::vector<Frame*> rdown60;
  std::vector<Frame*> ldown60;
  std::vector<Frame*> rdown30;
  std::vector<Frame*> ldown30;
  std::vector<Frame*> down;
  void normal(Uint32 ticks);
  void fire(string& power,string& offset);
};
#endif
