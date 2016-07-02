#ifndef UI_H
#define UI_H

#include "Adafruit_ST7735.h"
#include "LimitedEnc.h"
#include "EZKey.h"

const uint8_t TFT_W = 160;
const uint8_t TFT_H = 128;
const byte ALT_TAB = 0xE8;

class UI{
 public:
  Adafruit_ST7735 *tft_p;
  Uart *ezkey_p;
  int x, y, w, h;
  uint16_t bg_color, face_color;
  uint16_t bg_selected, face_selected;
  uint8_t fontsize;
  uint8_t textsize; // tft internal text size
  uint8_t selected;
  int last_mouse_delta_x;
  int last_mouse_delta_y;
  byte ez_modifier = MODIFIER_NONE;
  bool ezkey_ready = false;

  UI(Adafruit_ST7735* _tft_, Uart *_ezkey_p,
     int _x, int _y, int _w, int _h,
     uint16_t _bg_color, uint16_t _face_color, 
     uint16_t _bg_selected, uint16_t _face_selected,
     uint8_t _fontsize);
  virtual void begin();
  virtual bool onPressR();
  virtual bool onPressL();
  virtual bool onReleaseR();
  virtual bool onReleaseL();
  virtual bool onClickR();
  virtual bool onClickL();
  virtual bool onScrollR(int enc);
  virtual bool onScrollL(int enc);
  virtual bool onPowerUp();
  virtual void update(bool depressed_a, bool depressed_b);
  void keyCommand(uint8_t modifiers, uint8_t keycode);
  void EZ_keyCommand(uint8_t modifiers, uint8_t keycode1, uint8_t keycode2, 
		  uint8_t keycode3, uint8_t keycode4, uint8_t keycode5, 
		  uint8_t keycode6);
  void USB_keyCommand(uint8_t modifiers, uint8_t keycode);

  void mouseCommand(uint8_t buttons, uint8_t delta_x, uint8_t delta_y, int8_t wheel);
  void EZ_mouseCommand(uint8_t buttons, uint8_t delta_x, uint8_t delta_y, int8_t wheel);
  void USB_mouseCommand(uint8_t buttons, uint8_t delta_x, uint8_t delta_y, int8_t wheel);
};

class MenuUI: public UI{
 public:
  char **items;
  int n;
  bool right;
  LimitedEnc *lenc;

  MenuUI(Adafruit_ST7735* _tft_p, Uart* _ezkey_p,
	 char **_items, int _n, bool _right, 
	 uint16_t _bg_color, uint16_t _face_color, 
	 uint16_t _bg_selected, uint16_t _face_selected,
	 uint8_t fontsize);
  ~MenuUI(){delete lenc;}
  void begin();  
  void select(int position);
  bool onClickL();
  bool onClickR();
  bool onScrollL(int enc);
  bool onScrollR(int enc);
  bool onPowerUp();
  void update(bool depressed_a, bool depressed_b);
};

class KeyMenu: public MenuUI{
 public:
  bool keydown = false;
  byte *keys_p;
  bool immediate;
  KeyMenu(Adafruit_ST7735* _tft_p, Uart* _ezkey_p,
	 char **_items, 
	 byte *keys, bool _immediate,
	 int _n, bool _right, 
	 uint16_t _bg_color, uint16_t _face_color, 
	 uint16_t _bg_selected, uint16_t _face_selected,
	 uint8_t _fontsize);
  void update(bool depressed_a, bool depressed_b);
  bool onClick();
  bool onClickL();
  bool onClickR();
  bool onScrollL(int enc);
  bool onScrollR(int enc);
};

class Mouse_ui: public UI{
 public:
  bool keydown = false;
  LimitedEnc *lencL;
  LimitedEnc *lencR;
  unsigned int last_action = 0;
  unsigned int last_scroll_l = 0;
  unsigned int last_scroll_r = 0;
  bool is_clear = true;
  bool is_left = false;
  bool is_right = false;
  bool is_up = false;
  bool is_down = false;
  int velocity = 1;
  
  Mouse_ui(Adafruit_ST7735* _tft_, Uart *_ezkey_p,
	uint16_t _bg_color, uint16_t _face_color, 
	uint16_t _bg_selected, uint16_t _face_selected,
	uint8_t _fontsize);

  void begin();
  bool onPressL();
  bool onPressR();
  bool onReleaseL();
  bool onReleaseR();
  bool onClickL();
  bool onClickR();
  void accelerate(unsigned int now);
  bool onScrollL(int enc);
  bool onScrollR(int enc);
  bool onPowerUp();
  void update(bool depressed_a, bool depressed_b);
};

