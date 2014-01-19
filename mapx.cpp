#include "mapx.h"

std::vector<float> MapX::getY(int x){
	if(value.find(x)!=value.end()){
		return value[x];
	}
	else{
		std::vector<float> temp;
		for(int i=0; i<Gamedata::getInstance()->getXmlInt("mapdata"+intToString(x)+"Number"); i++){
			temp.push_back(Gamedata::getInstance()->getXmlFloat("mapdata"+intToString(x)+"Y"+intToString(i)));
			//std::cout<<i<<"   "<<temp[i]<<std::endl;
	}
	value[x]=temp;
	return temp;
	}
}


std::string MapX::intToString(int n){
	std::stringstream s;
	s << n;
	return s.str();
}
