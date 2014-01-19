#include <iostream>
#include <cmath>
#include "flame.h"

Flame::Flame(const string& n,const string& no) :
  SingleFrameSprite(n,no,
  					Vector2f(Gamedata::getInstance()->getXmlInt(n+no+"X"),
                    	Gamedata::getInstance()->getXmlInt(n+no+"Y")),
					Vector2f(Gamedata::getInstance()->getXmlInt(n+no+"Xspeed"),
                    	Gamedata::getInstance()->getXmlInt(n+no+"Yspeed"))),
  frame(FrameFactory::getInstance().getFrame(n,"")[0]),
  Xi(Gamedata::getInstance()->getXmlInt(n+no+"X"))
  { setFrame(frame); }

Flame::Flame(const Flame& s) :
  SingleFrameSprite(s.getName(),s.getNumber(),s.getPosition(),s.getVelocity()),
  frame(s.frame),
  Xi(s.Xi)
  { }

Flame& Flame::operator=(const Flame& rhs) {
  setName( rhs.getName() );
  setPosition(rhs.getPosition());
  setVelocity(rhs.getVelocity());
  setMaxVelocity(rhs.getMaxVelocity());
  setDirection(rhs.getDirection());
  setFrame(rhs.getFrame());
  frame = rhs.frame;
  Xi = rhs.Xi;
  return *this;
}

void Flame::update(Uint32 ticks) {
	uint8_t controls = getControls();
	if(controls==0xff){
		std::cout<< "i will never die soon --- "<<getName()<<std::endl;
		setControls(0x00);
	}
	else{ 
  		float incr = velocityX() * static_cast<float>(ticks) * 0.001;
  		X( X()+incr );
		if((Xi-X())>(Gamedata::getInstance()->getXmlFloat(getName()+"Distance")/2) || (X()-Xi+Gamedata::getInstance()->getXmlFloat(getName()+"Width"))>(Gamedata::getInstance()->getXmlFloat(getName()+"Distance")/2)){
			if(velocityX()>0){
				X(Xi+(Gamedata::getInstance()->getXmlFloat(getName()+"Distance"))/2-Gamedata::getInstance()->getXmlFloat(getName()+"Width")-1);
			}
			if(velocityX()<0){
				X(Xi-Gamedata::getInstance()->getXmlFloat(getName()+"Distance")/2+1);
			}
			velocityX(-velocityX());
		}
	}
}
