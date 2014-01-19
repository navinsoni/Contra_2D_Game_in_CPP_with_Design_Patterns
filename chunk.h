#include <iostream>
#include "sprite.h"
#include "gamedata.h"
#include "singleframesprite.h"

class Chunk : public SingleFrameSprite {
public:
  explicit Chunk(
    const Vector2f& pos, const Vector2f vel, 
    const string& name, const Frame* fm) :
    SingleFrameSprite(name,"",pos, vel), 
    distance(0), 
    maxDistance(Gamedata::getInstance()->getXmlInt(name+"Distance")), 
    tooFar(false)
  { setFrame(fm);}
  virtual void update(Uint32 ticks);
  bool goneTooFar() const { return tooFar; }
  void reset() {
    tooFar = false;
    distance = 0;
  }
private:
  float distance;
  float maxDistance;
  bool tooFar;
};
