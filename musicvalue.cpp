#include <sstream>
#include "musicvalue.h"
#include "gamedata.h"

MusicValue::MusicValue() : 
  io( IOManager::getInstance() ),
  words(), 
  position(),
  space(),
  nextIcon(0),
  click(0),
  keypressed(false)
{ 
  unsigned int n = Gamedata::getInstance()->getXmlInt("musicNumber");
  position[0] = Gamedata::getInstance()->getXmlInt("musicX");
  position[1] = Gamedata::getInstance()->getXmlInt("musicY");
  std::stringstream strm;
  for ( unsigned i = 0; i < n; ++i ) {
    strm << "music" << i;
    words.push_back( Gamedata::getInstance()->getXmlStr(strm.str()) );
    strm.clear(); // clear error flags
    strm.str(std::string()); // clear contents
  }

  space[0] = Gamedata::getInstance()->getXmlInt("musicSpaceX");
  space[1] = Gamedata::getInstance()->getXmlInt("musicSpaceY");
}



void MusicValue::update(Uint32){
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
		if(words[(nextIcon)%words.size()]==Gamedata::getInstance()->getXmlStr("music0")){
			SDLSound::getInstance().musicStart();
		}
		else if(words[(nextIcon)%words.size()]==Gamedata::getInstance()->getXmlStr("music1")){
			SDLSound::getInstance().musicStop();
		}
		std::cout<<words[(nextIcon)%words.size()]<<" selected"<<std::endl;
	}
}

void MusicValue::draw() const {
  int y = position[1];
    io.printMessageCenteredAt(Gamedata::getInstance()->getXmlStr("musicTitle"), y, "larger");
    y += 2*space[1];
  for (unsigned i = 0; i < words.size(); i=i+2) {
    io.printMessageCenteredAt(words[(nextIcon)%words.size()], y, "normal");
    y += space[1];
    io.printMessageCenteredAt(words[(nextIcon+1)%words.size()], y, "small");
    y += space[1];
  }
}

const string& MusicValue::getIconClicked() const { 
  return words[(nextIcon)%words.size()]; 
} 

