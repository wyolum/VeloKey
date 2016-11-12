#include "VeloKey.h"
#include "logo_rgb.h"

VeloKey_ST7735 tft = VeloKey_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
// VeloKey_ST7735 tft = VeloKey_ST7735(TFT_CS, TFT_DC, TFT_RST);
VeloKey_ST7735 *stft_p = &tft;

void VeloKey::begin(){
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  tft.setTextWrap(false); // Allow text to run off right edge
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(3);
  pinMode(A7, OUTPUT);
  ncodr.begin(57600);
}

void VeloKey::backlightOn(){
  digitalWrite(DISPLAY_BACKLIGHT, HIGH);
}
void VeloKey::backlightOff(){
  digitalWrite(DISPLAY_BACKLIGHT, LOW);
}

void VeloKey::fillScreen(uint16_t color){
  tft.fillScreen(color);
}

void VeloKey::drawPixel(uint16_t row, uint16_t col, uint16_t color){
  tft.drawPixel(row, col, color);
}

void VeloKey::drawText(uint16_t x, uint16_t y, uint16_t color, uint16_t size, char* msg){
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(size);
  tft.print(msg);
}

void VeloKey::splash(uint16_t hold_ms){
  backlightOn();
  fillScreen(ST7735_WHITE);
  for(int i = 0; i < n_rgb565; i++){
    tft.drawPixel(rgb565_rows[i], rgb565_cols[i], rgb565[i]);
  }
  int blink_counter = 0;
  char * by_wyolum = "by WyoLum";
  drawText(80, 100, ST7735_BLUE, 1, by_wyolum);
  delay(hold_ms);
  fillScreen(ST7735_BLACK);
  backlightOff();
}
void VeloKey::fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color){
  tft.fillRect(x, y, w, h, color);
}
void VeloKey::drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color){
  tft.drawRect(x, y, w, h, color);
}
void VeloKey::fillCircle(uint16_t x, uint16_t y, uint16_t r, uint16_t color){
  tft.fillCircle(x, y, r, color);
}
void VeloKey::drawCircle(uint16_t x, uint16_t y, uint16_t r, uint16_t color){
  tft.drawCircle(x, y, r, color);
}
void VeloKey::fillTriangle(uint16_t x1, uint16_t y1,
			   uint16_t x2, uint16_t y2,
			   uint16_t x3, uint16_t y3,
			   uint16_t color){
  tft.fillTriangle(x1, y1, x2, y2, x3, y3, color);
}
void VeloKey::drawTriangle(uint16_t x1, uint16_t y1,
			   uint16_t x2, uint16_t y2,
			   uint16_t x3, uint16_t y3,
			   uint16_t color){
  tft.fillTriangle(x1, y1, x2, y2, x3, y3, color);
}

void VeloKey::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color){
  tft.drawLine(x0, y0, x1, y1, color);
}
void VeloKey::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color){
  tft.drawFastVLine(x, y, h, color);
}
void VeloKey::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color){
  tft.drawFastHLine(x, y, w, color);
}

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

  
XPM2::XPM2(uint8_t _n_color, uint16_t *_colors, uint16_t _w, uint16_t _h, uint16_t *_data){
  n_color = _n_color;
  colors = _colors;
  w = _w;
  h = _h;
  data = _data;
}

CircleSprite::CircleSprite(int16_t _x, int16_t _y, uint16_t _r, uint16_t _color){
  x = _x;
  y = _y;
  r = _r;
  color = _color;
}

void CircleSprite::draw(){
  velokey.fillCircle(x, y, r, color);
}
			   
RectSprite::RectSprite(int16_t _x, int16_t _y, uint16_t _w, uint16_t _h, uint16_t _color){
  x = _x;
  y = _y;
  w = _w;
  h = _h;
  color = _color;
}

void RectSprite::move(int16_t dx, int16_t dy){
  if(dx > 0){
    velokey.fillRect(x, y,             dx, h, VELOKEY_BLACK);
  }
  if(dx < 0){
    velokey.fillRect(x + w + dx, y,    -dx, h, VELOKEY_BLACK);
  }
  if(dy > 0){
    velokey.fillRect(x,          y, w, dy, VELOKEY_BLACK);
  }
  if(dy < 0){
    velokey.fillRect(x, y + h + dy, w, -dy, VELOKEY_BLACK);
  }
  x += dx;
  y += dy;
  draw();
}

void RectSprite::draw(){
  velokey.fillRect(x, y, w, h, color);
}
			   
