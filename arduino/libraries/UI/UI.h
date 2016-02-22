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

  UI(Adafruit_ST7735* _tft_, Uart *_ezkey_p,
     int _x, int _y, int _w, int _h,
     uint16_t _bg_color, uint16_t _face_color, 
     uint16_t _bg_selected, uint16_t _face_selected,
     uint8_t _fontsize);
  virtual void begin();
  virtual bool onClickR();
  virtual bool onClickL();
  virtual bool onScrollR(int enc);
  virtual bool onScrollL(int enc);
  virtual bool onPowerUp();
  virtual void update(bool depressed_a, bool depressed_b);
  void keyCommand(uint8_t modifiers, uint8_t keycode1, uint8_t keycode2, 
		  uint8_t keycode3, uint8_t keycode4, uint8_t keycode5, 
		  uint8_t keycode6);
  void mouseCommand(uint8_t buttons, uint8_t delta_x, uint8_t delta_y);
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

class Mouse: public UI{
 public:
  bool keydown = false;
  LimitedEnc *lencL;
  LimitedEnc *lencR;
  unsigned int last_action = 0;
  bool is_clear = true;
  bool is_left = false;
  bool is_right = false;
  bool is_up = false;
  bool is_down = false;
  uint8_t velocity = 8;

  Mouse(Adafruit_ST7735* _tft_, Uart *_ezkey_p,
	uint16_t _bg_color, uint16_t _face_color, 
	uint16_t _bg_selected, uint16_t _face_selected,
	uint8_t _fontsize);

  void begin();
  bool onClickL();
  bool onClickR();
  bool onScrollL(int enc);
  bool onScrollR(int enc);
  bool onPowerUp();
  void update(bool depressed_a, bool depressed_b);
};

class Alpha: public KeyMenu{
 public:
  static const int n = 27;
  char *letters[n] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", 
		      "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", 
		      "u", "v", "w", "x", "y", "z", "del"};
  byte keys[n] = {
    KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J,
    KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T,
    KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z, KEY_DELETE};
  byte *keys_p;
  bool immediate;
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
