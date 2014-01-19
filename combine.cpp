#include "combine.h"
#include "vector2f.h"

Combine::Combine():
  screen( IOManager::getInstance().getScreen() ),
  sprite(),
  controls(0) {}

Combine::~Combine() {
	for (unsigned i=0; i<sprite.size(); i++){
		delete sprite[i];
	}
	SDL_FreeSurface(screen);
}

void Combine::draw() const {
	for (unsigned i=0; i<sprite.size(); i++){
		sprite[i]->draw();
	}
}

void Combine::update(Uint32 ticks){
	for (unsigned i=0; i<sprite.size(); i++){
		sprite[i]->setControls(controls);
		sprite[i]->update(ticks);
		//sprite[i]->draw();
	}
	SDL_Flip(screen);
}

void Combine::add(Intro* spr){
	sprite.push_back(spr);
}
