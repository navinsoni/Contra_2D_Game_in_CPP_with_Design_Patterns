#include <iostream>
#include <cmath>
#include "bigbullet.h"
#include "sound.h"

BigBullet::BigBullet(const string& n,const string& no) :
  MultiFrameSprite(n,no,
  					Vector2f(Gamedata::getInstance()->getXmlInt(n+no+"X"),
                    	Gamedata::getInstance()->getXmlInt(n+no+"Y")),
					Vector2f(Gamedata::getInstance()->getXmlInt(n+no+"Xspeed"),
                    	Gamedata::getInstance()->getXmlInt(n+no+"Yspeed"))),
  dt(0),
  strength(Gamedata::getInstance()->getXmlInt(n+"Strength")),
  power("bigBulletL"),
  offset("BulletLNormal"),
  bulletDirection(Vector2f(0,0)),
  rnormal(FrameFactory::getInstance().getFrame(n,"Normal")),
  lnormal(FrameFactory::getInstance().getFrame(n,"Normal"))
  { 
	currentFrame(0);
	setFrameVector(lnormal);
	}

BigBullet::BigBullet(const BigBullet& s) :
  MultiFrameSprite(s.getName(),s.getNumber(),s.getPosition(),s.getVelocity()), 
  dt(s.dt),
  strength(s.strength),
  power(s.power),
  offset(s.offset),
  bulletDirection(s.bulletDirection),
  rnormal(s.rnormal),
  lnormal(s.lnormal)
  { }

BigBullet& BigBullet::operator=(const BigBullet& rhs) {
  setName( rhs.getName() );
  setPosition(rhs.getPosition());
  setVelocity(rhs.getVelocity());
  setMaxVelocity(rhs.getMaxVelocity());
  currentFrame(rhs.currentFrame());
  change(rhs.change());
  setDirection(rhs.getDirection());
  dt = rhs.dt;
  strength = rhs.strength;
  power = rhs.power;
  offset = rhs.offset;
  bulletDirection = rhs.bulletDirection;
  setFrameVector(rhs.getFrameVector());
  rnormal = rhs.rnormal;
  lnormal = rhs.lnormal;
  return *this;
}

void BigBullet::update(Uint32 ticks){
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
	if (location[0] <= Gamedata::getInstance()->getXmlInt("enemyDistance")){
		if (location[1] > 90 && location[1] < 270){
			setDirection(true);
		}
		else{
			setDirection(false);
		}	

		if (((location[1] <= 15 && location[1] >= 0) || (location[1] <= 360 && location[1] >= 345) || (location[1] >= 165 && location[1] <= 195)))		  {
			normal(ticks);
		}	
		
		float ms =1000* (Gamedata::getInstance()->getXmlInt("enemyDistance"))/((Gamedata::getInstance()->getXmlInt(power+"NumberOfBullets"))*(Gamedata::getInstance()->getXmlInt(power+"Xspeed")));
		dt += ticks;
		int df = dt/ms;
		dt -= df*ms;
		if(df >= 1){
			fire(power,offset);
			SDLSound::getInstance()["gun"];
		}
	}
	else{
		setDirection(false);
		normal(ticks);
	}
	}
}

void BigBullet::normal(Uint32){
	if (getDirection() == false){
		setFrameVector(lnormal);
		power = "bigBulletL";
		offset = "BulletLNormal";
		bulletDirection = Vector2f(-1,0);
	}
	if (getDirection() == true){
		setFrameVector(rnormal);
		power = "bigBulletR";
		offset = "BulletRNormal";
		bulletDirection = Vector2f(1,0);
	}
}


void BigBullet::fire(string& power,string& offset){
		Bullets::getInstance().add(new Bullet(power,"",Vector2f(X()+Gamedata::getInstance()->getXmlInt(getName()+offset+"X"),
        	    Y()+Gamedata::getInstance()->getXmlInt(getName()+offset+"Y")),
			Vector2f(Gamedata::getInstance()->getXmlFloat("redorbXspeed")*bulletDirection[0],
            	Gamedata::getInstance()->getXmlFloat("redorbYspeed")*bulletDirection[1])));
}
