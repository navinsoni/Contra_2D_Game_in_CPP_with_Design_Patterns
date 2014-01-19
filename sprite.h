#ifndef SPRITE__H
#define SPRITE__H

#include <string>
using std::string;
#include <iostream>

#include "drawable.h"
#include "vector2f.h"
#include "frame.h"
#include "intro.h"
#include "framefactory.h"

class Sprite : public Drawable, public Intro {
public:
  Sprite(const string& n,const string& no, const Vector2f& pos, const Vector2f& vel);
  Sprite(const Sprite& s);
  virtual ~Sprite() { } 
  Sprite& operator=(const Sprite&);
  const string& getName() const { return name; }
  void setName(const string& n) { name = n; }
  const string& getNumber() const { return number; }
  void setNumber(const string& n) { number = n; }
  void setControls(uint8_t c) { controls = c; }
  uint8_t getControls() { return controls; }
  void Location(Vector2f l) { location = l; }
  Vector2f Location() const { return location; }
  void Location(const Sprite*);
  

  virtual const Frame* getFrame() const = 0;
  virtual void setFrame(const Frame* f) = 0;
  virtual void draw() const = 0;
  virtual void update(Uint32 ticks) = 0;
  virtual unsigned getPixel(Uint32, Uint32) const = 0;

 virtual Vector2f getCenter() const = 0; 

  void setDirection(bool d) { direction = d; }
  bool getDirection() const { return direction; }
  int getDistance(const Sprite*) const;
  int getAngle(const Sprite*) const;


private:
  string name;
  string number;
  uint8_t controls;
  Vector2f location;
  bool direction;
};
#endif
