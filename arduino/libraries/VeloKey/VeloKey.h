#ifndef VELOKEY_H
#define VELOKEY_H
#include <Arduino.h>
#include <events.h>
#include <VeloKey_ST7735.h>
#include "logo_rgb.h"

#define ncodr Serial1

const uint16_t VELOKEY_BLACK   = 0x0000;
const uint16_t VELOKEY_BLUE    = 0x001F;
const uint16_t VELOKEY_RED     = 0xF800;
const uint16_t VELOKEY_GREEN   = 0x07E0;
const uint16_t VELOKEY_CYAN    = 0x07FF;
const uint16_t VELOKEY_MAGENTA = 0xF81F;
const uint16_t VELOKEY_YELLOW  = 0xFFE0;
const uint16_t VELOKEY_WHITE   = 0xFFFF;

const uint16_t VELOKEY_WIDTH  = 160;
const uint16_t VELOKEY_HEIGHT = 128;

const int DISPLAY_BACKLIGHT = A3;
const uint8_t max_listeners = 5;
const uint8_t max_events    = 10;
const uint8_t TFT_CS        = 5;  
const uint8_t TFT_RST       = 9;  
const uint8_t TFT_DC        = 6;
const uint8_t TFT_SCLK      = 13;   // set these to be whatever pins you like!
const uint8_t TFT_MOSI      = 11;   // set these to be whatever pins you like!
  
//VeloKey_ST7735 tft = VeloKey_ST7735(TFT_CS, TFT_DC, TFT_MOSI, 
//				      TFT_SCLK, TFT_RST);
// VeloKey_ST7735 *tft_p      = &tft;

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

  void begin();
  void splash(uint16_t hold_ms);
  
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
  void backlightOn();
  void backlightOff();
  void fillRect(uint16_t, uint16_t, uint16_t, uint16_t, uint16_t);
  void drawRect(uint16_t, uint16_t, uint16_t, uint16_t, uint16_t);
  void fillCircle(uint16_t, uint16_t, uint16_t, uint16_t);
  void drawCircle(uint16_t, uint16_t, uint16_t, uint16_t);
  void fillTriangle(uint16_t x1, uint16_t y1,
		    uint16_t x2, uint16_t y2,
		    uint16_t x3, uint16_t y3,
		    uint16_t color);
  void drawTriangle(uint16_t x1, uint16_t y1,
		    uint16_t x2, uint16_t y2,
		    uint16_t x3, uint16_t y3,
		    uint16_t color);
  void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
  void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
  void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
  
  void drawText(uint16_t x, uint16_t y, uint16_t color, uint16_t size, char* msg);
  void fillScreen(uint16_t color);
  void drawPixel(uint16_t row, uint16_t col, uint16_t color);
  void setRotation(uint8_t val) ; // val in {0, 1, 2, 3}
};

class XPM2{
 public:
  uint8_t n_color;
  uint16_t *colors;
  uint16_t w;
  uint16_t h;
  uint16_t *data;
  XPM2(uint8_t _n_color, uint16_t *_colors, uint16_t _w, uint16_t _h, uint16_t *_data);
};

class Sprite{
 public:
  int16_t x, y;
  uint16_t color;
  
  virtual void move(int16_t dx, int16_t dy){
    //Sprite::move(int16 dx, int16 dy){
    draw(VELOKEY_BLACK);
    x += dx;
    y += dy;
    draw();
  }
    
  virtual void draw(uint16_t _color){
    uint16_t c = color;
    color = _color;
    draw();
    color = c;
  }
  virtual void draw();
};

class CircleSprite : public Sprite{
 public:
  uint16_t r;
  
  CircleSprite(int16_t _x, int16_t _y, uint16_t _r, uint16_t _color);
  void draw();
};

class RectSprite : public Sprite{
 public:
  uint16_t w;
  uint16_t h;
  
  RectSprite(int16_t _x, int16_t _y, uint16_t _w, uint16_t _h, uint16_t _color);
  void move(int16_t dx, int16_t dy);
  void draw();
  bool collide(RectSprite *other);
};

static VeloKey velokey = VeloKey();
#endif
