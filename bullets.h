#ifndef BULLETS__H
#define BULLETS__H

#include <SDL.h>
#include <iostream>
#include <list>

#include "sprite.h"
#include "explodingSprite.h"
#include "collisionStrategy.h"

class Bullets {
	public:
		Bullets() : sprites(), sprites_exploded(), strat() { }
		~Bullets();
		static Bullets& getInstance(){
			static Bullets instance;
			return instance;
		}
		void draw() const;
		void update(Uint32 ticks);
		void add(Sprite* ele);
		void remove(Sprite* ele);
		bool checkCollision(std::list<Sprite*>& enemy);
		bool checkCollisionPlayer(Sprite* player, std::list<Sprite*>& enemy);

	private:
		std::list<Sprite*> sprites;
		std::list<Sprite*> sprites_exploded;
		PerPixelCollisionStrategy strat;
};

#endif
