#ifndef INTRO__H
#define INTRO__H

#include <iostream>
#include <vector>
#include <string>


class Intro{
	public:
		Intro(): controls(0), notes(""), loopme(true) {}
		virtual ~Intro() {}
		virtual void draw() const = 0;
		virtual void update(Uint32 ticks) = 0;
  		void setControls(uint8_t c) { controls = c; }
  		bool loopMe() { return loopme; }
  		void loopMe(bool l) { loopme = l; }
  		uint8_t getControls() { return controls; }
		std::string& Notes() { return notes; }
		void Notes(const std::string& s ) { notes = s; }
  	
	private:
  		uint8_t controls;
		std::string notes;
		bool loopme;
};
#endif
