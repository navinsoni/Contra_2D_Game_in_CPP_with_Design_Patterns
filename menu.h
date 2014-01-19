#ifndef MENU__H
#define MENU__H

#include <vector>
#include <string>
#include "frame.h"
#include "ioManager.h"
#include "vector2f.h"
#include "intro.h"
#include "introduction.h"
#include "soundvalue.h"
#include "musicvalue.h"
#include "help.h" 
#include "wiimenu.h" 

class Menu : public Intro {
public:
  Menu();
  void draw() const;
  void update(Uint32);
  void lightOn() { click = 1; }
  void lightOff() { click = 0; }
  void increment() { nextIcon = (nextIcon + 1) % words.size(); }
  void decrement() { 
    nextIcon = (nextIcon + words.size()-1) % words.size(); 
  }
  const string& getIconClicked() const;
private:
  const IOManager& io;
  std::vector<std::string> words; 
  Vector2f position;
  Vector2f space;
  unsigned nextIcon;
  unsigned click;
  bool keypressed;
  std::vector<Intro*> t1;
  Introduction sound;
  Introduction music;
  Introduction help;
  Introduction wii;

  Menu(const Menu&);
  Menu& operator=(const Menu&);
};

#endif
