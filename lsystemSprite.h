#include "singleframesprite.h"
#include "lsystem.h"

class LsystemSprite : public SingleFrameSprite {
public:
  LsystemSprite(const string& n,const string& no);
  ~LsystemSprite();
  virtual void update(Uint32 ticks);
private:
  const Gamedata* gdata;
  LSystem lsystem;
  SDL_Surface * const lsysSurface;
  Frame * const lsysFrame;
  int currentColor;
  Uint32 strokeColor;

  void changeColor();
  void changeLength();
  LsystemSprite(const LsystemSprite&);
  LsystemSprite& operator=(const LsystemSprite&);
};
