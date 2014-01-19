#ifndef SOUND__H
#define SOUND__H

#include  <iostream>
#include  <string>
#include  <vector>
#include  <map>
#include <stdlib.h>
#include <SDL.h>
#include <SDL/SDL_mixer.h>

#include "gamedata.h"

// In this demo, we use Mix_Music *Mix_LoadMUS(const char *file)
// Where file is the name of the music file to use. 
//
// SDL_mixer supports music and sound samples from the following formats:
// - WAVE/RIFF (.wav)
// - AIFF (.aiff)
// - VOC (.voc)
// - MOD (.mod .xm .s3m .669 .it .med and more) using included mikmod
// - MIDI (.mid) using timidity or native midi hardware
// - OggVorbis (.ogg) requiring ogg/vorbis libraries on system
// - MP3 (.mp3) requiring SMPEG library on system
// - also any command-line player, which is not mixed by SDL_mixer...
//   that requires a command to play with.

class SDLSound {
public:
  ~SDLSound();

  static SDLSound& getInstance(){
	  static SDLSound instance;
	  return instance;
  }

  void startMusic();
  void stopMusic();      // stop all sounds
  void toggleMusic();    // toggle music on/off
  void musicStart();
  void musicStop();      // stop all sounds
  bool Sound()  { return soundvalue; }
  void Sound(const bool s) { soundvalue=s; }
  void operator[](const std::string s);  // play the indexed sound
private:
  SDLSound();
  bool soundvalue;
  int volume;
  Mix_Music *music;

  int audioRate;
  int audioChannels;
  int audioBuffers;
  std::map<const std::string, Mix_Chunk*> sound;
  std::map<const std::string, unsigned> channel;
  SDLSound(const SDLSound&);
  SDLSound& operator=(const SDLSound&);
};

#endif
