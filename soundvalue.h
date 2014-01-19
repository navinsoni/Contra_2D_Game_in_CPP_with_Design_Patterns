#ifndef SOUNDVALUE__H
#define SOUNDVALUE__H


#include <vector>
#include <string>
#include "frame.h"
#include "ioManager.h"
#include "vector2f.h"
#include "intro.h"
#include "sound.h"

class SoundValue : public Intro {
public:
  SoundValue();
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

  SoundValue(const SoundValue&);
  SoundValue& operator=(const SoundValue&);
};

#endif
