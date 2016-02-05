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

}

void UI::begin(){
   tft_p->fillRect(x, y, w, h, bg_color);  
}

bool UI::onClickL(){
}
bool UI::onClickR(){
}
bool UI::onScrollL(int enc){
}
bool UI::onScrollR(int enc){
}
bool UI::onPowerUp(){
}
void UI::update(){
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
  UI(_tft_p, _ezkey_p, _right*TFT_W/2, _right * TFT_W / 2, TFT_W / 2, TFT_H,
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
  for(int ii=0; ii<n; ii++){
    tft_p->setCursor(x, ii * fontsize);
    tft_p->println(items[ii]);
  }
  select(0);
}
void MenuUI::select(uint8_t position){
  tft_p->fillRect(x, selected * fontsize, TFT_W/2, fontsize, bg_color);
  tft_p->setCursor(x, selected * fontsize);
  tft_p->setTextColor(face_color);
  tft_p->println(items[selected]);
  
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
  int position = lenc->get(enc);
  bool out = false;
  if(!right && position != selected){    
    select(position);
    out = true;
  }
  return out;
}
bool MenuUI::onScrollR(int enc){
  int position = lenc->get(enc);
  bool out = false;

  if(right && position != selected){    
    select(position);
    out = true;
  }
  return out;
}
bool MenuUI::onPowerUp(){
}
void MenuUI::update(){
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
    keyCommand(MODIFIER_NONE, keys_p[selected], 0, 0, 0, 0, 0);
    keyCommand(MODIFIER_NONE, 0, 0, 0, 0, 0, 0);
}
bool KeyMenu::onClickL(){
  bool out = false;
  if(!right){
    // send a key via ezlink
    onClick();
    out = true;
  }
  return out;
}
bool KeyMenu::onClickR(){
  bool out = false;
  if(right){
    // send a key via ezlink
    onClick();
    out = true;
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

