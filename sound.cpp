#include <ctime>
#include "sound.h"
using std::string;

SDLSound::~SDLSound() {
  std::cout << "Cleaning up sounds ..." << std::endl;
  std::clock_t start = std::clock();
  Mix_HaltMusic();
  Mix_FreeMusic(music);
  Mix_CloseAudio();
  while(!sound.empty()){
  	  std::map<std::string, Mix_Chunk*>::iterator it = sound.begin();
	  Mix_FreeChunk(it->second);
	  sound.erase(it);
  }
  channel.clear();
  std::clock_t duration = std::clock() - start;
  std::cout << "Clean up took " << duration << " ticks\n";
}

SDLSound::SDLSound() :
  soundvalue(true),
  volume(SDL_MIX_MAXVOLUME/4), 
  music(NULL),
  audioRate(22050), 
  audioChannels(2), 
  audioBuffers(4096),
  sound(),
  channel()
{
  if(Mix_OpenAudio(audioRate, MIX_DEFAULT_FORMAT, audioChannels, 
                   audioBuffers)){
    throw string("Unable to open audio!");
  }
  //music = Mix_LoadMUS("sound/100Years.mp3");
  music = Mix_LoadMUS("sound/Jungle_Theme.mp3");
  // Need to install midi to play the following:
  //music = Mix_LoadMUS("sound/ballad2.mid");
  if (!music) throw string("Couldn't load Jungle_Theme.mp3")+Mix_GetError();

  startMusic();
  sound["boom"] = Mix_LoadWAV("sound/Boom.wav");
  channel["boom"] = channel.size();
  sound["gun"] = Mix_LoadWAV("sound/Gun.wav");
  channel["gun"] = channel.size();
  sound["phaser"] = Mix_LoadWAV("sound/phaser.wav");
  channel["phaser"] = channel.size();
  sound["putt"] = Mix_LoadWAV("sound/Putt1.wav");
  channel["putt"] = channel.size();
  sound["explosion"] = Mix_LoadWAV("sound/explosion.wav");
  channel["explosion"] = channel.size();
  sound["cannon"] = Mix_LoadWAV("sound/cannon.wav");
  channel["cannon"] = channel.size();
}

void SDLSound::toggleMusic() {
  if( Mix_PausedMusic() ) { 
    Mix_ResumeMusic(); 
  } 
  else { 
    Mix_PauseMusic(); 
  } 
}


void SDLSound::musicStart() {
	music = Mix_LoadMUS("sound/Jungle_Theme.mp3");
  	if (!music) throw string("Couldn't load Jungle_Theme.mp3")+Mix_GetError();
	Mix_PlayMusic(music, -1);
}


void SDLSound::musicStop() {
    Mix_PauseMusic(); 
}

void SDLSound::operator[](const std::string s) {
	if(Sound()){
  		std::map<std::string, Mix_Chunk*>::iterator it = sound.find(s);
		if(it!=sound.end()){
			Mix_VolumeChunk(it->second, volume);
			channel[s] = Mix_PlayChannel(channel[s], it->second, 0);
		}
	}
}

void SDLSound::startMusic() {
  Mix_VolumeMusic(volume);
  Mix_PlayMusic(music, -1);
}

void SDLSound::stopMusic() {
  Mix_HaltMusic();
  Mix_FreeMusic(music);
}

