#include <iostream>
#include <cmath>
#include "explodingSprite.h"
#include "framefactory.h"

ExplodingSprite::ExplodingSprite(const Sprite& s) :
  SingleFrameSprite(s.getName(),s.getNumber(),s.getPosition(),s.getVelocity()), 
  chunks(), 
  freeList(),
  frames() {
  setFrame(s.getFrame());
  makeChunks();
}

ExplodingSprite::~ExplodingSprite() { 
  chunks.clear();
  freeList.clear();
}

void ExplodingSprite::draw() const { 
  std::list<Chunk>::const_iterator ptr = chunks.begin();
  while (ptr != chunks.end()) {
    ptr->draw();
    ++ptr;
  }
}

void ExplodingSprite::update(Uint32 ticks) { 
  std::list<Chunk>::iterator ptr = chunks.begin();
  while (ptr != chunks.end()) {
    ptr->update(ticks);
    if (ptr->goneTooFar()) {
      freeList.push_back(*ptr);
      ptr = chunks.erase(ptr);
    }   
    else ++ptr;
  }
}

void ExplodingSprite::makeChunks() { 
  unsigned int chunk_width = getFrame()->getWidth()/Gamedata::getInstance()->getXmlInt(getName()+"ChunkNumberOfFrames");
  unsigned int chunk_height = getFrame()->getHeight()/Gamedata::getInstance()->getXmlInt(getName()+"ChunkNumberOfFramesY");
  int speedx = static_cast<int>(velocityX())+1; // Make sure it's not 0;
  int speedy = static_cast<int>(velocityY())+1; // Make sure it's an int.
  frames = FrameFactory::getInstance().getFrame(getName(),"Chunk");
  for (int j = 0; j < Gamedata::getInstance()->getXmlInt(getName()+"ChunkNumberOfFramesY"); ++j) {
  	for (int i = 0; i < Gamedata::getInstance()->getXmlInt(getName()+"ChunkNumberOfFrames"); ++i) {
      float sx = (rand() % speedx + 40) * (rand()%2?-1:1); // 'cause %0 is 
      float sy = (rand() % speedy + 40) * (rand()%2?-1:1); // float except
      Chunk chunk(
                Vector2f(X()+i*chunk_width,   // x coord of destination 
                         Y()+j*chunk_height), // y coord of destination
                Vector2f(sx, sy),
                getName()+"Chunk",
                frames[j*Gamedata::getInstance()->getXmlInt(getName()+"ChunkNumberOfFramesY")+i]);
      chunks.push_back(chunk);
    }
  }
}