class Alpha: public KeyMenu{
 public:
  static const int n = 26 + 1 + 3;
  char *letters[n] = {"a", "b", "c", "d", "e", "f", 
		      "g", "h", "i", "j", "k", "l",
		      "m", "n", "o", "p", "q", "r",
		      "s", "t", "u", "v", "w", "x", 
		      "y", "z", "_",           "<-",
		      "<Shift>",
		      "<Enter>"
  };
  char *shifted_letters[n] = {"A", "B", "C", "D", "E", "F", 
			      "G", "H", "I", "J", "K", "L",
			      "M", "N", "O", "P", "Q", "R",
			      "S", "T", "U", "V", "W", "X", 
			      "Y", "Z", "_",           "<-",
			      "<Shift>",
			      "<Enter>"
  };
  byte keys[n] = {
    EZKEY_A, EZKEY_B, EZKEY_C, EZKEY_D, EZKEY_E, EZKEY_F, EZKEY_G, EZKEY_H, 
    EZKEY_I, EZKEY_J, EZKEY_K, EZKEY_L, EZKEY_M, EZKEY_N, EZKEY_O, EZKEY_P, 
    EZKEY_Q, EZKEY_R, EZKEY_S, EZKEY_T, EZKEY_U, EZKEY_V, EZKEY_W, EZKEY_X, 
    EZKEY_Y, EZKEY_Z, EZKEY_SPACE,                         EZKEY_BACKSPACE,
    EZKEY_SHIFT_RIGHT, EZKEY_RETURN};
  byte *keys_p;
  bool immediate;
  bool shifted = false;
  Alpha(Adafruit_ST7735* _tft_p, Uart* _ezkey_p,
	uint16_t _bg_color, uint16_t _face_color, 
	uint16_t _bg_selected, uint16_t _face_selected,
	bool _right,
	uint8_t _fontsize);
  void draw_key(uint8_t pos, uint16_t color);
  void select(int position);
  void begin();
  bool onScrollL(int enc);
  bool onScrollR(int enc);
  bool onClick();
  bool onClickL();
  bool onClickR();
};

class Numeric: public KeyMenu{
 public:
  char *numbers[21 + 1 + 3] = {"1", "2", "3", "4", "5",
		       "6", "7", "8", "9", "0",
		       "`", ",", ".", "/", ";", 
		       "'", "[", "]", "-", "=",
		       "\\", "_",
		       "<-",
		       "<Shift>",
		       "<Enter>"
  };
  char *shifted_numbers[21 + 1 + 3] = {"!", "@", "#", "$", "%",
				       "^", "&", "*", "(", ")",
				       "~", "<", ">", "?", ":", 
				       "\"", "{", "}", "_", "+",
				       "|", "_",
				       "<-",
				       "<Shift>",
				       "<Enter>"
  };
  static const int n = 21 + 1 + 3;
  byte keys[n] = {
    EZKEY_1, EZKEY_2, EZKEY_3, EZKEY_4, EZKEY_5, EZKEY_6, EZKEY_7, EZKEY_8, 
    EZKEY_9, EZKEY_0, EZKEY_GRAVE, EZKEY_COMMA, EZKEY_PERIOD, EZKEY_SLASH, 
    EZKEY_SEMICOLON, 
    EZKEY_APOSTROPHE, EZKEY_BRACKET_LEFT, EZKEY_BRACKET_RIGHT,
    EZKEY_MINUS, EZKEY_EQUAL, EZKEY_BACKSLASH, EZKEY_SPACE,
    EZKEY_BACKSPACE,
    EZKEY_SHIFT_RIGHT,
    EZKEY_RETURN};
  bool immediate;
  bool shifted = false;
  Numeric(Adafruit_ST7735* _tft_p, Uart* _ezkey_p,
	uint16_t _bg_color, uint16_t _face_color, 
	uint16_t _bg_selected, uint16_t _face_selected,
	bool _right,
	uint8_t _fontsize);
  void draw_key(uint8_t pos, uint16_t color);
  void select(int position);
  void begin();
  bool onScrollL(int enc);
  bool onScrollR(int enc);
  bool onClick();
  bool onClickL();
  bool onClickR();
};

class BattLevel: public UI{
 public:
  uint8_t level = 128;
  BattLevel(Adafruit_ST7735* _tft_, Uart *_ezkey_p,
	    int _x, int _y, int _w, int _h,
	    uint16_t _bg_color, uint16_t _face_color, 
	    uint16_t _bg_selected, uint16_t _face_selected,
	    uint8_t _fontsize);
  void update(bool depressed_a, bool depressed_b);
};

#endif
