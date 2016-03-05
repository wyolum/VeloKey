#include "UI.h"
#include <EZKey.h>

UI::UI(Adafruit_ST7735* _tft_p, Uart *_ezkey_p,
       int _x, int _y, int _w, int _h,
       uint16_t _bg_color, uint16_t _face_color, 
       uint16_t _bg_selected, uint16_t _face_selected,
       uint8_t _fontsize){
  tft_p = _tft_p;
  ezkey_p = _ezkey_p;
  x = _x;
  y = _y;
  w = _w;
  h = _h;
  bg_color = _bg_color;
  face_color = _face_color;
  bg_selected = _bg_selected;
  face_selected = _face_selected;
  fontsize = _fontsize;
  if(fontsize < 10){
    textsize = 1;
  }
  else{
    textsize = 2;
  }

}

void UI::begin(){
   tft_p->fillRect(x, y, w, h, bg_color);  
}

bool UI::onClickL(){
  return false;
}
bool UI::onClickR(){
  return false;
}
bool UI::onScrollL(int enc){
  return false;
}
bool UI::onScrollR(int enc){
  return false;
}
bool UI::onPowerUp(){
  return false;
}
void UI::update(bool a_depressed, bool b_depressed){
}
void UI::keyCommand(
		    uint8_t modifiers, uint8_t keycode1, uint8_t keycode2, 
		    uint8_t keycode3, uint8_t keycode4, uint8_t keycode5, 
		    uint8_t keycode6) {
  ezkey_p->write(0xFD);       // our command
  ezkey_p->write(modifiers);  // modifier!
  ezkey_p->write((byte)0x00); // 0x00  
  ezkey_p->write(keycode1);   // key code #1
  ezkey_p->write(keycode2); // key code #2
  ezkey_p->write(keycode3); // key code #3
  ezkey_p->write(keycode4); // key code #4
  ezkey_p->write(keycode5); // key code #5
  ezkey_p->write(keycode6); // key code #6
}
void UI::mouseCommand(uint8_t buttons, uint8_t delta_x, uint8_t delta_y){
  ezkey_p->write(0xFD);
  ezkey_p->write((byte)0x00);
  ezkey_p->write((byte)0x03);
  ezkey_p->write(buttons);
  ezkey_p->write(delta_x);
  ezkey_p->write(delta_y);
  ezkey_p->write((byte)0x00);
  ezkey_p->write((byte)0x00);
  ezkey_p->write((byte)0x00);
  last_mouse_delta_x = delta_x;
  last_mouse_delta_y = delta_y;
}
MenuUI::MenuUI(Adafruit_ST7735* _tft_p,   Uart* _ezkey_p,
	       char **_items, int _n, bool _right, 
	       uint16_t _bg_color, uint16_t _face_color, 
	       uint16_t _bg_selected, uint16_t _face_selected,
	       uint8_t _fontsize):
  UI(_tft_p, _ezkey_p, _right*TFT_W/2, 0, TFT_W / 2, TFT_H,
     _bg_color, _face_color, _bg_selected, _face_selected, _fontsize)
{
  items = _items;
  n = _n;
  right = _right;
  selected = 0;
  lenc = new LimitedEnc(selected, n, right);
}
void MenuUI::begin(){
  UI::begin();
  tft_p->setTextColor(face_color);
  tft_p->setTextSize(textsize); // test of larger font size
  for(int ii=0; ii<n; ii++){
    tft_p->setCursor(x, ii * fontsize);
    tft_p->println(items[ii]);
  }
  select(selected);
}
void MenuUI::select(int position){
  tft_p->setTextSize(textsize); // test of larger font size
  
  // deselect old value
  tft_p->fillRect(x, selected * fontsize, TFT_W/2, fontsize, bg_color);
  tft_p->setCursor(x, selected * fontsize);
  tft_p->setTextColor(face_color);
  tft_p->println(items[selected]);
  
  // do we need to scroll?
  
  // select new position
  tft_p->fillRect(x, position * fontsize, TFT_W/2, fontsize, bg_selected);
  tft_p->setCursor(x, position * fontsize);
  tft_p->setTextColor(face_selected);
  tft_p->println(items[position]);
  selected = position;
}
bool MenuUI::onClickL(){
  bool out = false;
  if(!right){
    // take action;
    out = true;
  }
  return out;
}
bool MenuUI::onClickR(){
  bool out = false;
  if(right){
    //take action
    out = true;
  }
  return out;
}
bool MenuUI::onScrollL(int enc){
  bool out = false;
  if(!right){
    int position = lenc->get(enc);

    if(position != selected){    
      select(position);
      out = true;
    }
    else if(position == 0){
      // at top of left menu, send a left arrow
      keyCommand(MODIFIER_NONE, EZKEY_ARROW_LEFT, 0, 0, 0, 0, 0);
      keyCommand(MODIFIER_NONE, 0, 0, 0, 0, 0, 0);
    }
    else if(position == n - 1){
      // at bottom of left menu, send a right arrow
      keyCommand(MODIFIER_NONE, EZKEY_ARROW_RIGHT, 0, 0, 0, 0, 0);
      keyCommand(MODIFIER_NONE, 0, 0, 0, 0, 0, 0);
    }
  }
  return out;
}
bool MenuUI::onScrollR(int enc){
  bool out = false;
  if(right){
    int position = lenc->get(enc);
    if(position != selected){    
      select(position);
      out = true;
    }
    else if(position == 0){
      // at top of right menu, send a up arrow
      keyCommand(MODIFIER_NONE, EZKEY_ARROW_UP, 0, 0, 0, 0, 0);
      keyCommand(MODIFIER_NONE, 0, 0, 0, 0, 0, 0);
    }
    else if(position == n - 1){
      // at bottom of right menu, send a down arrow 
      // NOPE! (this causes a u-turn in ZWIFT)
      // keyCommand(MODIFIER_NONE, EZKEY_ARROW_DOWN, 0, 0, 0, 0, 0);
      // keyCommand(MODIFIER_NONE, 0, 0, 0, 0, 0, 0);
    }
  }
  return out;
}
bool MenuUI::onPowerUp(){
}
void MenuUI::update(bool a_depressed, bool b_depressed){
}

