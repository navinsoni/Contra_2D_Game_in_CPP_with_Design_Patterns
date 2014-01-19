#include <iostream>
#include <cmath>
#include "redorb.h"

Redorb::Redorb(const string& n,const string& no, const Vector2f& pos, const Vector2f& vel) :
  SingleFrameSprite(n,no,pos,vel),
  frame(FrameFactory::getInstance().getFrame(n,"")[0])
  { setFrame(frame); }

Redorb::Redorb(const Redorb& s) :
  SingleFrameSprite(s.getName(),s.getNumber(),s.getPosition(),s.getVelocity()),
  frame(s.frame)
  { }

Redorb& Redorb::operator=(const Redorb& rhs) {
  setName( rhs.getName() );
  setPosition(rhs.getPosition());
  setVelocity(rhs.getVelocity());
  setMaxVelocity(rhs.getMaxVelocity());
  setDirection(rhs.getDirection());
  setFrame(rhs.getFrame());
  frame = rhs.frame;
  return *this;
}

void Redorb::update(Uint32 ticks) { 
  float incr = velocityY() * static_cast<float>(ticks) * 0.001;
  Y( Y()+incr );
  float height = static_cast<float>(frame->getHeight());
  if ( Y() < 0) {
    velocityY(0);
  }
  if ( Y() > Gamedata::getInstance()->getXmlInt("viewHeight")-height) {
    velocityY(0);
  }

  incr = velocityX() * static_cast<float>(ticks) * 0.001;
  X( X()+incr );
  float width = static_cast<float>(frame->getWidth());
  if ( X() < 0) {
    //velocityX(0);
  }
  if ( X() > Gamedata::getInstance()->getXmlInt("viewWidth")-width) {
   // velocityX(0);
  }  
}
