#include <iostream>
#include <cmath>
#include "multiframesprite.h"

void MultiFrameSprite::advanceFrame(Uint32 ticks, float change, std::string action){
	float ms = change/(Gamedata::getInstance()->getXmlInt(getName() + action + "NumberOfFrames")-1);
	dt += ticks;
	int df = dt/ms;
	dt -= df*ms;
	currFrame = (currFrame+df)%Gamedata::getInstance()->getXmlInt(getName() + action +"NumberOfFrames");
}

MultiFrameSprite::MultiFrameSprite(const string& n,const string& no, const Vector2f& pos, const Vector2f& vel) :
  Sprite(n,no,pos,vel),
  dt(0),
  frame(),
  currFrame(0),
  diffLDraw(0)
{ }

MultiFrameSprite::MultiFrameSprite(const MultiFrameSprite& s) :
  Sprite(s.getName(),s.getNumber(),s.getPosition(),s.getVelocity()),
  dt(s.dt),
  frame(s.frame), 
  currFrame(s.currFrame),
  diffLDraw(s.diffLDraw)
  { }

MultiFrameSprite& MultiFrameSprite::operator=(const MultiFrameSprite& rhs) {
  setName( rhs.getName() );
  setPosition(rhs.getPosition());
  setVelocity(rhs.getVelocity());
  setMaxVelocity(rhs.getMaxVelocity());
  Location(rhs.Location());
  currFrame = rhs.currFrame;
  dt = rhs.dt;
  diffLDraw = rhs.diffLDraw;
  setDirection(rhs.getDirection());
  frame = rhs.frame;
  return *this;
}

void MultiFrameSprite::draw() const { 
  Uint32 x = static_cast<Uint32>(X()+diffLDraw);
  Uint32 y = static_cast<Uint32>(Y());
  frame[currFrame]->draw(x, y - frame[currFrame]->getHeight()); 
}

unsigned MultiFrameSprite::getPixel(Uint32 i, Uint32 j) const {
  Uint32 *pixels = static_cast<Uint32 *>(frame[currFrame]->getSurface()->pixels);
  return pixels[ ( j * frame[currFrame]->getWidth() ) + i ];
}


int MultiFrameSprite::getDistance(const MultiFrameSprite *obj) const { 
  return hypot(X()-obj->X(), Y()-obj->Y());
}
