#include <iostream>
#include <cmath>
#include "sprite.h"
#include "gamedata.h"

Sprite::Sprite(const string& n,const string& no, const Vector2f& pos, const Vector2f& vel) :
  Drawable( pos, vel, 
            Vector2f(Gamedata::getInstance()->getXmlInt(n+no+"MaxXspeed"),
                    Gamedata::getInstance()->getXmlInt(n+no+"MaxYspeed"))
  ),
  name(n),
  number(no),
  controls(0x00),
  location(Vector2f(0,0)),
  direction(true)
{ }

Sprite::Sprite(const Sprite& s) :
  Drawable(s.getPosition(), s.getVelocity(), s.getMaxVelocity()), 
  name( s.getName() ),
  number(s.number),
  controls(s.controls),
  location(s.location),
  direction(s.direction)
  { }

Sprite& Sprite::operator=(const Sprite& rhs) {
  setName( rhs.getName() );
  setPosition(rhs.getPosition());
  setVelocity(rhs.getVelocity());
  setMaxVelocity(rhs.getMaxVelocity());
  number = rhs.number;
  controls = rhs.controls;
  location = rhs.location;
  direction = rhs.direction;
  return *this;
}

int Sprite::getDistance(const Sprite *obj) const { 
  return hypot(X()-obj->X(), Y()-obj->Y());
}

int Sprite::getAngle(const Sprite *obj) const { 
  return (static_cast<int>((atan2(Y()-obj->Y(),X()-obj->X())*360/(2*3.14))+360)%360);
}

void Sprite::Location(const Sprite *obj){ 
	Location(Vector2f(hypot(X()-obj->X(), Y()-obj->Y()),static_cast<int>((atan2(Y()-obj->Y(),X()-obj->X())*360/(2*3.14))+360)%360));
}
