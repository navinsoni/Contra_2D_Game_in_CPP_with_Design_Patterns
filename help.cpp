#include <sstream>
#include "help.h"
#include "gamedata.h"

Help::Help() : 
  io( IOManager::getInstance() ),
  words(), 
  position(),
  space()
{ 
  unsigned int n = Gamedata::getInstance()->getXmlInt("helpNumber");
  position[0] = Gamedata::getInstance()->getXmlInt("helpX");
  position[1] = Gamedata::getInstance()->getXmlInt("helpY");
  std::stringstream strm;
  for ( unsigned i = 0; i < n; ++i ) {
    strm << "help" << i;
    words.push_back( Gamedata::getInstance()->getXmlStr(strm.str()) );
    strm.clear(); // clear error flags
    strm.str(std::string()); // clear contents
  }

  space[0] = Gamedata::getInstance()->getXmlInt("helpSpaceX");
  space[1] = Gamedata::getInstance()->getXmlInt("helpSpaceY");
}



void Help::update(Uint32){
}

void Help::draw() const {
  int y = position[1];
    io.printMessageCenteredAt(Gamedata::getInstance()->getXmlStr("helpTitle"), y, "large");
    y += 2*space[1];
  for (unsigned i = 0; i < words.size(); ++i) {
    io.printMessageCenteredAt(words[i], y, "smaller");
    y += space[1];
  }
}

