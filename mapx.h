#ifndef MAPX__H
#define MAPX__H

#include <iostream>
#include <vector>
#include <map>

#include "gamedata.h"

class MapX{
	public:
		~MapX(){}
		static MapX& getInstance(){
			static MapX instance;
			return instance;
		}
		std::vector<float> getY(int x);
	private:
		MapX():value(){}
		std::map<int, std::vector<float> > value;
		MapX(const MapX&);
		MapX& operator=(const MapX&);
		std::string intToString(int n);
};

#endif
