#include <cmath>
#include "spritemanager.h"
#include "bullets.h"

SpriteManager::~SpriteManager() { 
  // These deletions eliminate "definitely lost" and
  // "still reachable"s in Valgrind.
  delete player;
  std::list<Sprite*>::iterator it = enemy.begin();
  while(it!=enemy.end()){
	  delete (*it);
	  it = enemy.erase(it);
  }
}

SpriteManager::SpriteManager() :
  player(new Player("player","1")),
  playerAlive(true),
  enemyAlive(true),
  enemy(),
  viewport(Viewport::getInstance()),
  finalenemy(),
  controls(0),
  track(0)
{
  viewport.setObjectToTrack(player);
  for (int i=0; i<Gamedata::getInstance()->getXmlInt("enemyNumber");i++){
	  enemy.push_back(new EnemyStationary("enemy",intToString(i+1)));
  }
  for (int i=0; i<Gamedata::getInstance()->getXmlInt("bbulletNumber");i++){
	  enemy.push_back(new BigBullet("bbullet",intToString(i+1)));
  }
  for (int i=0; i<Gamedata::getInstance()->getXmlInt("boxenemyNumber");i++){
	  enemy.push_back(new BoxTarget("boxenemy",intToString(i+1)));
  }
  for (int i=0; i<Gamedata::getInstance()->getXmlInt("flameNumber");i++){
	  enemy.push_back(new Flame("flame",intToString(i+1)));
  }
	  finalenemy.push_back(new EnemyFinal1("enemyFinal1",""));
}

void SpriteManager::draw(){
	Bullets::getInstance().draw();
	std::list<Sprite*>::iterator it;
	for (it=enemy.begin(); it!=enemy.end();++it){
		(*it)->draw();
	}
	for (it=finalenemy.begin(); it!=finalenemy.end();++it){
		(*it)->draw();
	}
	if(!enemyAlive){
		IOManager::getInstance().printMessageCenteredAt("YOU WIN !!!",Gamedata::getInstance()->getXmlInt("viewHeight")*26/30,"small");
		IOManager::getInstance().printMessageCenteredAt("Press 'SPACE' OR 'A'  to Exit !!!",Gamedata::getInstance()->getXmlInt("viewHeight")*28/30,"smaller");
	}
	if(playerAlive)
    	player->draw();
	else{
		IOManager::getInstance().printMessageCenteredAt("GAME OVER !!!",Gamedata::getInstance()->getXmlInt("viewHeight")*26/30,"small");
		IOManager::getInstance().printMessageCenteredAt("Press 'SPACE' OR 'A'  to Exit !!!",Gamedata::getInstance()->getXmlInt("viewHeight")*28/30,"smaller");
	}

}

void SpriteManager::update(Uint32 ticks){
	viewport.update();
	Bullets::getInstance().update(ticks);
	Bullets::getInstance().checkCollision(enemy);
	if(!Bullets::getInstance().checkCollision(finalenemy)){
		std::cout<<"final enemy destroyed"<<std::endl;
		enemyAlive = false;
	}
	if(playerAlive){
	std::list<Sprite*>::iterator it;
	if(enemyAlive){
		for (it=enemy.begin(); it!=enemy.end();++it){
			(*it)->Location(player);
			(*it)->update(ticks);
		}
		for (it=finalenemy.begin(); it!=finalenemy.end();++it){
			(*it)->update(ticks);
		}
	}
	player->setControls(controls);
	player->update(ticks);
	if(!Bullets::getInstance().checkCollisionPlayer(player,enemy)){
		//std::cout<<"player busted Game Over...!!!"<<std::endl;
		playerAlive = false;
	}
		(player)->setControls(0xfe);
		(player)->update(0);
		if((player)->getControls()==0xfe){
			playerAlive = false;
		}
	}
}

std::string SpriteManager::intToString(int n){
	std::stringstream s;
	s << n;
	return s.str();
}

void SpriteManager::trackSprite(){
	/*if(track < enemy.size()){
	//	viewport.setObjectToTrack(enemy[track]);
	}
	else{
		track%2==0?viewport.setObjectToTrack(orb):viewport.setObjectToTrack(redorb);
	}
	track++;
	track %= (enemy.size()+2);
	*/
}
