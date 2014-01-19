#ifndef MULTIFRAMESPRITE__H
#define MULTIFRAMESPRITE__H

#include <string>
using std::string;
#include <iostream>

#include "sprite.h"
#include "frame.h"
#include "framefactory.h"
#include "gamedata.h"

class MultiFrameSprite : public Sprite {
public:
  MultiFrameSprite(const string& n,const string& no, const Vector2f& pos, const Vector2f& vel);
  MultiFrameSprite(const MultiFrameSprite& s);
  virtual ~MultiFrameSprite() { } 
  MultiFrameSprite& operator=(const MultiFrameSprite&);
  void currentFrame(unsigned c) { currFrame = c; }
  unsigned currentFrame() const { return currFrame; }
  void change(float d) { dt = d; }
  float change() const { return dt; }
  void setFrameVector(std::vector<Frame*> f) { frame = f; }
  std::vector<Frame*> getFrameVector() const { return frame; }

  virtual const Frame* getFrame() const { return frame[currFrame]; }
  virtual void setFrame(const Frame* f) { if(f){}}
  virtual void draw() const;
  virtual void update(Uint32 ticks) {
	  if(ticks){
		  std::cout << "Update not implemented for "<< getName() << std::endl;
	  }
  }
  
  unsigned getPixel(Uint32, Uint32) const;

  Vector2f getCenter() const { 
    return Vector2f( X()+frame[currFrame]->getWidth()/2, Y()+frame[currFrame]->getHeight()/2 );
  }

private:
  float dt;
  std::vector<Frame*> frame;
protected:
  unsigned currFrame;
  void advanceFrame(Uint32 ticks, float change, std::string action);
  int getDistance(const MultiFrameSprite*) const;
  float diffLDraw;     //used this variable bcoz the sprite was changing x position for diff frames in left direction while drawing
};
#endif
