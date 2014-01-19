#include <sstream>
#include "scrollingline.h"
#include "gamedata.h"

ScrollingLine::ScrollingLine(std::string w) : 
  words(w), 
  position()
{ 
  position[0] = Gamedata::getInstance()->getXmlInt("introductionTextX");
  position[1] = Gamedata::getInstance()->getXmlInt("introductionTextY");
}
 
 
 ScrollingLine::ScrollingLine(const ScrollingLine& s):
	 words(s.words),
	 position(s.position)
	 {}
 
 
 ScrollingLine& ScrollingLine::operator=(const ScrollingLine& rhs){
	 words = rhs.words;
	 position = rhs.position;
	 return *this;
 }



void ScrollingLine::update(Uint32 ticks){
	//std::cout << ticks<<std::endl;
	position[1]-=ticks*0.0001*Gamedata::getInstance()->getXmlFloat("introductionTextSpeed");
}

void ScrollingLine::draw() const {
	//float x=position[0];
	float y=position[1];
    IOManager::getInstance().printMessageCenteredAt(words, y, "smaller");
}
