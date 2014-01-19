#include "bullets.h"

Bullets::~Bullets(){
	std::list<Sprite*>::iterator it;
	for(it=sprites.begin(); it!=sprites.end(); ++it){
		delete (*it);
	}
	for(it=sprites_exploded.begin(); it!=sprites_exploded.end(); ++it){
		delete (*it);
	}
}

void Bullets::draw() const {
	std::list<Sprite*>::const_iterator it;
	for(it=sprites.begin(); it!=sprites.end(); ++it){
		(*it)->draw();
	}
	
	for(it=sprites_exploded.begin(); it!=sprites_exploded.end(); ++it){
		(*it)->draw();
	}
}

void Bullets::update(Uint32 ticks) {
	std::list<Sprite*>::iterator it;
	for(it=sprites.begin(); it!=sprites.end(); ++it){
		(*it)->update(ticks);
		if(((*it)->getControls())==0xFF){
			delete (*it);
			it = sprites.erase(it);
		}
	}
	for(it=sprites_exploded.begin(); it!=sprites_exploded.end(); ++it){
		(*it)->update(ticks);
		if(static_cast<ExplodingSprite*>(*it)->chunkCount() == 0 ){
			delete (*it);
			it = sprites.erase(it);
		}
	}
}

void Bullets::add(Sprite* ele){
	sprites.push_back(ele);
}

void Bullets::remove(Sprite* ele){
	std::list<Sprite*>::iterator it;
	if(it!=sprites.end() || ele){
		delete (*it);
		sprites.erase(it);
	}
}


bool Bullets::checkCollision(std::list<Sprite*>& enemy){
	std::list<Sprite*>::iterator it_enemy = enemy.begin();
	bool status = true;
	while(it_enemy!=enemy.end()){
		std::list<Sprite*>::iterator it_sprites;
		for(it_sprites=sprites.begin(); it_sprites!=sprites.end(); ++it_sprites){
			if(strat.execute(*(*it_sprites),*(*it_enemy)) && (*it_sprites)->getNumber()=="1"){
				delete (*it_sprites);
				it_sprites = sprites.erase(it_sprites);
				(*it_enemy)->setControls(0xff);
				(*it_enemy)->update(0);
				if((*it_enemy)->getControls()==0xff){
					sprites_exploded.push_back(new ExplodingSprite(*(*it_enemy)));
					delete (*it_enemy);
					it_enemy = enemy.erase(it_enemy);
					status = false;
				}
				--it_sprites;
				break;
			}
		}
		++it_enemy;
	}
	return status;
}


bool Bullets::checkCollisionPlayer(Sprite* player, std::list<Sprite*>& enemy){
	std::list<Sprite*>::iterator it_enemy = enemy.begin();

	while(it_enemy!=enemy.end()){
			if(strat.execute(*(player),*(*it_enemy))){
				(*it_enemy)->setControls(0xff);
				(*it_enemy)->update(0);
				if((*it_enemy)->getControls()==0xff){
					sprites_exploded.push_back(new ExplodingSprite(*(*it_enemy)));
					delete (*it_enemy);
					it_enemy = enemy.erase(it_enemy);
				}
				(player)->setControls(0xff);
				(player)->update(0);
				if((player)->getControls()==0xff){
					sprites_exploded.push_back(new ExplodingSprite(*(player)));
					return false;
				}
			}
		++it_enemy;
	}
		std::list<Sprite*>::iterator it_sprites;
		for(it_sprites=sprites.begin(); it_sprites!=sprites.end(); ++it_sprites){
			if(strat.execute(*(*it_sprites),*(player)) && (*it_sprites)->getNumber()!="1"){
				delete (*it_sprites);
				it_sprites = sprites.erase(it_sprites);
				(player)->setControls(0xff);
				(player)->update(0);
				if((player)->getControls()==0xff){
					sprites_exploded.push_back(new ExplodingSprite(*(player)));
					return false;
				}
			}
		}
	return true;
}