KeyMenu::KeyMenu(Adafruit_ST7735* _tft_p, Uart* _ezkey_p,
		 char **_items, 
		 byte *_keys_p, bool _immediate,
		 int _n, bool _right, 
		 uint16_t _bg_color, uint16_t _face_color, 
		 uint16_t _bg_selected, uint16_t _face_selected,
		 uint8_t _fontsize):
MenuUI(_tft_p, _ezkey_p, _items, _n, _right, _bg_color, _face_color,
       _bg_selected, _face_selected, _fontsize)
{
  keys_p = _keys_p;
  immediate = _immediate;
}
bool KeyMenu::onClick(){
    // send a key via ezlink
  byte key = keys_p[selected];
  if(key == ALT_TAB){
    keyCommand(MODIFIER_ALT_LEFT, EZKEY_ALT_LEFT, EZKEY_TAB, 0, 0, 0, 0);
    delay(100);
    keyCommand(MODIFIER_ALT_LEFT, EZKEY_ALT_LEFT, 0, 0, 0, 0, 0);
    keyCommand(MODIFIER_NONE, 0, 0, 0, 0, 0, 0);
  }
  else{
    keyCommand(ez_modifier, keys_p[selected], 0, 0, 0, 0, 0);
    keydown = true;
  }
  return true;
}
void KeyMenu::update(bool a_depressed, bool b_depressed){
  if(keydown && !(a_depressed || b_depressed)){
    keyCommand(MODIFIER_NONE, 0, 0, 0, 0, 0, 0);
    keydown = false;
  }
}
bool KeyMenu::onClickL(){
  bool out = false;
  if(!right){
    // send a key via ezlink
    out = onClick();
  }
  return out;
}
bool KeyMenu::onClickR(){
  bool out = false;
  if(right){
    // send a key via ezlink
    out = onClick();
  }
  return out;
}

bool KeyMenu::onScrollL(int enc){
  bool out = MenuUI::onScrollL(enc);
  if(out && immediate){
    // automatic click
    onClickL();
  }
  return out;
}
bool KeyMenu::onScrollR(int enc){
  bool out = MenuUI::onScrollR(enc);
  if(out && immediate){
    // automatic click
    onClickR();
  }
  return out;
}

