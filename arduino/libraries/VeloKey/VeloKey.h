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
  bool scroll_right_down;
  bool scroll_left_down;
  bool scroll_center_down;
  bool button_north_down;
  bool button_south_down;
  bool button_east_down;
  bool button_west_down;
  VeloKeyListener *listeners[max_listeners];
  uint8_t n_listener;
  uint8_t events[max_events];
  uint8_t n_events_pending;
    
  VeloKey(){
    scroll_right_down = false;
    scroll_left_down = false;
    scroll_center_down = false;
    button_north_down = false;
    button_south_down = false;
    button_east_down = false;
    button_west_down = false;
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

  void unsubscribe(VeloKeyListener *listener){
    for(byte ii = 0; ii < n_listener; ii++){
      if(listener == listeners[ii]){
	for(byte jj = ii + 1; jj < n_listener; jj++){
	  listeners[jj - 1] = listeners[jj];
	}
	n_listener--;
	break;
      }
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
  void drawText(uint16_t x, uint16_t y, uint16_t color, uint16_t size, int msg);
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
  int16_t x, y; // center
  int16_t r;    // radius used for collision detection
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
  virtual bool collide(Sprite *other){
    return (x - other->x) * (x - other->x) + (y - other->y) * (y - other->y)  <
      (r + other->r) * (r + other->r);
  }
};

class CircleSprite : public Sprite{
 public:
  
  CircleSprite(int16_t _x, int16_t _y, uint16_t _r, uint16_t _color);
  void draw();
};

const byte POLY_N_MAX = 16;
class ConvexPolygonSprite : public Sprite{
 public:
  byte n_point;
  int16_t xs[POLY_N_MAX];
  int16_t ys[POLY_N_MAX];
  ConvexPolygonSprite();
  void setup(byte _n_point, int16_t *_xs, int16_t *_ys, uint16_t _color);
  bool contains_point(int16_t x, int16_t y);
  bool collide(ConvexPolygonSprite *other);
  bool rotate(int degrees);
  void draw();
};

class RectSprite : public ConvexPolygonSprite{
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
