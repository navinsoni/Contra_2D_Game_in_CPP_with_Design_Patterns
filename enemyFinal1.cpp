#include <iostream>
#include <cmath>
#include "enemyFinal1.h"
#include "sound.h"

EnemyFinal1::EnemyFinal1(const string& n,const string& no) :
  MultiFrameSprite(n,no,
  					Vector2f(Gamedata::getInstance()->getXmlInt(n+no+"X"),
                    	Gamedata::getInstance()->getXmlInt(n+no+"Y")),
					Vector2f(Gamedata::getInstance()->getXmlInt(n+no+"Xspeed"),
                    	Gamedata::getInstance()->getXmlInt(n+no+"Yspeed"))),
  strength(Gamedata::getInstance()->getXmlInt(n+"Strength")),
  dt(0),
  bulletDirection(Vector2f(0,0)),
  power("enemyFinal"),
  offset("Offset"),
  rnormal(FrameFactory::getInstance().getFrame(n,"RNormal")),
  enemyFrame(FrameFactory::getInstance().getFrame("enemyFinal1Frame","")[0])
  { 
	setFrameVector(rnormal);
	}

EnemyFinal1::EnemyFinal1(const EnemyFinal1& s) :
  MultiFrameSprite(s.getName(),s.getNumber(),s.getPosition(),s.getVelocity()), 
  strength(s.strength),
  dt(s.dt),
  bulletDirection(s.bulletDirection),
  power(s.power),
  offset(s.offset),
  rnormal(s.rnormal),
  enemyFrame(s.enemyFrame)
  { }

EnemyFinal1& EnemyFinal1::operator=(const EnemyFinal1& rhs) {
  setName( rhs.getName() );
  setPosition(rhs.getPosition());
  setVelocity(rhs.getVelocity());
  setMaxVelocity(rhs.getMaxVelocity());
  currentFrame(rhs.currentFrame());
  change(rhs.change());
  setDirection(rhs.getDirection());
  power = rhs.power;
  offset = rhs.offset;
  strength = rhs.strength;
  dt = rhs.dt;
  bulletDirection = rhs.bulletDirection;
  setFrameVector(rhs.getFrameVector());
  rnormal = rhs.rnormal;
  enemyFrame = rhs.enemyFrame;
  return *this;
}

void EnemyFinal1::update(Uint32 ticks){
	uint8_t controls = getControls();
	if(controls==0xff){
		if(--strength==0){
			std::cout<< "i will die soon --- "<<getName()<<std::endl;
		}
		else{
			setControls(0x00);
		}
	}
	else{
		Vector2f location;
		location = Location();
  		advanceFrame(ticks, 600.0, "RNormal");
		bulletDirection = Vector2f(-cos((location[1]/360.0)*3.14),-sin((location[1]/360.0)*3.14));
			//fire(power,offset);
		float ms =1* (Gamedata::getInstance()->getXmlInt("enemyDistance"))/((Gamedata::getInstance()->getXmlInt(power+"NumberOfBullets"))*(Gamedata::getInstance()->getXmlInt(power+"Xspeed")));
		dt += ticks;
		int df = dt/ms;
		dt -= df*ms;
		if(df >= 1){
			fire(power,offset);
			//SDLSound::getInstance()["gun"];
		}
	}
}



void EnemyFinal1::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  enemyFrame->draw(7456,95);
  rnormal[currFrame]->draw(x, y - rnormal[currFrame]->getHeight()); 
}



void EnemyFinal1::fire(string& power,string& offset){
		Bullets::getInstance().add(new Bullet(power,"",Vector2f(X()+Gamedata::getInstance()->getXmlInt(getName()+offset+"X"),
        	    Y()+Gamedata::getInstance()->getXmlInt(getName()+offset+"Y")),
			Vector2f(Gamedata::getInstance()->getXmlInt("redorbXspeed")*bulletDirection[0],
            	Gamedata::getInstance()->getXmlInt("redorbYspeed")*bulletDirection[1])));
}