Mouse_ui::Mouse_ui(Adafruit_ST7735* _tft_p,   Uart* _ezkey_p,
	     uint16_t _bg_color, uint16_t _face_color, 
	     uint16_t _bg_selected, uint16_t _face_selected,
	     uint8_t _fontsize):
  UI(_tft_p, _ezkey_p, 0, 0, TFT_W, TFT_H,
     _bg_color, _face_color, _bg_selected, _face_selected, _fontsize)
{
  lencR = new LimitedEnc(0, 1, false);
  lencL = new LimitedEnc(0, 1, false);
}
void Mouse_ui::begin(){
  UI::begin();
  // draw a mouse
  int size = 8;
  // ears
  tft_p->drawCircle(TFT_W/2-size, TFT_H/2-3 * size / 2, size-2, ST7735_WHITE);
  tft_p->drawCircle(TFT_W/2+size, TFT_H/2-3 * size / 2, size-2, ST7735_WHITE);
  
  // head
  tft_p->fillTriangle(TFT_W/2,   TFT_H/2 + 3 * size / 2, 
		      TFT_W/2 - size, TFT_H/2 - 3 * size / 2, 
		      TFT_W/2 + size, TFT_H/2 - 3 * size / 2, 
		      // tft_p->Color565(100, 100, 100));
		      ST7735_WHITE);
  // eyes
  tft_p->drawCircle(TFT_W/2 - 3, TFT_H/2 - 3, 3, ST7735_WHITE);
  tft_p->drawCircle(TFT_W/2 + 3, TFT_H/2 - 3, 3, ST7735_WHITE);
  tft_p->fillCircle(TFT_W/2 - 3, TFT_H/2 - 3, 2, ST7735_BLUE);
  tft_p->fillCircle(TFT_W/2 + 3, TFT_H/2 - 3, 2, ST7735_BLUE);

  // nose
  tft_p->fillTriangle(TFT_W/2,   TFT_H/2 + 3 * size / 2, 
		      TFT_W/2 - 2, TFT_H/2 + 6,
		      TFT_W/2 + 2, TFT_H/2 + 6,
		      ST7735_BLUE);
  
}

bool Mouse_ui::onClickL(){
  mouseCommand(EZKEY_LEFT_MOUSE_BUTTON, 0, 0);
  mouseCommand(0, 0, 0);
  return true;
}
bool Mouse_ui::onClickR(){
  mouseCommand(EZKEY_LEFT_MOUSE_BUTTON, 0, 0);
  mouseCommand(0, 0, 0);
  return true;
}
void Mouse_ui::accelerate(unsigned int now){
  unsigned int dt = now - last_scroll_l;
  if(dt < 100){
    if(velocity < 16){
      velocity++;
    }
  }
  else if(dt < 400){
    velocity /= 2;
    if(velocity < 4){
      velocity = 4;
    }
  }
  else{
    velocity = 4;
  }
  last_scroll_l = now;
  
}

bool Mouse_ui::onScrollL(int enc){
  // right-left
  unsigned int now = millis();
  int delta_x;

  accelerate(now);
  delta_x = -lencL->getDelta(enc) * velocity;
  mouseCommand(0, delta_x, 0);
  last_action = now;

  if(delta_x < 0 && !is_left){
    // left arrow
    tft_p->fillTriangle(TFT_W/2-60, TFT_H/2, 
			TFT_W/2-40, TFT_H/2+20, 
			TFT_W/2-40, TFT_H/2-20, 
			ST7735_RED);
    is_left = true;
    is_clear = false;
  }
  else if(delta_x > 0 && !is_right){
    // right arrow
    tft_p->fillTriangle(TFT_W/2+60, TFT_H/2, 
			TFT_W/2+40, TFT_H/2+20, 
			TFT_W/2+40, TFT_H/2-20, 
			ST7735_RED);
    is_right = true;
    is_clear = false;
  }
  return true;
}

