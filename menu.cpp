#include <sstream>
#include "menu.h"
#include "gamedata.h"
#include "viewport.h"

Menu::Menu() : 
  io( IOManager::getInstance() ),
  words(), 
  position(),
  space(),
  //clicks(),
  nextIcon(3),
  click(0),
  keypressed(false),
  t1(),
  sound(),
  music(),
  help(),
  wii()
{ 
  unsigned int n = Gamedata::getInstance()->getXmlInt("wordsNumber");
  position[0] = Gamedata::getInstance()->getXmlInt("wordsX");
  position[1] = Gamedata::getInstance()->getXmlInt("wordsY");
  std::stringstream strm;
  for ( unsigned i = 0; i < n; ++i ) {
    strm << "words" << i;
    words.push_back( Gamedata::getInstance()->getXmlStr(strm.str()) );
    strm.clear(); // clear error flags
    strm.str(std::string()); // clear contents
  }

  space[0] = Gamedata::getInstance()->getXmlInt("wordsSpaceX");
  space[1] = Gamedata::getInstance()->getXmlInt("wordsSpaceY");
  t1.push_back(new MusicValue());
  music.add(t1);
  t1.clear();
  t1.push_back(new SoundValue());
  sound.add(t1);
  t1.clear();
  t1.push_back(new Help());
  help.add(t1);
  t1.clear();
  t1.push_back(new WiiMenu());
  wii.add(t1);
  t1.clear();
}



void Menu::update(Uint32){
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
		//std::cout<<words[(nextIcon+2)%words.size()]<<" selected"<<std::endl;
		if(words[(nextIcon+2)%words.size()]=="Sound"){
			sound.update(0);
		}
		else if(words[(nextIcon+2)%words.size()]=="Music"){
			music.update(0);
		}
		else if(words[(nextIcon+2)%words.size()]=="Help"){
			help.update(0);
		}
		else if(words[(nextIcon+2)%words.size()]=="Controls"){
			wii.update(0);
		}
		else if(words[(nextIcon+2)%words.size()]=="Start" || words[(nextIcon+2)%words.size()]=="Exit"){
			Notes(words[(nextIcon+2)%words.size()]);
			loopMe(false);
			//std::cout<<Notes()<<std::endl;
		}
	}
}

void Menu::draw() const {
  int x = position[0];
  int y = position[1];
  for (unsigned i = 0; i < words.size(); i=i+50) {
    io.printMessageCenteredAt(words[(nextIcon)%words.size()], y, "smaller");
    y += space[1];
    io.printMessageCenteredAt(words[(nextIcon+1)%words.size()], y, "small");
    y += space[1];
    io.printMessageCenteredAt(words[(nextIcon+2)%words.size()], y, "normal");
    y += space[1];
    io.printMessageCenteredAt(words[(nextIcon+3)%words.size()], y, "small");
    y += space[1];
    io.printMessageCenteredAt(words[(nextIcon+4)%words.size()], y, "smaller");
    y += space[1];
  }
}

const string& Menu::getIconClicked() const { 
  return words[nextIcon]; 
} 

