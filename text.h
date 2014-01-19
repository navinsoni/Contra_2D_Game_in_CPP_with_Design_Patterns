#ifndef TEXT__H
#define TEXT__H

#include <iostream>
#include "sound.h"
#include "ioManager.h"

class Text{
	public:
		static Text& getInstance(){
			static Text instance;
			return instance;
		}
	
		void print(const char* p);
	
	private:
		Text(){ }
		Text(const Text&);
		Text& operator=(const Text&);
};

#endif
