#ifndef VELOKEY_H
#define VELOKEY_H

#include "events.h"
#include "Adafruit_ST7735.h"

#define ncodr Serial1

const uint8_t max_listeners = 5;
const uint8_t max_events    = 10;
const uint8_t TFT_CS        = 5;  
const uint8_t TFT_RST       = 9;  
const uint8_t TFT_DC        = 6;
const uint8_t TFT_SCLK      = 13;   // set these to be whatever pins you like!
const uint8_t TFT_MOSI      = 11;   // set these to be whatever pins you like!
  
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, 
				      TFT_SCLK, TFT_RST);
Adafruit_ST7735 *tft_p      = &tft;

class VeloKeyListener{
 public:
  virtual void onScrollLeftCW(){Serial.println("OnScrollLeftCW()");}
  virtual void onScrollLeftCCW(){Serial.println("OnScrollLeftCCW()");}
  virtual void onScrollLeftPress(){Serial.println("OnScrollLeftPress()");}
  virtual void onScrollLeftRelease(){Serial.println("OnScrollLeftRelease()");}

  virtual void onScrollRightCW(){Serial.println("OnScrollRightCW()");}
  virtual void onScrollRightCCW(){Serial.println("OnScrollRightCCW()");}
  virtual void onScrollRightPress(){Serial.println("OnScrollRightPress()");}
  virtual void onScrollRightRelease(){Serial.println("OnScrollRightRelease()");}

  virtual void onScrollCenterCW(){Serial.println("OnScrollCenterCW()");}
  virtual void onScrollCenterCCW(){Serial.println("OnScrollCenterCCW()");}
  virtual void onScrollCenterPress(){Serial.println("OnScrollCenterPress()");}
  virtual void onScrollCenterRelease(){Serial.println("OnScrollCenterRelease()");}

  virtual void onButtonNorthPress(){Serial.println("OnButtonNorthPress()");}
  virtual void onButtonNorthRelease(){Serial.println("OnButtonNorthRelease()");}
  
  virtual void onButtonSouthPress(){Serial.println("OnButtonSouthPress()");}
  virtual void onButtonSouthRelease(){Serial.println("OnButtonSouthRelease()");}

  virtual void onButtonEastPress(){Serial.println("OnButtonEastPress()");}
  virtual void onButtonEastRelease(){Serial.println("OnButtonEastRelease()");}
  
  virtual void onButtonWestPress(){Serial.println("OnButtonWestPress()");}
  virtual void onButtonWestRelease(){Serial.println("OnButtonWestRelease()");}
};

class VeloKey{
 public:
  VeloKeyListener *listeners[max_listeners];
  uint8_t n_listener;
  uint8_t events[max_events];
  uint8_t n_events_pending;
    
  VeloKey(){
    n_listener = 0;
    n_events_pending = 0;
  }

  void begin(){
  }
  
  void subscribe(VeloKeyListener *listener){
    if(n_listener < max_listeners){
      listeners[n_listener] = listener;
      n_listener += 1;
    }
  }

  void captureEvents(){ // call as often as possible
    uint8_t event_count = ncodr.available();
    
    for(uint8_t ii = 0; ii < event_count && ii < max_events; ii++){
      events[n_events_pending++] = ncodr.read();
    }
  }

  void handleEvents();

// drawing functions
  void fillRect(uint16_t, uint16_t, uint16_t, uint16_t, uint16_t);
  void drawRect(uint16_t, uint16_t, uint16_t, uint16_t, uint16_t);
  void fillCircle(uint16_t, uint16_t, uint16_t, uint16_t);
  void drawCircle(uint16_t, uint16_t, uint16_t, uint16_t);
  void fillTriangle(uint16_t x1, uint16_t y1,
		    uint16_t x2, uint16_t y2,
		    uint16_t x3, uint16_t y3,
		    uint16_t color)
  void drawTriangle(uint16_t x1, uint16_t y1,
		    uint16_t x2, uint16_t y2,
		    uint16_t x3, uint16_t y3,
		    uint16_t color)
  void drawText(uint16_t x, uint16_t y, uint16_t color, uint16_t size, char* msg);
  void fillScreen(uint16_t color);
  void setRotation(uint8_t val) ; // val in {0, 1, 2, 3}
};

#endif
