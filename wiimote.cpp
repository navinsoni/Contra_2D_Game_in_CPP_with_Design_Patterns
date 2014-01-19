#include "wiimote.h"


WiiMote::~WiiMote(){
	if(!onOff){
		if(cwiid_disconnect(g_wiimote)){
		std::cout<<"disconnection failed"<<std::endl;
		}
		else{
		std::cout<<"disconnected successful"<<std::endl;
		}
	}
}


uint16_t WiiMote::getControls(){
	if(!cwiid_get_state(g_wiimote, &g_wii_state)){
		uint16_t temp = g_wii_state.buttons;
		if(temp!=0){
		uint16_t controls = 0;
		if (temp&0x0200) controls|=0x0080;
		if (temp&0x0100) controls|=0x0040;
		if (temp&0x0800) controls|=0x0020;
		if (temp&0x0400) controls|=0x0010;
		if (temp&0x0008) controls|=0x0008;
		if (temp&0x0004) controls|=0x0004;
		if (temp&0x0080) controls|=0x0800;
		if (temp&0x1000) controls|=0x0400;
		if (temp&0x0010) controls|=0x0200;
		if (temp&0x0002) controls|=0x0100;
		if (temp&0x0001) controls|=0x1000;
		std::cout<<"button: "<<controls<<std::endl;
		return controls;
		}
	}
	return 0x0000;
}


void WiiMote::start(){
	if(onOff){
		onOff = false;	
		std::cout<<"press keys:"<<std::endl;
		// Establish a continous and non-blocking connection
		g_wiimote = cwiid_connect(&g_bdaddr,
		CWIID_FLAG_CONTINUOUS|CWIID_FLAG_NONBLOCK);
		if(g_wiimote==NULL){
			std::cout<<"connection failed"<<std::endl;
		}
		else{
			std::cout<<"connection successful"<<std::endl;
		}
		cwiid_command(g_wiimote, CWIID_CMD_RPT_MODE,CWIID_RPT_IR|CWIID_RPT_ACC|CWIID_RPT_BTN);
		if(!cwiid_set_rpt_mode(g_wiimote,CWIID_RPT_IR|CWIID_RPT_ACC|CWIID_RPT_BTN)){
			inUse=true;
		}
	}
	else{
		inUse=true;
	}
}


void WiiMote::stop(){
	inUse = false;
}
