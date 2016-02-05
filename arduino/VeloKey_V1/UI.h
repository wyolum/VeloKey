#include "Adafruit_ST7735.h"
#include "LimitedEnc.h"

const uint8_t TFT_W = 160;
const uint8_t TFT_H = 128;

class UI{
 public:
  Adafruit_ST7735 *tft_p;
  Uart *ezkey_p;
  int x, y, w, h;
  uint16_t bg_color, face_color;
  uint16_t bg_selected, face_selected;
  uint8_t fontsize;
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
  virtual void update();
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
  void select(uint8_t position);
  bool onClickL();
  bool onClickR();
  bool onScrollL(int enc);
  bool onScrollR(int enc);
  bool onPowerUp();
  void update();
};

class KeyMenu: public MenuUI{
 public:
  byte *keys_p;
  bool immediate;
  KeyMenu(Adafruit_ST7735* _tft_p, Uart* _ezkey_p,
	 char **_items, 
	 byte *keys, bool _immediate,
	 int _n, bool _right, 
	 uint16_t _bg_color, uint16_t _face_color, 
	 uint16_t _bg_selected, uint16_t _face_selected,
	 uint8_t _fontsize);
  bool onClick();
  bool onClickL();
  bool onClickR();
  bool onScrollL(int enc);
  bool onScrollR(int enc);
};
