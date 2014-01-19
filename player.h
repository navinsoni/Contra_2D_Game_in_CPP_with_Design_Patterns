#ifndef PLAYER__H
#define PLAYER__H

#include <string>
using std::string;
#include <iostream>

#include "multiframesprite.h"
#include "frame.h"
#include "mapx.h"
#include "framefactory.h"
#include "gamedata.h"
#include "viewport.h"

class Player : public MultiFrameSprite {
public:
  Player(const string& n,const string& no);
  Player(const Player& s);
  virtual ~Player() { } 
  Player& operator=(const Player&);
  virtual void update(Uint32 ticks);
  void setUp(bool u) { upp = u; }
  bool getUp() const { return upp; }
  void setDown(bool d) { downn = d; }
  bool getDown() const { return downn; }
  void setPower(string& p) { power = p; }
  const string& getPower() const { return power; }
  void Jump(bool j) { jumpjump = j; }
  bool Jump() { return jumpjump; }

  float Xi() const { return position[0]; }
  void Xi(float x) { position[0] = x; }
  float Yi() const { return position[1]; }
  void Yi(float y) { position[1] = y; }


private:
  bool upp;
  bool downn;
  bool jumpjump;
  string power;
  string offset;
  Vector2f bulletDirection;
  Vector2f position;
  float dt;
  int strength;
  int df;
  unsigned currentPoint;
  bool swim;
  std::vector<Frame*> rwalk;
  std::vector<Frame*> rwalkswim;
  std::vector<Frame*> lwalk;
  std::vector<Frame*> lwalkswim;
  std::vector<Frame*> rwalkfire;
  std::vector<Frame*> rwalkfireswim;
  std::vector<Frame*> lwalkfire;
  std::vector<Frame*> lwalkfireswim;
  std::vector<Frame*> rjump;
  std::vector<Frame*> ljump;
  std::vector<Frame*> rgundown;
  std::vector<Frame*> lgundown;
  std::vector<Frame*> rgunup;
  std::vector<Frame*> rgunupswim;
  std::vector<Frame*> lgunup;
  std::vector<Frame*> lgunupswim;
  std::vector<Frame*> rdown;
  std::vector<Frame*> ldown;
  std::vector<Frame*> downswim;
  std::vector<Frame*> rup;
  std::vector<Frame*> rupswim;
  std::vector<Frame*> lup;
  std::vector<Frame*> lupswim;
  std::vector<Frame*> rnormal;
  std::vector<Frame*> lnormal;
  bool Swim() const { return swim; }
  void Swim(const bool s) { swim = s; }
  void jump(Uint32 ticks, bool& jumpjump);
  void walk(Uint32 ticks);
  void changeX();
  void normal(Uint32 ticks);
  void up(Uint32 ticks);
  void down(Uint32 ticks);
  void fire(string& power,string& offset);
};
#endif
