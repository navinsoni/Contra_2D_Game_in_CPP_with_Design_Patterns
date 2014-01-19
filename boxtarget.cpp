#include <iostream>
#include <cmath>
#include "boxtarget.h"
#include "sound.h"

BoxTarget::BoxTarget(const string& n,const string& no) :
  MultiFrameSprite(n,no,
  					Vector2f(Gamedata::getInstance()->getXmlInt(n+no+"X"),
                    	Gamedata::getInstance()->getXmlInt(n+no+"Y")),
					Vector2f(Gamedata::getInstance()->getXmlInt(n+no+"Xspeed"),
                    	Gamedata::getInstance()->getXmlInt(n+no+"Yspeed"))),
  upp(false),
  downn(false),
  dt(0),
  strength(Gamedata::getInstance()->getXmlInt(n+"Strength")),
  power("redorb"),
  offset("BulletLUp"),
  bulletDirection(Vector2f(0,0)),
  up(FrameFactory::getInstance().getFrame(n,"Up")),
  rup30(FrameFactory::getInstance().getFrame(n,"RUp30")),
  lup30(FrameFactory::getInstance().getFrame(n,"LUp30")),
  rup60(FrameFactory::getInstance().getFrame(n,"RUp60")),
  lup60(FrameFactory::getInstance().getFrame(n,"LUp60")),
  rnormal(FrameFactory::getInstance().getFrame(n,"RNormal")),
  lnormal(FrameFactory::getInstance().getFrame(n,"LNormal")),
  rdown60(FrameFactory::getInstance().getFrame(n,"RDown60")),
  ldown60(FrameFactory::getInstance().getFrame(n,"LDown60")),
  rdown30(FrameFactory::getInstance().getFrame(n,"RDown30")),
  ldown30(FrameFactory::getInstance().getFrame(n,"LDown30")),
  down(FrameFactory::getInstance().getFrame(n,"Down"))
  { 
	setFrameVector(lnormal);
	}

BoxTarget::BoxTarget(const BoxTarget& s) :
  MultiFrameSprite(s.getName(),s.getNumber(),s.getPosition(),s.getVelocity()), 
  upp(s.upp),
  downn(s.downn),
  dt(s.dt),
  strength(s.strength),
  power(s.power),
  offset(s.offset),
  bulletDirection(s.bulletDirection),
  up(s.up),
  rup30(s.rup30),
  lup30(s.lup30),
  rup60(s.rup60),
  lup60(s.lup60),
  rnormal(s.rnormal),
  lnormal(s.lnormal),
  rdown60(s.rdown60),
  ldown60(s.ldown60),
  rdown30(s.rdown30),
  ldown30(s.ldown30),
  down(s.down)
  { }

BoxTarget& BoxTarget::operator=(const BoxTarget& rhs) {
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
  strength = rhs.strength;
  power = rhs.power;
  offset = rhs.offset;
  bulletDirection = rhs.bulletDirection;
  setFrameVector(rhs.getFrameVector());
  up = rhs.up;
  rup30 = rhs.rup30;
  lup30 = rhs.lup30;
  rup60 = rhs.rup60;
  lup60 = rhs.lup60;
  rnormal = rhs.rnormal;
  lnormal = rhs.lnormal;
  rdown60 = rhs.rdown60;
  ldown60 = rhs.ldown60;
  rdown30 = rhs.rdown30;
  ldown30 = rhs.ldown30;
  down = rhs.down;
  return *this;
}

void BoxTarget::update(Uint32 ticks){
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

		if (((location[1] <= 15 && location[1] >= 0) || (location[1] <= 360 && location[1] >= 345) || (location[1] >= 165 && location[1] <= 195))){
			normal(ticks);
		}	

		if (location[1] > 15 && location[1] < 165){
			if (location[1] > 15 && location[1] <= 45){
				setFrameVector(lup60);
				offset = "BulletLUp60";
				bulletDirection = Vector2f(-0.87,-0.5);
			}
			
			if (location[1] > 45 && location[1] <= 75){
				setFrameVector(lup30);
				offset = "BulletLUp30";
				bulletDirection = Vector2f(-0.5,-0.87);
			}
			
			if (location[1] > 75 && location[1] <= 105){
				setFrameVector(up);
				offset = "BulletUp";
				bulletDirection = Vector2f(0,-1);
			}
			
			if (location[1] > 105 && location[1] <= 135){
				setFrameVector(rup30);
				offset = "BulletRUp30";
				bulletDirection = Vector2f(0.5,-0.87);
			}
			
			if (location[1] > 135 && location[1] < 165){
				setFrameVector(rup60);
				offset = "BulletRUp60";
				bulletDirection = Vector2f(0.87,-0.5);
			}
		}

		if (location[1] > 195 && location[1] < 345 ){
			if (location[1] > 195 && location[1] <= 225){
				setFrameVector(rdown60);
				offset = "BulletRDown60";
				bulletDirection = Vector2f(0.87,0.5);
			}
			if (location[1] > 225 && location[1] <= 255){
				setFrameVector(rdown30);
				offset = "BulletRDown30";
				bulletDirection = Vector2f(0.5,0.87);
			}
			if (location[1] > 255 && location[1] <= 285){
				setFrameVector(down);
				offset = "BulletDown";
				bulletDirection = Vector2f(0,1);
			}
			if (location[1] > 285 && location[1] <= 315){
				setFrameVector(ldown30);
				offset = "BulletLDown30";
				bulletDirection = Vector2f(-0.5,0.87);
			}
			if (location[1] > 315 && location[1] < 345){
				setFrameVector(ldown60);
				offset = "BulletLDown60";
				bulletDirection = Vector2f(-0.87,0.5);
			}
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

void BoxTarget::normal(Uint32){
	if (getDirection() == false){
		setFrameVector(lnormal);
		offset = "BulletLNormal";
		bulletDirection = Vector2f(-1,0);
	}
	if (getDirection() == true){
		setFrameVector(rnormal);
		offset = "BulletRNormal";
		bulletDirection = Vector2f(1,0);
	}
}


void BoxTarget::fire(string& power,string& offset){
		Bullets::getInstance().add(new Bullet(power,"",Vector2f(X()+Gamedata::getInstance()->getXmlInt(getName()+offset+"X"),
        	    Y()+Gamedata::getInstance()->getXmlInt(getName()+offset+"Y")),
			Vector2f(Gamedata::getInstance()->getXmlFloat("redorbXspeed")*bulletDirection[0],
            	Gamedata::getInstance()->getXmlFloat("redorbYspeed")*bulletDirection[1])));
}
