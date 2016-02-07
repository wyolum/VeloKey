#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <EZKey.h>
#include "LimitedEnc.h"
#include "UI.h"

// Serial2 pin and pad definitions (in Arduino files Variant.h & Variant.cpp)
#define PIN_SERIAL2_RX       (34ul) // Pin number for PIO_SERCOM on D12
#define PIN_SERIAL2_TX       (36ul) // Pin number for PIO_SERCOM on D10
#define PAD_SERIAL2_TX       (UART_TX_PAD_2)      // SERCOM pad 2
#define PAD_SERIAL2_RX       (SERCOM_RX_PAD_3)    // SERCOM pad 3

// Instantiate the Serial2 class
Uart Serial2(&sercom1, 
	     PIN_SERIAL2_RX, PIN_SERIAL2_TX, 
	     PAD_SERIAL2_RX, PAD_SERIAL2_TX);
//

#define ncodr Serial1
#define ezkey Serial2
//#define SerialDBG SerialUSB // for M0
#define SerialDBG SERIAL_PORT_USBVIRTUAL


#define TFT_CS     5  
#define TFT_RST    9  
#define TFT_DC     6
#define TFT_SCLK 13   // set these to be whatever pins you like!
#define TFT_MOSI 11   // set these to be whatever pins you like!
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, 
				      TFT_SCLK, TFT_RST);
Adafruit_ST7735 *tft_p = &tft;

union Data{
  int16_t value;
  char bytes[3];
};
Data enca_u;
Data encb_u;

const int n_camera_view = 10;
char *Camera_Views[n_camera_view] = {
  "1st Person",
  "2nd Person",
  "3nd Person",
  "Side",
  "Right Rear",
  "Head On",
  "Specator",
  "Helicopter",
  "Birdseye",
  "Rider Lock",
  };

byte CameraKeys[n_camera_view]{ 
  KEY_3,
    KEY_1,
    KEY_2,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_0,  
    };

const uint8_t n_action = 12;
char *Actions[n_action] = {
  "Elbow Flick",
  "Wave",
  "\"Ride On!\"",
  "\"Hammer Time!\"",
  "\"Nice!\"",
  "\"Bring it!\"",
  "\"I'm Toast!\"",
  "Bell",
  "Snapshot",
  "End Ride",
  "",
  "Mouse Mode"
};
byte ActionKeys[n_action+1]{
  KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F10,
    KEY_ESCAPE,
    0,
    MOUSE_MODE,
    };

KeyMenu camera_views = KeyMenu(&tft, &ezkey, Camera_Views, 
			       CameraKeys, true,
			       n_camera_view, false,
			       ST7735_BLACK, ST7735_YELLOW,
			       ST7735_BLUE, ST7735_WHITE,
			       9);

KeyMenu actions = KeyMenu(&tft, &ezkey, Actions, 
			  ActionKeys, false,
			  n_action, true,
			  ST7735_BLACK, ST7735_RED,
			  ST7735_BLUE, ST7735_WHITE,
			  9);
Mouse mouse = Mouse(&tft, &ezkey,
		    ST7735_BLACK, ST7735_RED,
		    ST7735_BLUE, ST7735_WHITE,
		    9);
/*
  Alpha alpha = Alpha(&tft, &ezkey,
  ST7735_BLACK, ST7735_RED,
  ST7735_BLUE, ST7735_WHITE,
  64);
*/
uint8_t last_mouse_delta_x;
uint8_t last_mouse_delta_y;
const int n_ui = 3;
UI *uis_pp[n_ui] = {&camera_views, &actions, &mouse};

int n_active_ui = 2;
UI *active_uis_pp[20] = {&camera_views, &actions};

void ui_setup(){
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

  // Use this initializer (uncomment) if you're using a 1.44" TFT
  //tft.initR(INITR_144GREENTAB);   // initialize a ST7735S chip, black tab
  tft.setTextWrap(false); // Allow text to run off right edge
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(3);
}

void toggle_ui(){
  if(n_active_ui == 1){
    n_active_ui = 2;
    active_uis_pp[0] = &camera_views;
    active_uis_pp[1] = &actions;
  }
  else{
    n_active_ui = 1;
    active_uis_pp[0] = &mouse;
  }
  tft.fillScreen(ST7735_BLACK);
  for(int i=0; i<n_active_ui; i++){
    active_uis_pp[i]->begin();
  }
}


void setup(void) {
  SerialDBG.begin(9600);
  ncodr.begin(57600);
  ezkey.begin(9600);

  resetEncoder();
  ui_setup();
  toggle_ui(); // start with mouse for testing
}

int last_enca_pos = -999;
int last_encb_pos = -999;

void handleEvents(){
  readEncoder();
  int enca_pos = enca_u.value / 4;
  int encb_pos = encb_u.value / 4;
  uint8_t btna = enca_u.bytes[2];
  bool depressed_a = (bool)(btna >> 4);
  btna &= 0b1111;
  uint8_t btnb = encb_u.bytes[2];
  bool depressed_b = (bool)(btnb >> 4);
  btnb &= 0b1111;

  if(enca_pos != last_enca_pos){
    for(int i=0; i<n_active_ui; i++){
      if(active_uis_pp[i]->onScrollL(enca_pos)){
	break;
      }
    }
    last_enca_pos = enca_pos;
  }
  if(btna){
    if(btna > 1){
      toggle_ui(); // swap uis
    }
    for(int i=0; i<n_active_ui; i++){
      if(active_uis_pp[i]->onClickL()){
	break;
      }
    }
  }
  if(encb_pos != last_encb_pos){
    for(int i=0; i<n_active_ui; i++){
      if(active_uis_pp[i]->onScrollR(encb_pos)){
	break;
      }
    }
    last_encb_pos = encb_pos;
  }
  if(btnb > 0){
    for(int i=0; i<n_active_ui; i++){
      if(active_uis_pp[i]->onClickR()){
	break;
      }
    }
  }
}

void update(){
  for(int i=0; i<n_active_ui; i++){
    active_uis_pp[i]->update();
  }
}

void loop(void) {
  int fontsize=9;
  int active_view = 5;
  
  tft.setTextSize(1);
  for(int ii=0; ii<11; ii++){
    //tft.setCursor(80, ii * fontsize);
    //tft.setTextColor(ST7735_RED);
    //tft.println(Actions[ii]);
  }
  for(int ii=0; ii<10; ii++){
    //tft.setCursor(0, ii * fontsize);
    //tft.setTextColor(ST7735_YELLOW);
    //tft.println(Camera_Views[ii]);
  }
  while(1){
    handleEvents();
    update();
    delay(4);
  }
  
}

void resetEncoder(){
  ncodr.print("a");
  delay(1);
  ncodr.print("b");
}

bool readEncoder(){
  //read encoder value into global enca_u.value
  bool out = false;
  ncodr.print("R");
  if(ncodr.available()){
    out = true;
    encb_u.bytes[0] = ncodr.read(); // receive a bytes as characters
    encb_u.bytes[1] = ncodr.read(); 
    encb_u.bytes[2] = ncodr.read(); 
    enca_u.bytes[0] = ncodr.read(); 
    enca_u.bytes[1] = ncodr.read(); 
    enca_u.bytes[2] = ncodr.read(); 
    while(ncodr.available()){ // read any remaining bytes left in serial buffer
      ncodr.read();
    }
  }
  return out;
}

