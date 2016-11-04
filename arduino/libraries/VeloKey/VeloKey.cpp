#include "VeloKey.h"

void VeloKey::handleEvents(){
    uint8_t device, action;
    for(uint8_t ii = 0; ii < n_events_pending; ii++){
      switch(events[ii]){

      case SCROLL_LEFT_CW:
	for(uint8_t jj = 0; jj < n_listener; jj++){
	  listeners[jj]->onScrollLeftCW();
	}
	break;
	
      case SCROLL_LEFT_CCW:
	for(uint8_t jj = 0; jj < n_listener; jj++){
	  listeners[jj]->onScrollLeftCCW();
	}
	break;
	
      case SCROLL_LEFT_PRESS:
	for(uint8_t jj = 0; jj < n_listener; jj++){
	  listeners[jj]->onScrollLeftPress();
	}
	break;
	
      case SCROLL_LEFT_RELEASE:
	for(uint8_t jj = 0; jj < n_listener; jj++){
	  listeners[jj]->onScrollLeftRelease();
	}
	break;
	
      case SCROLL_RIGHT_CW:
	for(uint8_t jj = 0; jj < n_listener; jj++){
	  listeners[jj]->onScrollRightCW();
	}
	break;
	
      case SCROLL_RIGHT_CCW:
	for(uint8_t jj = 0; jj < n_listener; jj++){
	  listeners[jj]->onScrollRightCCW();
	}
	break;
	
      case SCROLL_RIGHT_PRESS:
	for(uint8_t jj = 0; jj < n_listener; jj++){
	  listeners[jj]->onScrollRightPress();
	}
	break;
 	
      case SCROLL_RIGHT_RELEASE:
	for(uint8_t jj = 0; jj < n_listener; jj++){
	  listeners[jj]->onScrollRightRelease();
	}
	break;
	
      case SCROLL_CENTER_CW:
	for(uint8_t jj = 0; jj < n_listener; jj++){
	  listeners[jj]->onScrollCenterCW();
	}
	break;
	
      case SCROLL_CENTER_CCW:
	for(uint8_t jj = 0; jj < n_listener; jj++){
	  listeners[jj]->onScrollCenterCCW();
	}
	break;
	
      case SCROLL_CENTER_PRESS:
	for(uint8_t jj = 0; jj < n_listener; jj++){
	  listeners[jj]->onScrollCenterPress();
	}
	break;
	
      case SCROLL_CENTER_RELEASE:
	for(uint8_t jj = 0; jj < n_listener; jj++){
	  listeners[jj]->onScrollCenterRelease();
	}
	break;

      case BUTTON_NORTH_PRESS:
	for(uint8_t jj = 0; jj < n_listener; jj++){
	  listeners[jj]->onButtonNorthPress();
	}
	break;
	
      case BUTTON_NORTH_RELEASE:
	for(uint8_t jj = 0; jj < n_listener; jj++){
	  listeners[jj]->onButtonNorthRelease();
	}
	break;

      case BUTTON_SOUTH_PRESS:
	for(uint8_t jj = 0; jj < n_listener; jj++){
	  listeners[jj]->onButtonSouthPress();
	}
	break;
	
      case BUTTON_SOUTH_RELEASE:
	for(uint8_t jj = 0; jj < n_listener; jj++){
	  listeners[jj]->onButtonSouthRelease();
	}
	break;

      case BUTTON_EAST_PRESS:
	for(uint8_t jj = 0; jj < n_listener; jj++){
	  listeners[jj]->onButtonEastPress();
	}
	break;
	
      case BUTTON_EAST_RELEASE:
	for(uint8_t jj = 0; jj < n_listener; jj++){
	  listeners[jj]->onButtonEastRelease();
	}
	break;

      case BUTTON_WEST_PRESS:
	for(uint8_t jj = 0; jj < n_listener; jj++){
	  listeners[jj]->onButtonWestPress();
	}
	break;
	
      case BUTTON_WEST_RELEASE:
	for(uint8_t jj = 0; jj < n_listener; jj++){
	  listeners[jj]->onButtonWestRelease();
	}
	break;
      }
    }
    n_events_pending = 0;
  }

  
