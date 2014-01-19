#include <sstream>
#include "soundvalue.h"
#include "gamedata.h"

SoundValue::SoundValue() : 
  io( IOManager::getInstance() ),
  words(), 
  position(),
  space(),
//  clicks(),
  nextIcon(0),
  click(0),
  keypressed(false)
{ 
  unsigned int n = Gamedata::getInstance()->getXmlInt("soundNumber");
  position[0] = Gamedata::getInstance()->getXmlInt("soundX");
  position[1] = Gamedata::getInstance()->getXmlInt("soundY");
  std::stringstream strm;
  for ( unsigned i = 0; i < n; ++i ) {
    strm << "sound" << i;
    words.push_back( Gamedata::getInstance()->getXmlStr(strm.str()) );
    strm.clear(); // clear error flags
    strm.str(std::string()); // clear contents
  }

  space[0] = Gamedata::getInstance()->getXmlInt("soundSpaceX");
  space[1] = Gamedata::getInstance()->getXmlInt("soundSpaceY");
}



void SoundValue::update(Uint32){
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
		if(words[(nextIcon)%words.size()]==Gamedata::getInstance()->getXmlStr("sound0")){
			SDLSound::getInstance().Sound(true);
		}
		else if(words[(nextIcon)%words.size()]==Gamedata::getInstance()->getXmlStr("sound1")){
			SDLSound::getInstance().Sound(false);
		}
		std::cout<<words[(nextIcon)%words.size()]<<" selected"<<std::endl;
	}
}

void SoundValue::draw() const {
  int y = position[1];
    io.printMessageCenteredAt(Gamedata::getInstance()->getXmlStr("soundTitle"), y, "larger");
    y += 2*space[1];
  for (unsigned i = 0; i < words.size(); i=i+2) {
    io.printMessageCenteredAt(words[(nextIcon)%words.size()], y, "normal");
    y += space[1];
    io.printMessageCenteredAt(words[(nextIcon+1)%words.size()], y, "small");
    y += space[1];
  }
}

const string& SoundValue::getIconClicked() const { 
  return words[(nextIcon)%words.size()]; 
} 

