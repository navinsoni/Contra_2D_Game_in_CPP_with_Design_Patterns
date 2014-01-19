#include <iostream>
#include <algorithm>
#include <cmath>
#include "player.h"
#include "bullets.h"
#include "bullet.h"
#include "sound.h"

Player::Player(const string& n,const string& no) :
  MultiFrameSprite(n,no,
  					Vector2f(Gamedata::getInstance()->getXmlInt(n+no+"X"),
                    	Gamedata::getInstance()->getXmlInt(n+no+"Y")),
					Vector2f(Gamedata::getInstance()->getXmlInt(n+no+"Xspeed"),
                    	Gamedata::getInstance()->getXmlInt(n+no+"Yspeed"))),
  upp(false),
  downn(false),
  jumpjump(false),
  power("redorb"),
  offset("BulletLUp"),
  bulletDirection(Vector2f(0,0)),
  position(Vector2f(Gamedata::getInstance()->getXmlInt(n+no+"X"),
                    Gamedata::getInstance()->getXmlInt(n+no+"Y"))),
  dt(0),
  strength(Gamedata::getInstance()->getXmlInt(n+"Strength")),
  df(0),
  currentPoint(0),
  swim(false),
  rwalk(FrameFactory::getInstance().getFrame(n,"RWalk")),
  rwalkswim(FrameFactory::getInstance().getFrame(n,"RWalkSwim")),
  lwalk(FrameFactory::getInstance().getFrame(n,"LWalk")),
  lwalkswim(FrameFactory::getInstance().getFrame(n,"LWalkSwim")),
  rwalkfire(FrameFactory::getInstance().getFrame(n,"RWalkFire")),
  rwalkfireswim(FrameFactory::getInstance().getFrame(n,"RWalkFireSwim")),
  lwalkfire(FrameFactory::getInstance().getFrame(n,"LWalkFire")),
  lwalkfireswim(FrameFactory::getInstance().getFrame(n,"LWalkFireSwim")),
  rjump(FrameFactory::getInstance().getFrame(n,"RJump")),
  ljump(FrameFactory::getInstance().getFrame(n,"LJump")),
  rgundown(FrameFactory::getInstance().getFrame(n,"RGunDown")),
  lgundown(FrameFactory::getInstance().getFrame(n,"LGunDown")),
  rgunup(FrameFactory::getInstance().getFrame(n,"RGunUp")),
  rgunupswim(FrameFactory::getInstance().getFrame(n,"RGunUpSwim")),
  lgunup(FrameFactory::getInstance().getFrame(n,"LGunUp")),
  lgunupswim(FrameFactory::getInstance().getFrame(n,"LGunUpSwim")),
  rdown(FrameFactory::getInstance().getFrame(n,"RDown")),
  ldown(FrameFactory::getInstance().getFrame(n,"LDown")),
  downswim(FrameFactory::getInstance().getFrame(n,"DownSwim")),
  rup(FrameFactory::getInstance().getFrame(n,"RUp")),
  rupswim(FrameFactory::getInstance().getFrame(n,"RUpSwim")),
  lup(FrameFactory::getInstance().getFrame(n,"LUp")),
  lupswim(FrameFactory::getInstance().getFrame(n,"LUpSwim")),
  rnormal(FrameFactory::getInstance().getFrame(n,"RNormal")),
  lnormal(FrameFactory::getInstance().getFrame(n,"LNormal"))
{ 
	reverse(lwalk.begin(),lwalk.end());
	reverse(lwalkfire.begin(),lwalkfire.end());
	reverse(ljump.begin(),ljump.end());
	reverse(lgundown.begin(),lgundown.end());
	reverse(lgunup.begin(),lgunup.end());
	reverse(ldown.begin(),ldown.end());
	reverse(lup.begin(),lup.end());
	reverse(lnormal.begin(),lnormal.end());
	setFrameVector(rnormal);
	}

Player::Player(const Player& s) :
  MultiFrameSprite(s.getName(),s.getNumber(),s.getPosition(),s.getVelocity()), 
  upp(s.upp),
  downn(s.downn),
  jumpjump(s.jumpjump),
  power(s.power),
  offset(s.offset),
  bulletDirection(s.bulletDirection),
  position(s.position),
  dt(s.dt),
  strength(s.strength),
  df(s.df),
  currentPoint(s.currentPoint),
  swim(s.swim),
  rwalk(s.rwalk),
  rwalkswim(s.rwalkswim),
  lwalk(s.lwalk),
  lwalkswim(s.lwalkswim),
  rwalkfire(s.rwalkfire),
  rwalkfireswim(s.rwalkfireswim),
  lwalkfire(s.lwalkfire),
  lwalkfireswim(s.lwalkfireswim),
  rjump(s.rjump),
  ljump(s.ljump),
  rgundown(s.rgundown),
  lgundown(s.lgundown),
  rgunup(s.rgunup),
  rgunupswim(s.rgunupswim),
  lgunup(s.lgunup),
  lgunupswim(s.lgunupswim),
  rdown(s.rdown),
  ldown(s.ldown),
  downswim(s.downswim),
  rup(s.rup),
  rupswim(s.rupswim),
  lup(s.lup),
  lupswim(s.lupswim),
  rnormal(s.rnormal),
  lnormal(s.lnormal)
  { }