bool Mouse_ui::onScrollR(int enc){
  // up/down
  unsigned int now = millis();

  accelerate(now);
  int delta_y = lencR->getDelta(enc) * velocity;
  mouseCommand(0, 0, delta_y);
  last_action = millis();
  if(delta_y < 0 && !is_up){
    tft_p->fillTriangle(TFT_W/2, TFT_H/2 - 60, 
			TFT_W/2 + 20, TFT_H/2-40, 
			TFT_W/2 - 20, TFT_H/2-40, 
			ST7735_BLUE);
    is_up = true;
    is_clear = false;
  }
  else if(delta_y > 0 && !is_down){
    tft_p->fillTriangle(TFT_W/2, TFT_H/2 + 60, 
			TFT_W/2 + 20, TFT_H/2+40, 
			TFT_W/2 - 20, TFT_H/2+40, 
			ST7735_BLUE);
    is_down = true;
    is_clear = false;
  }
  return true;
}
bool Mouse_ui::onPowerUp(){
  return true;
}
void Mouse_ui::update(bool a_depressed, bool b_depressed){
  unsigned long now = millis();
  if(!is_clear && now - last_action > 1000){
    // clear screen
    begin();
    is_clear = true;
    is_up = false;
    is_down = false;
    is_right = false;
    is_left = false;
  }
}


Alpha::Alpha(Adafruit_ST7735* _tft_p, Uart *_ezkey_p,
	     uint16_t _bg_color, uint16_t _face_color, 
	     uint16_t _bg_selected, uint16_t _face_selected,
	     bool _right,
	     uint8_t _fontsize):
  KeyMenu(_tft_p, _ezkey_p,
	  letters, keys, false,
	  1, _right, 
	  _bg_color, _face_color, _bg_selected, _face_selected,
	  _fontsize)
  
{
}
  
bool Alpha::onClick(){
  //check for special char
  // send a key via ezlink
  byte key = keys_p[selected];
  if(selected == n-2){ // kludge to detech shift button
    if(shifted){
      shifted = false;
    }
    else{
      shifted = true;
    }
    begin();
  }
  else{
    if(shifted){
      ez_modifier = MODIFIER_SHIFT_RIGHT;
    }
    else{
      ez_modifier = MODIFIER_NONE;
    }
    KeyMenu::onClick();
    if(ez_modifier == MODIFIER_SHIFT_RIGHT){
      ez_modifier = MODIFIER_NONE;
      shifted = false;
      begin();
    }
  }
  return true;
}

bool Alpha::onClickL(){
  bool out = false;
  if(!right){
    onClick();
    out = true;
  }
  return out;
}
bool Alpha::onClickR(){
  bool out = false;
  if(right){
    onClick();
    out = true;
  }
  return out;
}

void Alpha::begin(){
  UI::begin();
  for(int pos = 0; pos < n; pos++){
    draw_key(pos, face_color);
  }
  draw_key(selected, face_selected);
}
void Alpha::draw_key(uint8_t pos, uint16_t color){
  int ii = pos % 6;
  int jj = pos / 6;
  tft_p->setTextColor(color);
  tft_p->setTextSize(2);
  if(pos < 26 + 0){
    tft_p->setCursor(12 * ii + right * 80, fontsize * jj);
    }
  else if(pos == 26 + 0 + 0){ // backspace
    tft_p->setCursor(12 * 4 + right * 80, fontsize * 4);
  }
  else if(pos == 26 + 0 + 1){ // shift
    tft_p->setCursor(12 * 0 + right * 80, fontsize * 5);
  }
  else if(pos == 26 + 0 + 2){ // enter
    tft_p->setCursor(12 * 0 + right * 80, fontsize * 6);
  }
  if(pos < n){
    if(!shifted){
      tft_p->print(letters[pos]);
    }
    else{
      tft_p->print(shifted_letters[pos]);
    }
  }
}

void Alpha::select(int position){
  int value = -position;
  int _x, _y;
  while(value < 0){ // correct negative encoder value
    value += n * ((abs(value)) / n + 1);
  }
  value = value % n;
  char *msg = letters[value%n];
  draw_key(selected, face_color);
  draw_key(value, face_selected);
  selected = value;
}

bool Alpha::onScrollR(int enc){
  bool out = false;
  if(right){
    out = true;
    select(enc);
  }
  return out;
}
bool Alpha::onScrollL(int enc){
  bool out = false;
  if(!right){
    out = true;
    select(enc);
  }
  return out;
}

