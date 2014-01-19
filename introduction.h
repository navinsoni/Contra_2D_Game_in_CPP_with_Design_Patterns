#ifndef INTRODUCTION__H
#define INTRODUCTION__H

#include <SDL.h>
#include <iostream>
#include <vector>

#include "clock.h"
#include "ioManager.h"
#include "intro.h"
#include "frame.h"
#include "framefactory.h"
#include "viewport.h"
#include "wiimote.h"

class Introduction : public Intro{
	public:
		Introduction();
		~Introduction();
		virtual void draw() const;
		virtual void update(Uint32 ticks);
		SDL_Surface *screen;
		std::string& Notes() { return Intro::Notes(); }
		void add(std::vector<Intro*> spr);
		uint32_t getPreviousTicks() { return prevticks; }
	
	private:
  		Clock& clock;
  		uint16_t controls;
		uint32_t prevticks;
		std::vector<std::vector<Intro*> > sprite;
  		Frame* const backgroundFrame;
		Introduction(const Introduction& intr);
		Introduction& operator=(const Introduction& intr);
};
#endif