Player& Player::operator=(const Player& rhs) {
  setName( rhs.getName() );
  setPosition(rhs.getPosition());
  setVelocity(rhs.getVelocity());
  setMaxVelocity(rhs.getMaxVelocity());
  currentFrame(rhs.currentFrame());
  change(rhs.change());
  setDirection(rhs.getDirection());
  setUp(rhs.getUp());
  setDown(rhs.getDown());
  power = rhs.power;
  offset = rhs.offset;
  bulletDirection = rhs.bulletDirection;
  position = rhs.position;
  dt = rhs.dt;
  strength = rhs.strength;
  df = rhs.df;
  currentPoint = rhs.currentPoint;
  upp = rhs.upp;
  downn = rhs.downn;
  jumpjump = rhs.jumpjump;
  position = rhs.position;
  swim = rhs.swim;
  rwalk = rhs.rwalk;
  rwalkswim = rhs.rwalkswim;
  lwalk = rhs.lwalk;
  lwalkswim = rhs.lwalkswim;
  rwalkfire = rhs.rwalkfire;
  rwalkfireswim = rhs.rwalkfireswim;
  lwalkfire = rhs.lwalkfire;
  lwalkfireswim = rhs.lwalkfireswim;
  rjump = rhs.rjump;
  ljump = rhs.ljump;
  rgundown = rhs.rgundown;
  lgundown = rhs.lgundown;
  rgunup = rhs.rgunup;
  rgunupswim = rhs.rgunupswim;
  lgunup = rhs.lgunup;
  lgunupswim = rhs.lgunupswim;
  rdown = rhs.rdown;
  ldown = rhs.ldown;
  downswim = rhs.downswim;
  rup = rhs.rup;
  rupswim = rhs.rupswim;
  lup = rhs.lup;
  lupswim = rhs.lupswim;
  rnormal = rhs.rnormal;
  lnormal = rhs.lnormal;
  setFrameVector(rhs.getFrameVector());
  return *this;
}

