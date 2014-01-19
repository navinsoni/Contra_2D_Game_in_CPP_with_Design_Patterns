#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>

#include "ioManager.h"
#include "clock.h"
#include "framefactory.h"
#include "world.h"
#include "spritemanager.h"
#include "sound.h"
#include "name.h"
#include "scrolling.h"
#include "menu.h"
#include "intro.h"
#include "introduction.h"
#include "wiimote.h"

class Manager {
public:
  Manager ();
  ~Manager ();
  void play();

private:
  const bool env;
  const IOManager& io;
  Clock& clock;
  uint16_t controls;

  SDL_Surface *screen;
  World world;
  World world1;
  World world2;
  SpriteManager spriteManager;
  std::vector<Intro*> t1;
  Introduction intro;
  Introduction menu;

  void help();
  void draw();
  void update(Uint32 ticks);
  Manager(const Manager&);
  Manager& operator=(const Manager&);
};
