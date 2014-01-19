#ifndef COMBINE__H
#define COMBINE__H

#include <SDL.h>
#include <iostream>
#include <vector>
#include "ioManager.h"
#include "intro.h"

class Combine : public Intro{
	public:
		Combine();
		~Combine();
		virtual void draw() const;
		virtual void update(Uint32 ticks);
		SDL_Surface *screen;
		void add(Intro* spr);
		void setControls(const uint8_t c) { controls = c; }
	
	private:
		std::vector<Intro*> sprite;
		Combine(const Combine& intr);
		Combine& operator=(const Combine& intr);
		uint8_t controls;
};
#endif