void Player::update(Uint32 ticks) { 
	uint8_t controls = getControls();
	if(controls==0xff || controls==0xfe){
		if(controls==0xff && strength>0 && !(Swim() && getDown())){
			--strength;
		}
		if(strength==0 && !(Swim() && getDown())){
			std::cout<< "i will die soon --- "<<getName()<<std::endl;
		}
		else{
			setControls(0x00);
		}
	}
	else{
    std::vector<float> temp;
	temp = MapX::getInstance().getY((X()+getFrame()->getWidth()/2)/Gamedata::getInstance()->getXmlInt("unitLength"));
	for(unsigned i=0;i<temp.size();i++){
		currentPoint = i;
		if(temp[i]>=Yi()){
			break;
		}
	}
//	for (unsigned i=0;i<temp.size();i++){
//		std::cout<<temp[i]<<std::endl;
//	}
//	std::cout<<std::endl;
//		if(temp.size()!=0){std::cout<<"Yi  "<<Yi()<<"temp  "<<temp[currentPoint]<<std::endl;}
//	std::cout<<std::endl;
	uint8_t controls = getControls();
	if (Jump()) { controls |= 0x08; }
	
	
	if(controls & 0x40){
		setDirection(false);
	}
	if(controls & 0x80){
		setDirection(true);
	}
	if(controls & 0x20){
		setUp(true);
	}
	if(!(controls & 0x20)){
		setUp(false);
	}
	if(controls & 0x10){
		setDown(true);
	}
	if(!(controls & 0x10)){
		setDown(false);
	}
	

	if(Yi()>temp[currentPoint] && Y()<(temp[currentPoint]-getFrame()->getHeight()) && Jump() && !getDown()){
		Yi(temp[currentPoint]);
		velocityY(-abs(velocityY()));
//		std::cout<<"i am here condition satisfied"<<temp[currentPoint]-getFrame()->getHeight()<<"   "<<Yi()<<"    "<<Y() <<std::endl;
//		std::cout<<std::endl;
	}


	if(currentPoint>0 && Yi() <= temp[currentPoint] && Y()<(temp[currentPoint-1]-getFrame()->getHeight()) && Jump() && !getDown()){
		Yi(temp[currentPoint-1]);
		velocityY(-abs(velocityY()));
//		std::cout<<temp[currentPoint-1]-getFrame()->getHeight()<<"   "<<Yi()<<"    "<<Y() <<std::endl;
//		std::cout<<std::endl;
	}

	if(((controls&0x18) == 0x18) && !Jump()){
		if(currentPoint<temp.size()-2){
			Yi(temp[currentPoint+1]);
		}
	}
	
	
	if(controls & 0xC0){
		if((currentPoint<temp.size()) && (Yi()<temp[currentPoint]) && !Jump()){
			Yi(temp[currentPoint]);
			velocityY(-abs(velocityY()));
			Jump(true);
			jump(ticks,jumpjump);
		}
  		float width = static_cast<float>(rwalk[currentFrame()]->getWidth());
  		float incr = velocityX() * static_cast<float>(ticks) * 0.001;
  		//if((X()+incr) <= Gamedata::getInstance()->getXmlInt("worldWidthStart") || (X()+incr) >=  Gamedata::getInstance()->getXmlInt("worldWidthEnd")-width)
  		if((X()+incr) <= Viewport::getInstance().Xv() || (X()+incr) >=  Gamedata::getInstance()->getXmlInt("worldWidthEnd")-width)
	 		 incr = 0;
		if(!(Swim() && getDown())){
  			X( X()+incr );
			if(Y()>500){
				strength = 0;
			}
		}
		std::cout<<"Yi(): "<<Yi()<<"Y(): "<<Y()<<"temp: "<<temp[currentPoint]<< std::endl;

		if(Swim() && getDown()){
			down(ticks);
		}

		else if(controls & 0x08){
			changeX();
		}
		else if((controls&0x08)==0x00){
			walk(ticks);
		}
	}
	
	if((controls & 0x08) || Jump()){
		Jump(true);
		jump(ticks,jumpjump);
	}
	if((controls&(0xf8)) == 0x20){
		up(ticks);
	}

	if((controls&(0xf8)) == 0x10){
		down(ticks);
	}

	if((controls&(0xf8)) == 0x00){
		normal(ticks);
		if((currentPoint<temp.size()) && (Yi()<temp[currentPoint]) && !Jump()){
			Yi(temp[currentPoint]);
			velocityY(-abs(velocityY()));
			Jump(true);
			jump(ticks,jumpjump);
		}
	}
	
	if(!(controls&0x04)){
		df = 1;
	}

	if(Y()>=(Gamedata::getInstance()->getXmlInt(getName()+"SwimLoc")-2) && Y()<=(Gamedata::getInstance()->getXmlInt(getName()+"SwimLoc")+2))
		Swim(true);
	else
		Swim(false);

	if(Swim() && getDown()){
		down(ticks);
	}

	if(controls&0x04 && !(Swim() && getDown())){
		if(df >= 1){
			fire(power,offset);
			SDLSound::getInstance()["gun"];
		}
		float ms =1000* (Gamedata::getInstance()->getXmlInt("enemyDistance"))/((Gamedata::getInstance()->getXmlInt(power+"NumberOfBullets"))*(Gamedata::getInstance()->getXmlInt(power+"Xspeed")));
		dt += ticks;
		df = dt/ms;
		dt -= df*ms;
	}
	}
}


void Player::jump(Uint32 ticks, bool& jumpjump) {
  float incr = -velocityY() * static_cast<float>(ticks) * 0.001;
  Y( Y()+incr );
  if (getDirection() == false){
	if (getFrameVector() != ljump){
		currentFrame(0);
	}
	advanceFrame(ticks,350.0, "LJump");
	setFrameVector(ljump);
	offset = "BulletLJump";
  }

  if (getDirection() == true){
	if (getFrameVector() != rjump){
		currentFrame(0);
	}
	advanceFrame(ticks,350.0, "RJump");
	setFrameVector(rjump);
	offset = "BulletRJump";
  }

  if ( abs(Yi()-Y()) > Gamedata::getInstance()->getXmlInt(getName()+"JumpHeight")) {
    velocityY( -abs( velocityY() ) );
  }
  if (Y() > Yi()) {
	jumpjump = false;
	Y(Yi());
    velocityY( abs( velocityY() ) );
  }
  //X(X());
}


