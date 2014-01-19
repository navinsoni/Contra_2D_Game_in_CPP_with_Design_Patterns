#include "introduction.h"
#include "vector2f.h"

Introduction::Introduction():
  screen( IOManager::getInstance().getScreen() ),
  clock( Clock::getInstance() ),
  controls(0),
  prevticks(0),
  sprite(),
  backgroundFrame(FrameFactory::getInstance().getFrame("menuFrame","")[0])
  {}

Introduction::~Introduction() {
	for (unsigned i=0; i<sprite.size(); i++){
	for (unsigned j=0; j<sprite[i].size(); j++){
		delete sprite[i][j];
	}
	}
	SDL_FreeSurface(screen);
}

void Introduction::draw() const {
	/*for (unsigned i=0; i<sprite.size(); i++){
		//sprite[i]->draw();
	}*/
}

void Introduction::update(Uint32 ticks){
	SDL_Event event;
	unsigned i=0;
	uint16_t tempc = 0;
	bool keyCatch = false;
	bool done = false;
	prevticks = ticks;
  	Uint8 *keystate;
	loopMe(true);
	Intro::Notes("");
	while(i<sprite.size() && !done && loopMe()){
		ticks = clock.getElapsedTicks();
		backgroundFrame->draw(Viewport::getInstance().X(),Viewport::getInstance().Y());
		for(unsigned j=0; j<sprite[i].size(); j++){
		sprite[i][j]->setControls(controls);
		sprite[i][j]->update(ticks);
		sprite[i][j]->draw();
		sprite[i][j]->setControls(0x00);
		if(!sprite[i][j]->loopMe()){
			sprite[i][j]->loopMe(true);
			loopMe(false);
			//std::cout<<"loop me is false"<<std::endl;
			Intro::Notes(sprite[i][j]->Notes());
			//std::cout<<sprite[i][j]->Notes()<<" finally done"<<std::endl;
			break;
		}
		else{
			//std::cout<<"loop me is true"<<std::endl;
		}
		}
		controls=0;
		SDL_Flip(screen);
		//std::cout << "At Location: "<<i<<std::endl;
		if(WiiMote::getInstance().getStatus()){
			std::cout<<"wiiMote Connected"<<std::endl;
			tempc = WiiMote::getInstance().getControls();
			if(!keyCatch){ controls = tempc; keyCatch = true; }
			if(tempc==0x0000) { keyCatch = false; }
		}
		else{
			std::cout<<"wiiMote disconnected"<<std::endl;
			SDL_PollEvent(&event);
    			keystate = SDL_GetKeyState(NULL);
    			if (event.type ==  SDL_QUIT) { ticks = clock.getElapsedTicks(); break; }
    			if(event.type == SDL_KEYUP) { keyCatch = false; }
    			if(event.type == SDL_KEYDOWN) {
      				if(!keyCatch){
      					switch ( event.key.keysym.sym ) {
        					case SDLK_ESCAPE : case SDLK_q : case SDLK_BACKSPACE : controls|=0x100; break;
        					case SDLK_p      : {
          					if (!keyCatch) {
            						keyCatch = true;
            						if ( clock.isPaused() ) clock.unpause();
            						else clock.pause();
          					}
          					break;
        					}
        					default          : break;
      					}
      				}
      
      			if(!keyCatch){
				controls = 0;
        			if(keystate[SDLK_q])       		controls |= (0x0100);
        			if(keystate[SDLK_BACKSPACE])    controls |= (0x0100);
        			if(keystate[SDLK_ESCAPE])       controls |= (0x0100);
        			if(keystate[SDLK_d])       controls |= (0x0080);
        			if(keystate[SDLK_a])       controls |= (0x0040);
        			if(keystate[SDLK_w])       controls |= (0x0020);
        			if(keystate[SDLK_s])       controls |= (0x0010);
        			if(keystate[SDLK_RETURN])  controls |= (0x0008);
        			if(keystate[SDLK_f]) 	   controls |= (0x0004);
        			keyCatch = true;
      			}
      }
    }
      		if(controls&0x0100) { done = true; ticks = clock.getElapsedTicks(); }
      		else if(controls&0x0080) { i++; }
      		//if(controls&0x0040) { if(i>0) i--; }
  }
  loopMe(true);
}

void Introduction::add(std::vector<Intro*> spr){
	sprite.push_back(spr);
}
