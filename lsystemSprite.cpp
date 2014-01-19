#include "ioManager.h"
#include "lsystemSprite.h"

LsystemSprite::LsystemSprite(const string& n,const string& no) :
  SingleFrameSprite(n,no,
  					Vector2f(Gamedata::getInstance()->getXmlInt(n+no+"X"),
                    	Gamedata::getInstance()->getXmlInt(n+no+"Y")),
					Vector2f(Gamedata::getInstance()->getXmlInt(n+no+"Xspeed"),
                    	Gamedata::getInstance()->getXmlInt(n+no+"Yspeed"))),
  gdata( Gamedata::getInstance() ),
  lsystem(gdata->getXmlStr(n+"File")),
  lsysSurface(lsystem.getSurface()),
  lsysFrame(new Frame(lsysSurface, 
                gdata->getXmlInt(n+"Width"), 
                gdata->getXmlInt(n+"Height"),
                gdata->getXmlInt(n+"SrcX"),
                gdata->getXmlInt(n+"SrcY"))
           ),
  currentColor(0),
  strokeColor(0)
{ 
  setFrame(lsysFrame);
  Uint32 colorkey = SDL_MapRGB(lsysSurface->format, 255, 0, 255);
  SDL_SetColorKey(lsysSurface, SDL_SRCCOLORKEY|SDL_RLEACCEL, colorkey);
}

LsystemSprite::~LsystemSprite() {
  SDL_FreeSurface(lsysSurface);
  delete lsysFrame;
}

void LsystemSprite::changeLength() {
  static int strokeLength = 7;
  static int factor = -1;
  if (strokeLength <= 3) {
    factor = 1;
  }
  else if (strokeLength >= 7) {
    factor = -1;
  }
  strokeLength = strokeLength + factor;
  //lsystem.changeStrokeLength(strokeLength);
}

void LsystemSprite::changeColor() {
 // changeLength();
  SDL_Surface* screen = IOManager::getInstance().getScreen();
  currentColor = (currentColor+1) % 3;
  switch (currentColor) {
    case 0: strokeColor = SDL_MapRGB(screen->format, 0xff, 0x00, 0x00); 
            break;
    case 1: strokeColor = SDL_MapRGB(screen->format, 0x00, 0xff, 0x00); 
            break;
    case 2: strokeColor = SDL_MapRGB(screen->format, 255, 215, 0); 
  }
  lsystem.changeColor(strokeColor);
}

void LsystemSprite::update(Uint32 ticks) {
  static float previous = 0;
  float incr = velocityX() * static_cast<float>(ticks) * 0.001;
  X( X()+incr );
  float width = static_cast<float>(getFrame()->getWidth());
  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
  }
  if ( X() > Gamedata::getInstance()->getXmlInt("worldWidth")-width) {
    velocityX( -abs( velocityX() ) );
  }  

if(abs(previous-X())>200) {
previous = X();
changeColor();
}
}
