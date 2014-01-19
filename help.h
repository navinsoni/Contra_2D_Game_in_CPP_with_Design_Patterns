#ifndef HELP__H
#define HELP__H

#include <vector>
#include <string>
#include "frame.h"
#include "ioManager.h"
#include "vector2f.h"
#include "intro.h"
#include "sound.h"

class Help : public Intro {
public:
  Help();
  void draw() const;
  void update(Uint32);
private:
  const IOManager& io;
  std::vector<std::string> words; 
  Vector2f position;
  Vector2f space;

  Help(const Help&);
  Help& operator=(const Help&);
};

#endif