void Player::walk(Uint32 ticks) { 
  if ( getDirection() == false) {
    velocityX( -abs( velocityX() ) );
	if(getUp()){
		if(!Swim()){
			if (getFrameVector() != lgunup){
				currentFrame(0);
			}
  			advanceFrame(ticks,240.0, "LGunUp");
			setFrameVector(lgunup);
			offset = "BulletLGunUp";
		}
		else{
			currentFrame(0);
			setFrameVector(lgunupswim);
			offset = "BulletLGunUpSwim";
		}
		bulletDirection = Vector2f(-1,-1);
	}
	else if(getDown()){
		if(!Swim()){
			if (getFrameVector() != lgundown){
				currentFrame(0);
			}
  			advanceFrame(ticks,240.0, "LGunDown");
			setFrameVector(lgundown);
			offset = "BulletLGunDown";
		}
		bulletDirection = Vector2f(-1,1);
	}
	else{
		if(!Swim()){
			if (getFrameVector() != lwalk){
				if (getFrameVector() != lwalkfire){
					currentFrame(0);
				}
			}
  			advanceFrame(ticks,500.0, "LWalk");
			setFrameVector(lwalk);
			offset = "BulletLWalk";
			if(getControls()&0x04){
				setFrameVector(lwalkfire);
			}
		}
		else
		{
			currentFrame(0);
			setFrameVector(lwalkswim);
			offset = "BulletLWalkSwim";
			if(getControls()&0x04){
				setFrameVector(lwalkfireswim);
			}
		}
		bulletDirection = Vector2f(-1,0);
	}
  }
  if ( getDirection() == true) {
    velocityX( abs( velocityX() ) );
	if(getUp()){
		if(!Swim()){
			if (getFrameVector() != rgunup){
				currentFrame(0);
			}
  			advanceFrame(ticks,240.0, "RGunUp");
			setFrameVector(rgunup);
			offset = "BulletRGunUp";
		}
		else{
			currentFrame(0);
			setFrameVector(rgunupswim);
			offset = "BulletRGunUpSwim";
		}
		bulletDirection = Vector2f(1,-1);
	}
	else if(getDown()){
		if(!Swim()){
			if (getFrameVector() != rgundown){
				currentFrame(0);
			}
  			advanceFrame(ticks,240.0, "RGunDown");
			setFrameVector(rgundown);
			offset = "BulletRGunDown";
		}
		bulletDirection = Vector2f(1,1);
	}
	else{
		if(!Swim()){
			if (getFrameVector() != rwalk){
				if (getFrameVector() != rwalkfire){
					currentFrame(0);
				}
			}
  			advanceFrame(ticks,500.0, "RWalk");
			setFrameVector(rwalk);
			offset = "BulletRWalk";
			if(getControls()&0x04){
				setFrameVector(rwalkfire);
			}
		}
		else
		{
			currentFrame(0);
			setFrameVector(rwalkswim);
			offset = "BulletRWalkSwim";
			if(getControls()&0x04){
				setFrameVector(rwalkfireswim);
			}
		}
		bulletDirection = Vector2f(1,0);
	}
  }
  /*if ( getDirection() == true ) {
    velocityX( abs( velocityX() ) );
	if(getUp()){
		if (getFrameVector() != rgunup){
			currentFrame(0);
		}
  		advanceFrame(ticks,240.0, "RGunUp");
		setFrameVector(rgunup);
		offset = "BulletRGunUp";
		bulletDirection = Vector2f(1,-1);
	}
	else if(getDown()){
		if (getFrameVector() != rgundown){
			currentFrame(0);
		}
  		advanceFrame(ticks,240.0, "RGunDown");
		setFrameVector(rgundown);
		offset = "BulletRGunDown";
		bulletDirection = Vector2f(1,1);
	}
	else{
		if (getFrameVector() != rwalk){
			if (getFrameVector() != rwalkfire){
				currentFrame(0);
			}
		}
  		advanceFrame(ticks,500.0, "RWalk");
		setFrameVector(rwalk);
		offset = "BulletRWalk";
		bulletDirection = Vector2f(1,0);
		if(getControls()&0x04){
			setFrameVector(rwalkfire);
		}
	}
  } */ 
}


void Player::changeX() { 
  //advanceFrame(ticks,350.0);
  //Y(Y());
  if ( getDirection() == false) {
//	advanceFrame(ticks,350.0, "LJump");
	setFrameVector(ljump);
	offset = "BulletLJump";
	bulletDirection = Vector2f(-1,0);
	//std::cout<<"in changex"<<currentFrame()<<std::endl;
    velocityX( -abs( velocityX() ) );
  }
  if ( getDirection() == true ) {
//	advanceFrame(ticks,350.0, "RJump");
	setFrameVector(rjump);
	offset = "BulletRJump";
	bulletDirection = Vector2f(1,0);
	//std::cout<<"in changex"<<currentFrame()<<std::endl;
    velocityX( abs( velocityX() ) );
  }  
}


