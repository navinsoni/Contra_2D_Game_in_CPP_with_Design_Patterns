#ifndef SINGLE__H
#define SINGLE__H
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include <map>
#include <sstream>
using std::string;
#include "gamedata.h"

class IOManager {
public:
  static IOManager& getInstance();
  SDL_Surface * getScreen() const { return screen; }
  ~IOManager() { 
  	std::map<std::string, TTF_Font*>::const_iterator it=fmap.begin();
	while(it!=fmap.end()){
		std::cout<<it->first<<std::endl;
    	TTF_CloseFont(it->second);
		it++;
	}
  }
  SDL_Surface* loadAndSet(const string& filename, bool setcolorkey) const;

  void printMessageAt(const string& msg, Uint32 x, Uint32 y, std::string font) const;
  void printMessageCenteredAt(const string& msg, Uint32 y, std::string font) const;
  void printStringAfterMessage(const string&, Uint32 x, Uint32 y, std::string font) const;

  template <typename T>
  void printMessageValueAt(const string& msg, T value, 
         Uint32 x, Uint32 y, std::string font) const;

  void buildString(SDL_Event);
  void clearString() { inputString = ""; }
  const string& getString() const { return inputString; }
private:
  IOManager();
  IOManager(const IOManager&);
  IOManager& operator=(const IOManager&);
  const Gamedata* gdata;
  int viewWidth;
  int viewHeight;
  const unsigned MAX_STRING_SIZE;
  SDL_Surface * screen;
  std::map<std::string, TTF_Font*> fmap;
  string inputString;
};
#endif
