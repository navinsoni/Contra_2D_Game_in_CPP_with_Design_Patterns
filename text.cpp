#include "text.h"
#include <string.h>

void Text::print(const char* p){
	std::cout<<"reached here "<<std::endl;
	int i = 0;
	char temp;
	char* tempStr = new char[strlen(p)+1];
	strcpy(tempStr,p);
	int length = strlen(p);
	temp = p[i];
	while(i<length){
		//std::cout<<"reached here "<<std::endl;
		tempStr[i]=temp;
		temp = tempStr[i+1];
		tempStr[i+1]='\0';
		i++;
	//	IOManager::getInstance().printMessageAt(static_cast<std::string>(tempStr),100,100);
		SDLSound::getInstance()["gun"];
		usleep(500000);
		std::cout<<"test: "<<tempStr<<std::endl;
	}
}