void Player::normal(Uint32 ticks){
	if (getFrameVector() != lnormal || getFrameVector() != rnormal || ticks){
		currentFrame(0);
		diffLDraw = 0;
	}
	if(!Swim()){
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
	else{
		if((getControls()&0x04)){
			if (getDirection() == false){
				setFrameVector(lwalkfireswim);
				offset = "BulletLWalkFireSwim";
				bulletDirection = Vector2f(-1,0);
			}
			if (getDirection() == true){
				setFrameVector(rwalkfireswim);
				offset = "BulletRWalkFireSwim";
				bulletDirection = Vector2f(1,0);
			}
		}
		else{	
			if (getDirection() == false){
				setFrameVector(lwalkswim);
				offset = "BulletLWalkSwim";
				bulletDirection = Vector2f(-1,0);
			}
			if (getDirection() == true){
				setFrameVector(rwalkswim);
				offset = "BulletRWalkSwim";
				bulletDirection = Vector2f(1,0);
			}
		}
	}
}


void Player::up(Uint32 ticks){
	if (getFrameVector() != lup){
	}
	if (getFrameVector() != lup || getFrameVector() != rup || ticks){
		currentFrame(0);
	}
	if (getDirection() == false){
		if(!Swim()){
			diffLDraw = static_cast<float>(getFrame()->getWidth())-static_cast<float>(Gamedata::getInstance()->getXmlInt(getName() +  "LUpWidth")/Gamedata::getInstance()->getXmlInt(getName() + "LUpNumberOfFrames"));
			setFrameVector(lup);
			offset = "BulletLUp";
		}
		else{
			diffLDraw = static_cast<float>(getFrame()->getWidth())-static_cast<float>(Gamedata::getInstance()->getXmlInt(getName() +  "LUpSwimWidth")/Gamedata::getInstance()->getXmlInt(getName() + "LUpSwimNumberOfFrames"));
			setFrameVector(lupswim);
			offset = "BulletLUpSwim";
		}
	}
	if (getDirection() == true){
		if(!Swim()){
			diffLDraw = static_cast<float>(getFrame()->getWidth())-static_cast<float>(Gamedata::getInstance()->getXmlInt(getName() +  "RUpWidth")/Gamedata::getInstance()->getXmlInt(getName() + "RUpNumberOfFrames"));
			setFrameVector(rup);
			offset = "BulletRUp";
		}
		else{
			diffLDraw = static_cast<float>(getFrame()->getWidth())-static_cast<float>(Gamedata::getInstance()->getXmlInt(getName() +  "RUpSwimWidth")/Gamedata::getInstance()->getXmlInt(getName() + "RUpSwimNumberOfFrames"));
			setFrameVector(rupswim);
			offset = "BulletRUpSwim";
		}
	}
	bulletDirection = Vector2f(0,-1);
}


void Player::down(Uint32 ticks){
	if(!Swim()){
		if (getFrameVector() != rdown){
			diffLDraw = static_cast<float>(getFrame()->getWidth())-static_cast<float>(Gamedata::getInstance()->getXmlInt(getName() +  "RDownWidth")/Gamedata::getInstance()->getXmlInt(getName() + "RDownNumberOfFrames"));
		}
		if (getFrameVector() != ldown || getFrameVector() != rdown || ticks){
			currentFrame(0);
		}
		if (getDirection() == false){
			setFrameVector(ldown);
			offset = "BulletLDown";
			bulletDirection = Vector2f(-1,0);
		}
		if (getDirection() == true){
			setFrameVector(rdown);
			offset = "BulletRDown";
			bulletDirection = Vector2f(1,0);
		}
	}
	else{
			setFrameVector(downswim);
			offset = "BulletRDown";
			bulletDirection = Vector2f(1,0);
	}
}


void Player::fire(string& power,string& offset){
	Bullets::getInstance().add(new Bullet(power,"1",Vector2f(X()+Gamedata::getInstance()->getXmlInt(getName()+offset+"X"),
            Y()+Gamedata::getInstance()->getXmlInt(getName()+offset+"Y")),
		Vector2f(Gamedata::getInstance()->getXmlInt(power+"Xspeed")*bulletDirection[0]*1.5,
            Gamedata::getInstance()->getXmlInt(power+"Yspeed")*bulletDirection[1])));
}
