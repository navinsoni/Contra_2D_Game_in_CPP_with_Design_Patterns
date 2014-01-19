#include <iostream>
#include <cmath>
#include "enemystationary.h"
#include "sound.h"

EnemyStationary::EnemyStationary(const string& n,const string& no) :
  MultiFrameSprite(n,no,
  					Vector2f(Gamedata::getInstance()->getXmlInt(n+no+"X"),
                    	Gamedata::getInstance()->getXmlInt(n+no+"Y")),
					Vector2f(Gamedata::getInstance()->getXmlInt(n+no+"Xspeed"),
                    	Gamedata::getInstance()->getXmlInt(n+no+"Yspeed"))),
  upp(false),
  downn(false),
  dt(0),
  power("redorb"),
  offset("BulletLUp"),
  bulletDirection(Vector2f(0,0)),
  rgundown(FrameFactory::getInstance().getFrame(n,"RGunDown")),
  lgundown(FrameFactory::getInstance().getFrame(n,"LGunDown")),
  rgunup(FrameFactory::getInstance().getFrame(n,"RGunUp")),
  lgunup(FrameFactory::getInstance().getFrame(n,"LGunUp")),
  rnormal(FrameFactory::getInstance().getFrame(n,"RNormal")),
  lnormal(FrameFactory::getInstance().getFrame(n,"LNormal"))
{ 
	setFrameVector(rnormal);
	}

EnemyStationary::EnemyStationary(const EnemyStationary& s) :
  MultiFrameSprite(s.getName(),s.getNumber(),s.getPosition(),s.getVelocity()), 
  upp(s.upp),
  downn(s.downn),
  dt(s.dt),
  power(s.power),
  offset(s.offset),
  bulletDirection(s.bulletDirection),
  rgundown(s.rgundown),
  lgundown(s.lgundown),
  rgunup(s.rgunup),
  lgunup(s.lgunup),
  rnormal(s.rnormal),
  lnormal(s.lnormal)
  { }

EnemyStationary& EnemyStationary::operator=(const EnemyStationary& rhs) {
  setName( rhs.getName() );
  setPosition(rhs.getPosition());
  setVelocity(rhs.getVelocity());
  setMaxVelocity(rhs.getMaxVelocity());
  currentFrame(rhs.currentFrame());
  change(rhs.change());
  setDirection(rhs.getDirection());
  setUp(rhs.getUp());
  setDown(rhs.getDown());
  upp = rhs.upp;
  downn = rhs.downn;
  dt = rhs.dt;
  power = rhs.power;
  offset = rhs.offset;
  bulletDirection = rhs.bulletDirection;
  rgundown = rhs.rgundown;
  lgundown = rhs.lgundown;
  rgunup = rhs.rgunup;
  lgunup = rhs.lgunup;
  rnormal = rhs.rnormal;
  lnormal = rhs.lnormal;
  setFrameVector(rhs.getFrameVector());
  return *this;
}

void EnemyStationary::update(Uint32 ticks){
	uint8_t controls = getControls();
	if(controls==0xff){
		std::cout<< "i will die soon --- "<<getName()<<std::endl;
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

		if (((location[1] <= 22.5 && location[1] >= 0) || (location[1] <= 360 && location[1] >= 337.5) || (location[1] >= 157.5 && location[1] <= 202.5))){
			normal(ticks);
		}	

		if (((location[1] > 22.5 && location[1] <= 67.5) || (location[1] >= 112.5 && location[1] < 157.5))){
			up(ticks);
		}

		if (((location[1] >= 292.5 && location[1] < 337.5) || (location[1] <= 247.5 && location[1] > 202.5))){
			down(ticks);
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

void EnemyStationary::normal(Uint32 ticks){
	if (getDirection() == false){
		if (getFrameVector() != lnormal){
			currentFrame(0);
		}
  		advanceFrame(ticks, 600.0, "LNormal");
		setFrameVector(lnormal);
		offset = "BulletLNormal";
		bulletDirection = Vector2f(-1,0);
	}
	if (getDirection() == true){
		if (getFrameVector() != rnormal){
			currentFrame(0);
		}
  		advanceFrame(ticks, 600.0, "RNormal");
		setFrameVector(rnormal);
		offset = "BulletRNormal";
		bulletDirection = Vector2f(1,0);
	}
}


void EnemyStationary::up(Uint32 ticks){
	if (getDirection() == false){
		if (getFrameVector() != lgunup){
			currentFrame(0);
		}
  		advanceFrame(ticks, 600.0, "LGunUp");
		setFrameVector(lgunup);
		offset = "BulletLGunUp";
		bulletDirection = Vector2f(-1,-1);
	}
	if (getDirection() == true){
		if (getFrameVector() != rgunup){
			currentFrame(0);
		}
  		advanceFrame(ticks, 600.0, "RGunUp");
		setFrameVector(rgunup);
		offset = "BulletRGunUp";
		bulletDirection = Vector2f(1,-1);
	}
}


void EnemyStationary::down(Uint32 ticks){
	if (getDirection() == false){
		if (getFrameVector() != lgundown){
			currentFrame(0);
		}
  		advanceFrame(ticks, 600.0, "LGunDown");
		setFrameVector(lgundown);
		offset = "BulletLGunDown";
		bulletDirection = Vector2f(-1,1);
	}
	if (getDirection() == true){
		if (getFrameVector() != rgundown){
			currentFrame(0);
		}
  		advanceFrame(ticks, 600.0, "RGunDown");
		setFrameVector(rgundown);
		offset = "BulletRGunDown";
		bulletDirection = Vector2f(1,1);
	}
}


void EnemyStationary::fire(string& power,string& offset){
		Bullets::getInstance().add(new Bullet(power,"",Vector2f(X()+Gamedata::getInstance()->getXmlInt(getName()+offset+"X"),
        	    Y()+Gamedata::getInstance()->getXmlInt(getName()+offset+"Y")),
			Vector2f(Gamedata::getInstance()->getXmlInt("redorbXspeed")*bulletDirection[0],
            	Gamedata::getInstance()->getXmlInt("redorbYspeed")*bulletDirection[1])));
}
