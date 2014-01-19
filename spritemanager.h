#include <SDL.h>
#include <iostream>
#include <string>
#include <list>

#include "framefactory.h"
#include "viewport.h"
#include "sprite.h"
#include "player.h"
#include "redorb.h"
#include "enemystationary.h"
#include "boxtarget.h"
#include "bigbullet.h"
#include "flame.h"
#include "frame.h"
#include "enemyFinal1.h"
class SpriteManager {
public:
  SpriteManager ();
  ~SpriteManager ();
  void draw();
  void update(Uint32 ticks);
  void setControls(uint8_t c) { controls = c; }
  bool getStatusPlayer() { return playerAlive; }
  bool getStatusEnemy() { return enemyAlive; }
  void trackSprite();

private:
  Sprite* player;
  bool playerAlive;
  bool enemyAlive;
  std::list<Sprite*> enemy;
  Viewport& viewport;
  std::list<Sprite*> finalenemy;

  uint8_t controls;
  unsigned track;
  std::string intToString(int n);

  SpriteManager(const SpriteManager&);
  SpriteManager& operator=(const SpriteManager&);
};
