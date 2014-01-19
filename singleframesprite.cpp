#include <iostream>
#include <cmath>
#include "singleframesprite.h"
#include "viewport.h"


SingleFrameSprite::SingleFrameSprite(const string& n,const string& no, const Vector2f& pos, const Vector2f& vel) :
  Sprite(n,no,pos,vel),
  frame()
{ }

SingleFrameSprite::SingleFrameSprite(const SingleFrameSprite& s) :
  Sprite(s.getName(),s.getNumber(),s.getPosition(),s.getVelocity()), 
  frame(s.frame)
  { }

SingleFrameSprite& SingleFrameSprite::operator=(const SingleFrameSprite& rhs) {
  setName( rhs.getName() );
  setPosition(rhs.getPosition());
  setVelocity(rhs.getVelocity());
  setMaxVelocity(rhs.getMaxVelocity());
  Location(rhs.Location());
  setDirection(rhs.getDirection());
  frame = rhs.frame;
  return *this;
}

void SingleFrameSprite::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frame->draw(x, y - frame->getHeight()); 
}


unsigned SingleFrameSprite::getPixel(Uint32 i, Uint32 j) const { 
  Uint32 *pixels = static_cast<Uint32 *>(frame->getSurface()->pixels);
  return pixels[ ( j * frame->getWidth() ) + i ];
}

