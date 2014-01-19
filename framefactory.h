#ifndef FRAMEFACTORY__H
#define FRAMEFACTORY__H
#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include "ioManager.h"
#include "gamedata.h"
#include "frame.h"

class FrameFactory{
	public:
		~FrameFactory();
		static FrameFactory& getInstance(){
			static FrameFactory instance;
			return instance;
		}

		std::vector<Frame*> getFrame(std::string key, std::string action);
		
		private:
			FrameFactory();
			FrameFactory(const FrameFactory& f);
			FrameFactory& operator=(const FrameFactory& f);
			std::map <std::string, std::vector<Frame*> > frame;
			std::map <std::string, SDL_Surface*> surface;
};

#endif
