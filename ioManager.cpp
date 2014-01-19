#include <iostream>
#include <iomanip>
#include "ioManager.h"
using std::string;

IOManager& IOManager::getInstance() {
  static IOManager io;
  return io;
}

IOManager::IOManager( ) :
  gdata( Gamedata::getInstance() ),
  viewWidth( gdata->getXmlInt("viewWidth") ),
  viewHeight( gdata->getXmlInt("viewHeight") ),
  MAX_STRING_SIZE( gdata->getXmlInt("maxStringSize") ),
    // The 3rd and 4th parameters are just as important as the first 2!
    screen(SDL_SetVideoMode(viewWidth, viewHeight, 0, SDL_HWSURFACE)),
    fmap(), inputString("")  {
  if (screen == NULL) { 
    throw string("Unable to set video mode"); 
  }
  if ( TTF_Init() == -1 ) {
    throw string("TTF_Init failed: ") + TTF_GetError();
  }
  fmap["smaller"] = TTF_OpenFont(Gamedata::getInstance()->getXmlStr("fontSmaller").c_str(), 
         Gamedata::getInstance()->getXmlInt("fontSmallerSize"));
  if ( !fmap["smaller"] ) {
    throw string("TTF_OpenFont failed: ") + TTF_GetError();
  }
  fmap["small"] = TTF_OpenFont(Gamedata::getInstance()->getXmlStr("fontSmall").c_str(), 
         Gamedata::getInstance()->getXmlInt("fontSmallSize"));
  if ( !fmap["small"] ) {
    throw string("TTF_OpenFont failed: ") + TTF_GetError();
  }
  fmap["normal"] = TTF_OpenFont(Gamedata::getInstance()->getXmlStr("fontNormal").c_str(), 
         Gamedata::getInstance()->getXmlInt("fontNormalSize"));
  if ( !fmap["normal"] ) {
    throw string("TTF_OpenFont failed: ") + TTF_GetError();
  }
  fmap["large"] = TTF_OpenFont(Gamedata::getInstance()->getXmlStr("fontLarge").c_str(), 
         Gamedata::getInstance()->getXmlInt("fontLargeSize"));
  if ( !fmap["large"] ) {
    throw string("TTF_OpenFont failed: ") + TTF_GetError();
  }
  fmap["larger"] = TTF_OpenFont(Gamedata::getInstance()->getXmlStr("fontLarger").c_str(), 
         Gamedata::getInstance()->getXmlInt("fontLargerSize"));
  if ( !fmap["larger"] ) {
    throw string("TTF_OpenFont failed: ") + TTF_GetError();
  }
  SDL_EnableUNICODE( SDL_ENABLE );
  atexit(TTF_Quit);
}

SDL_Surface* IOManager::loadAndSet(const string& filename, bool setcolorkey) const {
  SDL_Surface *tmp = IMG_Load(filename.c_str());
  if (tmp == NULL) {
    throw string("Unable to load bitmap ")+filename;
  }
  if ( setcolorkey ) {
    Uint32 colorkey = SDL_MapRGB(tmp->format, 255, 0, 255);
    SDL_SetColorKey(tmp, SDL_SRCCOLORKEY|SDL_RLEACCEL, colorkey);
  }
  // Optimize the strip for fast display
  SDL_Surface *image = SDL_DisplayFormat(tmp);
  if (image == NULL) {
    image = tmp;
  } 
  else {
    SDL_FreeSurface(tmp);
  }
  return image;
}

void IOManager::printMessageAt(const string& msg, Uint32 x, Uint32 y, std::string font) const {
   SDL_Rect dest = {x,y,0,0};
   SDL_Color color = {0, 0, 0, 0};
   std::map<std::string, TTF_Font*>::const_iterator it = fmap.find(font);
   if(it!=fmap.end()){
   SDL_Surface * stext = TTF_RenderText_Blended(it->second, msg.c_str(), color);
   if (stext) {
     SDL_BlitSurface( stext, NULL, screen, &dest );
     SDL_FreeSurface(stext);
   }
   else {
     throw 
     string("Couldn't allocate text sureface in printMessageAt");
   }
   }
   else{
	   std::cout<<"Please use correct font size"<<std::endl;
   }
}

void IOManager::printMessageCenteredAt( const string& msg, Uint32 y, std::string font) const {
   SDL_Color color = {0, 0, 0, 0};
   std::map<std::string, TTF_Font*>::const_iterator it = fmap.find(font);
   if(it!=fmap.end()){
   SDL_Surface *stext = TTF_RenderText_Blended(it->second, msg.c_str(), color);
   if (stext) {
     Uint32 x = ( viewWidth - stext->w ) / 2;
     SDL_Rect dest = {x,y,0,0};
     SDL_BlitSurface( stext, NULL, screen, &dest );
     SDL_FreeSurface(stext);
   }
   else {
     throw 
     string("Couldn't allocate text sureface in printMessageCenteredAt");
   }
   }
   else{
	   std::cout<<"Please use correct font size"<<std::endl;
   }
}

template <typename T>
void IOManager::printMessageValueAt(const string& msg, T value, 
     Uint32 x, Uint32 y, std::string font) const {
   std::stringstream strm;
   std::string message = msg;
   strm << message << value << "\0";
   message = strm.str();
   SDL_Rect dest = {x,y,0,0};
   SDL_Color color = {0, 0, 0, 0};
   std::map<std::string, TTF_Font*>::const_iterator it = fmap.find(font);
   if(it!=fmap.end()){
   SDL_Surface *stext = 
       TTF_RenderText_Blended(it->second, message.c_str(), color);
   if (stext) {
     SDL_BlitSurface( stext, NULL, screen, &dest );
     SDL_FreeSurface(stext);
   }
   else {
     throw 
     string("Couldn't allocate text sureface in printMessageValueAt");
   }
   }
   else{
	   std::cout<<"Please use correct font size"<<std::endl;
   }
}

void IOManager::printStringAfterMessage( const string& msg,
       Uint32 x, Uint32 y, std::string font ) const {
   printMessageAt(msg+inputString, x, y, font);
}

void IOManager::buildString(SDL_Event event) {
  if( inputString.size() <= MAX_STRING_SIZE) {
    unsigned ch = event.key.keysym.sym;
    if ( isalpha(ch) || isdigit(ch) || ch == ' ') {
      inputString += char(event.key.keysym.unicode);
    }
  }     
  if( event.key.keysym.sym == SDLK_BACKSPACE
      && inputString.length() > 0 ) {
      // remove a character from the end
      int length = inputString.size();
      inputString.erase( length - 1 );
  }
}

template void IOManager::
printMessageValueAt(const string& msg, float, Uint32, Uint32, std::string) const;

template void IOManager::
printMessageValueAt(const string& msg, unsigned, Uint32, Uint32, std::string) const;

template void IOManager::
printMessageValueAt(const string& msg, int, Uint32, Uint32, std::string) const;