Numeric::Numeric(Adafruit_ST7735* _tft_p, Uart *_ezkey_p,
	     uint16_t _bg_color, uint16_t _face_color, 
	     uint16_t _bg_selected, uint16_t _face_selected,
	     bool _right,
	     uint8_t _fontsize):
  KeyMenu(_tft_p, _ezkey_p,
	  letters, keys, false,
	  1, _right, 
	  _bg_color, _face_color, _bg_selected, _face_selected,
	  _fontsize)
  
{
}
  
void Numeric::begin(){
  UI::begin();
  for(int pos = 0; pos < n; pos++){
    draw_key(pos, face_color);
  }
  draw_key(selected, face_selected);
}
void Numeric::draw_key(uint8_t pos, uint16_t color){
  int ii = pos % 6;
  int jj = pos / 6;
  tft_p->setTextColor(color);
  tft_p->setTextSize(2);
  if(pos < 21 + 0){
    tft_p->setCursor(12 * ii + right * 80, fontsize * jj);
    }
  else if(pos == 21 + 0 + 0){ // backspace
    tft_p->setCursor(12 * 4 + right * 80, fontsize * 4);
  }
  else if(pos == 21 + 0 + 1){ // shift
    tft_p->setCursor(12 * 0 + right * 80, fontsize * 5);
  }
  else if(pos == 21 + 0 + 2){ // enter
    tft_p->setCursor(12 * 0 + right * 80, fontsize * 6);
  }
  if(pos < n){
    if(!shifted){
      tft_p->print(letters[pos]);
    }
    else{
      tft_p->print(shifted_letters[pos]);
    }
  }
}

void Numeric::select(int position){
  int value = -position;
  int _x, _y;
  while(value < 0){ // correct negative encoder value
    value += n * ((abs(value)) / n + 1);
  }
  value = value % n;
  char *msg = letters[value%n];
  draw_key(selected, face_color);
  draw_key(value, face_selected);
  selected = value;
}

bool Numeric::onScrollR(int enc){
  bool out = false;
  if(right){
    out = true;
    select(enc);
  }
  return out;
}
bool Numeric::onScrollL(int enc){
  bool out = false;
  if(!right){
    out = true;
    select(enc);
  }
  return out;
}
bool Numeric::onClick(){
  // check for special char
  // send a key via ezlink
  byte key = keys_p[selected];
  if(selected == n-2){ // kludge to detech shift button
    if(shifted){
      shifted = false;
    }
    else{
      shifted = true;
    }
    begin();
  }
  else{
    if(shifted){
      ez_modifier = MODIFIER_SHIFT_RIGHT;
    }
    else{
      ez_modifier = MODIFIER_NONE;
    }
    KeyMenu::onClick();
  }
  return true;
}

bool Numeric::onClickL(){
  bool out = false;
  if(!right){
    onClick();
    out = true;
  }
  return out;
}
bool Numeric::onClickR(){
  bool out = false;
  if(right){
    onClick();
    out = true;
  }
  return out;
}


BattLevel::BattLevel(Adafruit_ST7735* _tft_p, Uart *_ezkey_p,
		     int _x, int _y, int _w, int _h,
		     uint16_t _bg_color, uint16_t _face_color, 
		     uint16_t _bg_selected, uint16_t _face_selected,
		     uint8_t _fontsize):
  UI(_tft_p, _ezkey_p,
	    _x, _y, _w, _h,
	    _bg_color, _face_color, 
	    _bg_selected, _face_selected,
	    _fontsize){
  
}
void BattLevel::update(bool depressed_a, bool depressed_b){
  //level = 128 * checkBattery() / 4.7;
  int new_level;

  float measuredvbat = 0; // analogRead(A7);
  measuredvbat *= 2;    // we divided by 2, so multiply back
  measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
  measuredvbat /= 1024; // convert to voltage
  new_level = measuredvbat * 160 / 4.7;


  if(level != new_level){
    tft_p->fillRect(level, 124, 160 - level, 4, face_color);
    tft_p->fillRect(0, 124, level, 4, bg_color);
  }
  if(new_level > 0){
    level = new_level;
  }
  else{
    level = 160;
  }
}
