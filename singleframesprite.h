#ifndef SINGLEFRAMESPRITE__H
#define SINGLEFRAMESPRITE__H

#include <string>
using std::string;
#include <iostream>

#include "sprite.h"
#include "frame.h"
#include "framefactory.h"
#include "gamedata.h"

class SingleFrameSprite : public Sprite {
public:
  SingleFrameSprite(const string& n,const string& no, const Vector2f& pos, const Vector2f& vel);
  SingleFrameSprite(const SingleFrameSprite& s);
  virtual ~SingleFrameSprite() { } 
  SingleFrameSprite& operator=(const SingleFrameSprite&);

  virtual const Frame* getFrame() const { return frame; }
  virtual void setFrame(const Frame* f) { frame = f; }
  virtual void draw() const;
  virtual void update(Uint32 ticks) {
	  if(ticks){
		  std::cout << "Update not implemented for "<< getName() << std::endl;
	  }
  }
  
  unsigned getPixel(Uint32, Uint32) const;

  Vector2f getCenter() const { 
    return Vector2f( X()+frame->getWidth()/2, Y()+frame->getHeight()/2 );
  }

private:
  const Frame* frame;
};
#endif
