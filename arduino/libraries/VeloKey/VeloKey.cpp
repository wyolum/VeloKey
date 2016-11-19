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

void VeloKey::drawText(uint16_t x, uint16_t y, uint16_t color, uint16_t size, int msg){
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
  if(!scroll_center_down){
    drawText(80, 100, ST7735_BLUE, 1, by_wyolum);
    delay(hold_ms);
  }
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
	scroll_left_down = true;
	for(uint8_t jj = 0; jj < n_listener; jj++){
	  listeners[jj]->onScrollLeftPress();
	}
	break;
	
      case SCROLL_LEFT_RELEASE:
	scroll_left_down = false;
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
	scroll_right_down = true;
	for(uint8_t jj = 0; jj < n_listener; jj++){
	  listeners[jj]->onScrollRightPress();
	}
	break;
 	
      case SCROLL_RIGHT_RELEASE:
	scroll_right_down = false;
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
	scroll_center_down = true;
	for(uint8_t jj = 0; jj < n_listener; jj++){
	  listeners[jj]->onScrollCenterPress();
	}
	break;
	
      case SCROLL_CENTER_RELEASE:
	scroll_center_down = false;
	for(uint8_t jj = 0; jj < n_listener; jj++){
	  listeners[jj]->onScrollCenterRelease();
	}
	break;

      case BUTTON_NORTH_PRESS:
	button_north_down = true;
	for(uint8_t jj = 0; jj < n_listener; jj++){
	  listeners[jj]->onButtonNorthPress();
	}
	break;
	
      case BUTTON_NORTH_RELEASE:
	button_north_down = false;
	for(uint8_t jj = 0; jj < n_listener; jj++){
	  listeners[jj]->onButtonNorthRelease();
	}
	break;

      case BUTTON_SOUTH_PRESS:
	button_south_down = true;
	for(uint8_t jj = 0; jj < n_listener; jj++){
	  listeners[jj]->onButtonSouthPress();
	}
	break;
	
      case BUTTON_SOUTH_RELEASE:
	button_south_down = false;
	for(uint8_t jj = 0; jj < n_listener; jj++){
	  listeners[jj]->onButtonSouthRelease();
	}
	break;

      case BUTTON_EAST_PRESS:
	button_east_down = true;
	for(uint8_t jj = 0; jj < n_listener; jj++){
	  listeners[jj]->onButtonEastPress();
	}
	break;
	
      case BUTTON_EAST_RELEASE:
	button_east_down = false;
	for(uint8_t jj = 0; jj < n_listener; jj++){
	  listeners[jj]->onButtonEastRelease();
	}
	break;

      case BUTTON_WEST_PRESS:
	button_west_down = true;
	for(uint8_t jj = 0; jj < n_listener; jj++){
	  listeners[jj]->onButtonWestPress();
	}
	break;
	
      case BUTTON_WEST_RELEASE:
	button_west_down = false;
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
  x = _x + _w / 2;
  y = _y + _h / 2;
  r = min(_w, _h) / 2;
  w = _w;
  h = _h;
  color = _color;
  n_point = 4;
  xs[0] = x    ;  ys[0] = y;
  xs[1] = x + w;  ys[1] = y;
  xs[2] = x + w;  ys[2] = y + h;
  xs[3] = x    ;  ys[3] = y + h;
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

bool z_sign(int16_t x1, int16_t y1, int16_t x2, int16_t y2,int16_t x, int16_t y){
  // deterime what side (x, y) is on the line defined by p1 = x1, y1 and p2 = x2, y2
  // derived from the z component of the cross product of (x, y) - p1 and p2 - p1
  return (x - x1) * (y2 - y1) - (x2 - x1) * (y - y1);
}

bool pt_in_triangle(int16_t px, int16_t py, int16_t vx1,int16_t vy1, int16_t vx2, int16_t vy2, int16_t vx3, int16_t vy3){
  bool s1, s2, s3;
  s1 = z_sign(vx1, vy1, vx2, vy2, px, py);
  s2 = z_sign(vx2, vy2, vx3, vy3, px, py);
  s3 = z_sign(vx3, vy3, vx1, vy1, px, py);
  return s1 == s2 && s2 == s3;
}

ConvexPolygonSprite::ConvexPolygonSprite(){
}

void ConvexPolygonSprite::setup(byte _n_point, int16_t *_xs, int16_t *_ys, uint16_t _color){
  n_point = _n_point;
  color = _color;
  x = 0;
  y = 0;
  for(byte i=0; i<n_point; i++){
    xs[i] = _xs[i];
    ys[i] = _ys[i];
    x += xs[i];
    y += ys[i];
  }
  x = x / n_point;
  y = y / n_point;
}

void ConvexPolygonSprite::draw(){
  for(byte i=0; i < n_point; i++){
    velokey.drawLine(xs[i], ys[i], xs[(i + 1) % n_point], ys[(i + 1) % n_point], color);
  }
}

bool ConvexPolygonSprite::rotate(int degrees){
  float theta = degrees * 3.14159 / 180;
  Serial.println(theta);
  for(byte i=1; i<n_point-1; i++){
    xs[i] -= x;
    ys[i] -= y;
    xs[i] = cos(theta) * xs[i] - sin(theta) * ys[i];
    ys[i] = sin(theta) * xs[i] + cos(theta) * ys[i];
    xs[i] += x;
    ys[i] += y;
  }
}

bool ConvexPolygonSprite::contains_point(int16_t x, int16_t y){
  bool out = false;
  for(byte ii=1; ii<n_point-1; ii++){
    if(pt_in_triangle(x, y, xs[0], ys[0], xs[ii], ys[ii], xs[ii+1], ys[ii+1])){
      out = true;
      break;
    }
  }
  return out;
}

bool ConvexPolygonSprite::collide(ConvexPolygonSprite *other){
  bool out=false;
  int i;
  
  // see if any of my points are in other
  for(int i=0; i < n_point && out == false; i++){
    if(other->contains_point(xs[i], ys[i])){
      out = true;
    }
  }

  //see if any of other's points are in me
  for(int i=0; i < other->n_point && out == false; i++){
    if(contains_point(other->xs[i], other->ys[i])){
      out = true;
    }
  }
  return out;
}

bool RectSprite::collide(RectSprite* other){
  // check four corners of self in other
  bool out = false;

  // check if one of my corners is in other
  // top left (x, y)
  if(other->x < x && x < other->x + other->w &&
     other->y < y && y < other->y + other->h){
    out = true;
  }
  // top right (x, y)
  else if(other->x < x + w && x + w < other->x + other->w &&
     other->y < y && y < other->y + other->h){
    out = true;
  }
  // bottom right (x, y)
  else if(other->x < x + w && x + w < other->x + other->w &&
     other->y < y + h && y + h < other->y + other->h){
    out = true;
  }
  // bottom left (x, y)
  else if(other->x < x && x < other->x + other->w &&
     other->y < y + h && y + h < other->y + other->h){
    out = true;
  }

  // check if other corner is inside me
  else if(x < other->x && other->x < x + w &&
	  y < other->y && other->y < y + h){
    out = true;
  }
  return out;
}
			   
