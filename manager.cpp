#include <cmath>
#include "manager.h"
#include "text.h"

Manager::~Manager() { 
  // These deletions eliminate "definitely lost" and
  // "still reachable"s in Valgrind.
  SDL_FreeSurface(screen);
  delete Gamedata::getInstance();
}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  controls(0),
  screen( io.getScreen() ),
  world(FrameFactory::getInstance().getFrame("background2","")[0],4),
  world1(FrameFactory::getInstance().getFrame("background1","")[0],2),
  world2(FrameFactory::getInstance().getFrame("background","")[0]),
  spriteManager(),
  t1(),
  intro(),
  menu()
{
  t1.push_back(new Name("name",""));
  intro.add(t1);
  t1.clear();
  t1.push_back(new Scrolling());
  intro.add(t1);
  t1.clear();
  t1.push_back(new Menu());
  menu.add(t1);
  t1.clear();
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  atexit(SDL_Quit);
  SDLSound::getInstance();
  intro.update(0);
}

void Manager::help(){
	io.printMessageCenteredAt("HELP !!!",Gamedata::getInstance()->getXmlInt("viewHeight")*26/30,"small");
	io.printMessageAt("Press 'm' OR 'HOME' for Menu",Gamedata::getInstance()->getXmlInt("viewWidth")*2/5,Gamedata::getInstance()->getXmlInt("viewHeight")*28/30,"smaller");
}

void Manager::draw(){
	world.draw();
	world1.draw();
	world2.draw();
	spriteManager.draw();
}

void Manager::update(Uint32 ticks){
	world.update();
	world1.update();
	world2.update();
	spriteManager.update(ticks);
}

void Manager::play() {
  SDL_Event event;

  bool done	         = false;
  bool keyCatch		 = false;
  bool helphelp		 = false;
  uint32_t prevticks;
  menu.update(0);
  while(!(menu.Notes()=="Start" || menu.Notes()=="Exit")){
  	menu.update(0);
  }
  if(menu.Notes() == "Exit"){
  	done = true;
  }
  Uint8 *keystate;
  Uint32 ticks = 0;
  while ( not done ) {
	draw();
	if (helphelp){
		help();
	}
    
	SDL_Flip(screen);
    SDL_PollEvent(&event);
    keystate = SDL_GetKeyState(NULL);
    if (event.type ==  SDL_QUIT) { break; }

	if(WiiMote::getInstance().getStatus()){
		std::cout<<"wiiMote Connected in manager"<<std::endl;
		controls = WiiMote::getInstance().getControls();
		if(controls==0x0000) { keyCatch = false; }
	}
	else{
	//	std::cout<<"wiiMote disconnected"<<std::endl;
    	if(event.type == SDL_KEYUP) {
			keyCatch = false;
		}
    		
		controls = 0;
    	if(keystate[SDLK_d])       	controls |= (0x0080);
    	if(keystate[SDLK_a])       	controls |= (0x0040);
    	if(keystate[SDLK_w])       	controls |= (0x0020);
    	if(keystate[SDLK_s])       	controls |= (0x0010);
    	if(keystate[SDLK_SPACE])   	controls |= (0x0008);
    	if(keystate[SDLK_f]) 		controls |= (0x0004);
    	if(keystate[SDLK_m]) 		controls |= (0x0800);
    	if(keystate[SDLK_F1]) 		controls |= (0x1000);
    	if(keystate[SDLK_p]) 		controls |= (0x0100);
	}				

	if(!spriteManager.getStatusPlayer() && (controls&0x0008)){
		std::cout<<"player died...!!!"<<std::endl;
		done = true;
	}
	
	
	if(!spriteManager.getStatusEnemy() && (controls&0x0008)){
		std::cout<<"enemy died...!!!"<<std::endl;
		done = true;
	}

	if(controls&0x0800){
		if(!keyCatch){
    	   	keyCatch=true;
    	   	menu.update(ticks);
    	   	prevticks = menu.getPreviousTicks();
    	   	std::cout<<menu.Notes()<<" in manager class"<<std::endl;
  			while(!(menu.Notes()=="Start" || menu.Notes()=="Exit")){
				menu.update(prevticks);
			}
			if(menu.Notes() == "Exit"){
			 	done = true;
			}
       	 }
	}	

	if(controls&0x1000){
		helphelp = true;
	}
	else{
		helphelp = false;
	}

	if(controls&0x0100){
        if (!keyCatch) {
        keyCatch = true;
        if ( clock.isPaused() ) clock.unpause();
        else clock.pause();
      }
	}
	//std::cout<<"controls: "<< controls << tempc << std::endl;
	spriteManager.setControls(controls);

	if(prevticks!=0){
		clock.getElapsedTicks();
	}
	
    ticks = prevticks + clock.getElapsedTicks();
	prevticks = 0;
	update(ticks);
  }
}
