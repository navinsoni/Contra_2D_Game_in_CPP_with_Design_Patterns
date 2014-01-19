#include <sstream>
#include "wiimenu.h"
#include "gamedata.h"

WiiMenu::WiiMenu() : 
  io( IOManager::getInstance() ),
  words(), 
  position(),
  space(),
  nextIcon(0),
  click(0),
  keypressed(false)
{ 
  unsigned int n = Gamedata::getInstance()->getXmlInt("controlsNumber");
  position[0] = Gamedata::getInstance()->getXmlInt("controlsX");
  position[1] = Gamedata::getInstance()->getXmlInt("controlsY");
  std::stringstream strm;
  for ( unsigned i = 0; i < n; ++i ) {
    strm << "controls" << i;
    words.push_back( Gamedata::getInstance()->getXmlStr(strm.str()) );
    strm.clear(); // clear error flags
    strm.str(std::string()); // clear contents
  }

  space[0] = Gamedata::getInstance()->getXmlInt("controlsSpaceX");
  space[1] = Gamedata::getInstance()->getXmlInt("controlsSpaceY");
}



void WiiMenu::update(Uint32){
	uint8_t controls = getControls();
	if(controls&0x20){
		decrement();
		click=0;
	}
	if(controls&0x10){
		increment();
		click=0;
	}
	if(controls&0x08){
		click=1;
		if(words[(nextIcon)%words.size()]==Gamedata::getInstance()->getXmlStr("controls0")){
			WiiMote::getInstance().start();
		}
		else if(words[(nextIcon)%words.size()]==Gamedata::getInstance()->getXmlStr("controls1")){
			WiiMote::getInstance().stop();
		}
		std::cout<<words[(nextIcon)%words.size()]<<" selected"<<std::endl;
	}
}

void WiiMenu::draw() const {
  int y = position[1];
    io.printMessageCenteredAt(Gamedata::getInstance()->getXmlStr("controlsTitle"), y, "larger");
    y += 2*space[1];
  for (unsigned i = 0; i < words.size(); i=i+2) {
    io.printMessageCenteredAt(words[(nextIcon)%words.size()], y, "normal");
    y += space[1];
    io.printMessageCenteredAt(words[(nextIcon+1)%words.size()], y, "small");
    y += space[1];
  }
}

const string& WiiMenu::getIconClicked() const { 
  return words[(nextIcon)%words.size()]; 
} 

