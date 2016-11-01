#include "events.h"

class VeloKeyListener{
 public:
  void onScrollLeftCW(){Serial.println("OnScrollLeftCW()");}
  void onScrollLeftCCW(){Serial.println("OnScrollLeftCCW()");}
  void onScrollLeftPress(){Serial.println("OnScrollLeftPress()");}
  void onScrollLeftRelease(){Serial.println("OnScrollLeftRelease()");}

  void onScrollRightCW(){Serial.println("OnScrollRightCW()");}
  void onScrollRightCCW(){Serial.println("OnScrollRightCCW()");}
  void onScrollRightPress(){Serial.println("OnScrollRightPress()");}
  void onScrollRightRelease(){Serial.println("OnScrollRightRelease()");}

  void onScrollCenterCW(){Serial.println("OnScrollCenterCW()");}
  void onScrollCenterCCW(){Serial.println("OnScrollCenterCCW()");}
  void onScrollCenterPress(){Serial.println("OnScrollCenterPress()");}
  void onScrollCenterRelease(){Serial.println("OnScrollCenterRelease()");}

  void onButtonNorthPress(){Serial.println("OnButtonNorthPress()");}
  void onButtonNorthRelease(){Serial.println("OnButtonNorthRelease()");}
  
  void onButtonSouthPress(){Serial.println("OnButtonSouthPress()");}
  void onButtonSouthRelease(){Serial.println("OnButtonSouthRelease()");}

  void onButtonEastPress(){Serial.println("OnButtonEastPress()");}
  void onButtonEastRelease(){Serial.println("OnButtonEastRelease()");}
  
  void onButtonWestPress(){Serial.println("OnButtonWestPress()");}
  void onButtonWestRelease(){Serial.println("OnButtonWestRelease()");}
};

const uint8_t max_listeners = 5;
const uint8_t max_events = 10;

class VeloKey{
 public:
  VeloKeyListener *listeners[max_listeners];
  uint8_t n_listener;
  uint8_t events[max_events];
  uint8_t n_events_pending;
  Uart *ncodr_p;
    
  VeloKey(){
    n_listener = 0;
    n_events_pending = 0;
  }

  void subscribe(VeloKeyListener *listener){
    if(n_listener < max_listeners){
      listeners[n_listener] = listener;
      n_listener += 1;
    }
  }

  void captureEvents(){ // call as often as possible
    uint8_t event_count = ncodr_p->available();
    
    for(uint8_t ii = 0; ii < event_count; ii++){
      events[n_events_pending++] = ncodr_p->read();
    }
  }

  void handleEvents(){
    uint8_t device, action;
    for(uint8_t ii = 0; ii < n_events_pending; ii++){
      switch(events[ii]){

      case SCROLL_LEFT_CW:
	for(uint8_t jj = 0; jj < n_listener && n_events_pending < max_events; jj++){
	  listeners[jj]->onScrollLeftCW();
	}
	break;
	
      case SCROLL_LEFT_CCW:
	for(uint8_t jj = 0; jj < n_listener && n_events_pending < max_events; jj++){
	  listeners[jj]->onScrollLeftCCW();
	}
	break;
	
      case SCROLL_LEFT_PRESS:
	for(uint8_t jj = 0; jj < n_listener && n_events_pending < max_events; jj++){
	  listeners[jj]->onScrollLeftPress();
	}
	break;
	
      case SCROLL_LEFT_RELEASE:
	for(uint8_t jj = 0; jj < n_listener && n_events_pending < max_events; jj++){
	  listeners[jj]->onScrollLeftRelease();
	}
	break;
	
      case SCROLL_RIGHT_CW:
	for(uint8_t jj = 0; jj < n_listener && n_events_pending < max_events; jj++){
	  listeners[jj]->onScrollRightCW();
	}
	break;
	
      case SCROLL_RIGHT_CCW:
	for(uint8_t jj = 0; jj < n_listener && n_events_pending < max_events; jj++){
	  listeners[jj]->onScrollRightCCW();
	}
	break;
	
      case SCROLL_RIGHT_PRESS:
	for(uint8_t jj = 0; jj < n_listener && n_events_pending < max_events; jj++){
	  listeners[jj]->onScrollRightPress();
	}
	break;
 	
      case SCROLL_RIGHT_RELEASE:
	for(uint8_t jj = 0; jj < n_listener && n_events_pending < max_events; jj++){
	  listeners[jj]->onScrollRightRelease();
	}
	break;
	
      case SCROLL_CENTER_CW:
	for(uint8_t jj = 0; jj < n_listener && n_events_pending < max_events; jj++){
	  listeners[jj]->onScrollCenterCW();
	}
	break;
	
      case SCROLL_CENTER_CCW:
	for(uint8_t jj = 0; jj < n_listener && n_events_pending < max_events; jj++){
	  listeners[jj]->onScrollCenterCCW();
	}
	break;
	
      case SCROLL_CENTER_PRESS:
	for(uint8_t jj = 0; jj < n_listener && n_events_pending < max_events; jj++){
	  listeners[jj]->onScrollCenterPress();
	}
	break;
	
      case SCROLL_CENTER_RELEASE:
	for(uint8_t jj = 0; jj < n_listener && n_events_pending < max_events; jj++){
	  listeners[jj]->onScrollCenterRelease();
	}
	break;

      case BUTTON_NORTH_PRESS:
	for(uint8_t jj = 0; jj < n_listener && n_events_pending < max_events; jj++){
	  listeners[jj]->onButtonNorthPress();
	}
	break;
	
      case BUTTON_NORTH_RELEASE:
	for(uint8_t jj = 0; jj < n_listener && n_events_pending < max_events; jj++){
	  listeners[jj]->onButtonNorthRelease();
	}
	break;

      case BUTTON_SOUTH_PRESS:
	for(uint8_t jj = 0; jj < n_listener && n_events_pending < max_events; jj++){
	  listeners[jj]->onButtonSouthPress();
	}
	break;
	
      case BUTTON_SOUTH_RELEASE:
	for(uint8_t jj = 0; jj < n_listener && n_events_pending < max_events; jj++){
	  listeners[jj]->onButtonSouthRelease();
	}
	break;

      case BUTTON_EAST_PRESS:
	for(uint8_t jj = 0; jj < n_listener && n_events_pending < max_events; jj++){
	  listeners[jj]->onButtonEastPress();
	}
	break;
	
      case BUTTON_EAST_RELEASE:
	for(uint8_t jj = 0; jj < n_listener && n_events_pending < max_events; jj++){
	  listeners[jj]->onButtonEastRelease();
	}
	break;

      case BUTTON_WEST_PRESS:
	for(uint8_t jj = 0; jj < n_listener && n_events_pending < max_events; jj++){
	  listeners[jj]->onButtonWestPress();
	}
	break;
	
      case BUTTON_WEST_RELEASE:
	for(uint8_t jj = 0; jj < n_listener && n_events_pending < max_events; jj++){
	  listeners[jj]->onButtonWestRelease();
	}
	break;
      }
    }
  }
  // drawing functions
};
