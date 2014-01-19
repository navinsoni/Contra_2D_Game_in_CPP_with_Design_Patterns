#include <sstream>
#include "scrolling.h"
#include "gamedata.h"

Scrolling::Scrolling() : 
  io( IOManager::getInstance() ),
  words(), 
  nextIcon(0),
  time(0),
  scroller()
{ 
  unsigned int n = Gamedata::getInstance()->getXmlInt("introductionTextNumber");
  std::stringstream strm;
  for ( unsigned i = 0; i < n; ++i ) {
    strm << "introductionText" << i;
    words.push_back( Gamedata::getInstance()->getXmlStr(strm.str()) );
    strm.clear(); // clear error flags
    strm.str(std::string()); // clear contents
  }
}



void Scrolling::update(Uint32 ticks){
	time+=ticks*0.0001*Gamedata::getInstance()->getXmlFloat("introductionTextSpeed");
	if(time>Gamedata::getInstance()->getXmlFloat("introductionTextDelay")){
		time-=Gamedata::getInstance()->getXmlFloat("introductionTextDelay");
		scroller.push_back(ScrollingLine(words[nextIcon]));
	if(nextIcon<words.size()-1){
		increment();
	}
	}
	if(nextIcon<words.size()-1){
	for(unsigned i=0; i<nextIcon; i++){
		scroller[i].update(ticks);
	}
	}
}

void Scrolling::draw() const {
	for(unsigned i=0; i<nextIcon; i++){
		scroller[i].draw();
	}
}

const string& Scrolling::getIconClicked() const { 
  return words[nextIcon]; 
} 

