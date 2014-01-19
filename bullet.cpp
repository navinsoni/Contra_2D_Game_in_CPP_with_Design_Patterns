#include <iostream>
#include <cmath>
#include "bullet.h"

Bullet::Bullet(const string& n,const string& no, const Vector2f& pos, const Vector2f& vel) :
  SingleFrameSprite(n,no,pos,vel),
  frame(FrameFactory::getInstance().getFrame(n,"")[0]),
  time(0)
  { setFrame(frame); }

Bullet::Bullet(const Bullet& s) :
  SingleFrameSprite(s.getName(),s.getNumber(),s.getPosition(),s.getVelocity()),
  frame(s.frame),
  time(s.time)
  { }

Bullet& Bullet::operator=(const Bullet& rhs) {
  setName( rhs.getName() );
  setPosition(rhs.getPosition());
  setVelocity(rhs.getVelocity());
  setMaxVelocity(rhs.getMaxVelocity());
  setDirection(rhs.getDirection());
  setFrame(rhs.getFrame());
  frame = rhs.frame;
  time = rhs.time;
  return *this;
}

void Bullet::update(Uint32 ticks) {
	uint8_t controls = getControls();
	if(controls==0xff){
		std::cout<< "i will die soon --- "<<getName()<<std::endl;
	}
	else{ 
  float incr = velocityY() * static_cast<float>(ticks) * 0.001;
  Y( Y()+incr );
  incr = velocityX() * static_cast<float>(ticks) * 0.001;
  X( X()+incr );
  time += ticks*0.001;
  if(time>Gamedata::getInstance()->getXmlFloat(getName()+"Time")){
	  setControls(0xFF);
  }
  else{
	  setControls(0x00);
  }
  }
}
