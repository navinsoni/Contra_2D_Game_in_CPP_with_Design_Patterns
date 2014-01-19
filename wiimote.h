#ifndef WIIMOTE__H
#define WIIMOTE__H

#include <iostream>
#include <cwiid.h>

class WiiMote{
	public:
		WiiMote() : g_bdaddr({{0, 0, 0, 0, 0, 0}}), g_wiimote(NULL), g_wii_state(), onOff(true), inUse(false) {}
		~WiiMote();
		
		static WiiMote& getInstance(){
			static WiiMote instance;
			return instance;
		}

		bool getStatus() { return inUse; }
		uint16_t getControls();
		void start();
		void stop();
	
	private:
		bdaddr_t g_bdaddr;
		cwiid_wiimote_t *g_wiimote;
		struct cwiid_state g_wii_state;
		bool onOff;
		bool inUse;
		WiiMote(const WiiMote&);
		WiiMote& operator=(const WiiMote&);
};
#endif
