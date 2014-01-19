#include <iostream>
#include <cmath>
#include "bar.h"

Bar::Bar(const string& n,const string& no) :
  SingleFrameSprite(n,no,
  					Vector2f(Gamedata::getInstance()->getXmlInt(n+no+"X"),
                    	Gamedata::getInstance()->getXmlInt(n+no+"Y")),
					Vector2f(Gamedata::getInstance()->getXmlInt(n+no+"Xspeed"),
                    	Gamedata::getInstance()->getXmlInt(n+no+"Yspeed"))),
  value(Gamedata::getInstance()->getXmlInt(n+"Value")),
  frame(FrameFactory::getInstance().getFrame(n,"")),
  screen(IOManager::getInstance().getScreen())
  { }

Bar::Bar(const Bar& b) :
  SingleFrameSprite(b.getName(),b.getNumber(),b.getPosition(),b.getVelocity()),
  value(b.value),
  frame(b.frame),
  screen(b.screen)
  { }

Bar& Bar::operator=(const Bar& rhs) {
  setName( rhs.getName() );
  setPosition(rhs.getPosition());
  setVelocity(rhs.getVelocity());
  setMaxVelocity(rhs.getMaxVelocity());
  setDirection(rhs.getDirection());
  setFrame(rhs.getFrame());
  value = rhs.value;
  frame = rhs.frame;
  screen = rhs.screen;
  return *this;
}

void Bar::draw() const {
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frame[0]->draw(x, y);
  Draw_AALine(screen,x+Gamedata::getInstance()->getXmlInt(getName()+"Width")-value-0.5f,y+(Gamedata::getInstance()->getXmlInt(getName()+"Height")+1)/2-0.5f,x+Gamedata::getInstance()->getXmlInt(getName()+"Width")-0.5f,y+(Gamedata::getInstance()->getXmlInt(getName()+"Height")+1)/2-0.5f,Gamedata::getInstance()->getXmlInt(getName()+"Height"),0x99,0x99,0x99,50);
}

void Bar::update(Uint32 ticks) {
	if(ticks){
	uint8_t controls = getControls();
	if(controls & 0x80) { if(value>0)value--; };
	if(controls & 0x40) { if(value<=Gamedata::getInstance()->getXmlInt(getName()+"Width"))value++; };
	}
}
