#include "framefactory.h"


FrameFactory::FrameFactory():frame(),surface(){
}

FrameFactory::~FrameFactory(){
	std::cout<<"framefactory destructor"<<std::endl;
	while(!frame.empty()){
		std::map<std::string, std::vector<Frame*> >::iterator it=frame.begin();
		for(unsigned int i = 0; i < it->second.size(); i++){
			delete  it->second[i];
		}
		it->second.clear();
		std::cout<<"framefactory delete frame "<<it->first<<std::endl;
		frame.erase(it);
	}

	while(!surface.empty()){
		std::map<std::string, SDL_Surface* >::iterator it=surface.begin();
		std::cout<<"framefactory delete surface "<<it->first<<std::endl;
		SDL_FreeSurface(it->second);
		surface.erase(it);
	}
}

std::vector<Frame*> FrameFactory::getFrame(std::string key, std::string action = ""){
	std::vector<Frame*> f;
	if (frame.find(key+action) != frame.end()){
		f = frame[key+action];
	}
	else{
		SDL_Surface* surf = NULL;
		if (surface.find(key) != surface.end())
			surf = surface[key];
		else{
			surf = IOManager::getInstance().loadAndSet(Gamedata::getInstance()->getXmlStr(key+"File"),Gamedata::getInstance()->getXmlBool(key+"Transparency"));
			surface[key] = surf;
		}
		for(int j = 0; j < Gamedata::getInstance()->getXmlInt(key + action  + "NumberOfFramesY"); j++){
		for(int i = 0; i < Gamedata::getInstance()->getXmlInt(key + action  + "NumberOfFrames"); i++){
		f.push_back(new Frame(surf,
                Gamedata::getInstance()->getXmlInt(key + action + "Width")/Gamedata::getInstance()->getXmlInt(key + action + "NumberOfFrames"), 
                Gamedata::getInstance()->getXmlInt(key + action + "Height")/Gamedata::getInstance()->getXmlInt(key + action + "NumberOfFramesY"),
				Gamedata::getInstance()->getXmlInt(key + action + "Width")*i/Gamedata::getInstance()->getXmlInt(key + action + "NumberOfFrames") + Gamedata::getInstance()->getXmlInt(key + action + "SrcX"),
				Gamedata::getInstance()->getXmlInt(key + action + "Height")*j/Gamedata::getInstance()->getXmlInt(key + action + "NumberOfFramesY") + Gamedata::getInstance()->getXmlInt(key + action + "SrcY")));
		}
		}
		frame[key + action] = f;
	}
	return f;
}

