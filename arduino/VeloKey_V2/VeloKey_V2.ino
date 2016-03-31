/* 
 * changes from V1:
 *     new splash screen
 *     alpha UI
 *     ezkey verification
 */
#include <Mouse.h>
#include <Keyboard.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <EZKey.h>
#include "LimitedEnc.h"
#include "UI.h"
// #include "logo.h"
#include "logo_rgb.h"

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
//#define SerialDBG SerialUSB // for M0
#define SerialDBG SERIAL_PORT_USBVIRTUAL
#define ezkey Serial2

#define TFT_CS     5  
#define TFT_RST    9  
#define TFT_DC     6
#define TFT_SCLK 13   // set these to be whatever pins you like!
#define TFT_MOSI 11   // set these to be whatever pins you like!
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, 
				      TFT_SCLK, TFT_RST);
Adafruit_ST7735 *tft_p = &tft;
const int ezkey_l2 = A4;
const int powerup_pin = A5;
unsigned long last_high = 0;
unsigned long ezkey_l2_period = 0;
void ezkey_l2_cb(){
  unsigned long now = millis();
  ezkey_l2_period = now - last_high;
  last_high = now;
}

int last_enca_pos = -999;
int last_encb_pos = -999;
bool depressed_a = false;
bool depressed_b = false;

bool ezkey_linked = false;
bool update_ezkey_linking(void) {
  if((ezkey_l2_period > 3500) && 
     (ezkey_l2_period < 4500)){
    if(!ezkey_linked){
      ezkey_linked = true;
      ezkey.begin(9600);
    }
  }
  else{
    ezkey.end();
    ezkey_linked = false;
  }
  return ezkey_linked;
}

void consumerCommand(uint8_t mask0,uint8_t mask1) {
  ezkey.write(0xFD);
  ezkey.write((byte)0x00);
  ezkey.write((byte)0x02);
  ezkey.write(mask0);
  ezkey.write(mask1);
  ezkey.write((byte)0x00);
  ezkey.write((byte)0x00);
  ezkey.write((byte)0x00);
  ezkey.write((byte)0x00);
}

void ezkey_volume_up(){
  consumerCommand(0x10, 0x00);
  consumerCommand(0x00, 0x00);
}
void ezkey_volume_down(){
  consumerCommand(0x20, 0x00);
  consumerCommand(0x00, 0x00);
}

union Data{
  int16_t value;
  char bytes[3];
};
Data enca_u;
Data encb_u;

const int n_camera_view = 8;
char *Camera_Views[n_camera_view] = {
  "Head On",
  "1st Person",
  "Side",
  "3rd Person",
  "Right Rear",
  "Birdseye",
  "Helicopter",
  "Specator",
  };

byte CameraKeys[n_camera_view]{ 
  EZKEY_6, // Head on
    EZKEY_3, // first person
    EZKEY_4, // Side
    EZKEY_1, // third person
    EZKEY_5, // Right Rear
    EZKEY_9, // Birds eye
    EZKEY_8, // Heli
    EZKEY_7, // Spectator
    };

const uint8_t n_action = 13;
char *Actions[n_action] = {
  "< LEFT",
  "^ STRAIGHT",
  "> RIGHT",
  "v U-TURN",
  "Elbow Flick", // f1
  "Wave",        // f2
  "\"Ride On!\"",// f3
  //  "\"HammerTime\"",// f4
  // "\"Nice!\"",      // f5
  // "\"Bring it!\"",  // f6
  "\"I'm Toast!\"", // f7
  // "Bell",           // f8
  "Message",       // M
  "Snapshot",      // f10
  "Changing Room", // T
  "<Alt-Tab>",
  "End Ride",      // ESC
};
byte ActionKeys[n_action+1]{
    EZKEY_ARROW_LEFT, 
    EZKEY_ARROW_UP,
    EZKEY_ARROW_RIGHT,
    EZKEY_ARROW_DOWN,
    EZKEY_F1, // Elbow
    EZKEY_F2, // Wave
    EZKEY_F3, // Ride on
    //    EZKEY_F4, // Hammer Time
    //    EZKEY_F5, // Nice
    //    EZKEY_F6, // Bringit
    EZKEY_F7, // I'm toast
    //    EZKEY_F8, // Bell
    EZKEY_M, // Message
    EZKEY_F10, // Snapshot
    EZKEY_T, // changing room
    ALT_TAB, 
    EZKEY_ESCAPE, // End ride
    };

bool camera_immediate = true; // for BT free demo
KeyMenu camera_views = KeyMenu(&tft, &ezkey, Camera_Views, 
			       CameraKeys, camera_immediate,
			       n_camera_view, true,
			       ST7735_BLACK, ST7735_YELLOW,
			       ST7735_BLUE, ST7735_WHITE,
			       9);

KeyMenu actions = KeyMenu(&tft, &ezkey, Actions, 
			  ActionKeys, false,
			  n_action, false,
			  ST7735_BLACK, ST7735_RED,
			  ST7735_BLUE, ST7735_WHITE,
			  9);
Mouse_ui mouse = Mouse_ui(&tft, &ezkey,
		    ST7735_BLACK, ST7735_RED,
		    ST7735_BLUE, ST7735_WHITE,
		    9);


Alpha alpha = Alpha(&tft, &ezkey,
		    ST7735_BLACK, ST7735_RED,
		    ST7735_BLUE, ST7735_WHITE,
		    true,
		    15);
Numeric numeric = Numeric(&tft, &ezkey,
			  ST7735_BLACK, ST7735_BLUE,
			  ST7735_BLUE, ST7735_WHITE,
			  false,
			  15);

uint8_t last_mouse_delta_x;
uint8_t last_mouse_delta_y;
const int n_ui = 5;
UI *uis_pp[n_ui] = {&camera_views, &actions, &mouse, &alpha, &numeric};

int n_active_ui = 2;
UI *active_uis_pp[20] = {&camera_views, &actions};

void ui_setup(){
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

  // Use this initializer (uncomment) if you're using a 1.44" TFT
  //tft.initR(INITR_144GREENTAB);   // initialize a ST7735S chip, black tab
  tft.setTextWrap(false); // Allow text to run off right edge
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(3);
  splash();
  pinMode(A7, OUTPUT);
}

void swap_mouse(){
  if(n_active_ui == 1){
    n_active_ui = 2;
    active_uis_pp[0] = &camera_views;
    active_uis_pp[1] = &actions;

    // reset encoders to old selected positions
    actions.lenc     ->last_enc_pos = last_enca_pos;
    camera_views.lenc->last_enc_pos = last_encb_pos;

    actions.lenc     ->selected =      actions.selected;
    camera_views.lenc->selected = camera_views.selected;
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

void swap_kb(){
  if(active_uis_pp[0] == &numeric){
    n_active_ui = 2;
    active_uis_pp[0] = &actions;
    active_uis_pp[1] = &camera_views;

    // reset encoders to old selected positions
    actions.lenc     ->last_enc_pos = last_enca_pos;
    camera_views.lenc->last_enc_pos = last_encb_pos;

    actions.lenc     ->selected =      actions.selected;
    camera_views.lenc->selected = camera_views.selected;
  }
  else{
    n_active_ui = 2;
    active_uis_pp[0] = &numeric;
    active_uis_pp[1] = &alpha;

    // reset encoders to old selected positions
    numeric.lenc->last_enc_pos = last_enca_pos;
    alpha.lenc  ->last_enc_pos = last_encb_pos;

    alpha.lenc  ->selected = alpha.selected;
    numeric.lenc->selected = numeric.selected;
  }
  tft.fillScreen(ST7735_BLACK);
  for(int i=0; i<n_active_ui; i++){
    active_uis_pp[i]->begin();
  }
}


void setup(void) {
  SerialDBG.begin(9600);
  ncodr.begin(57600);
  attachInterrupt(ezkey_l2, ezkey_l2_cb, RISING);
  // ezkey.begin(9600);// begin after linking

  pinMode(powerup_pin, INPUT);
  resetEncoder();
  ui_setup();
  for(int i=0; i<n_active_ui; i++){
    active_uis_pp[i]->begin();
  }
  // swap_mouse(); // start with mouse for testing
  Mouse.begin();
}

bool powerup_state = false;
bool check_powerup(){
  bool out = false;
  bool new_powerup_state = !digitalRead(powerup_pin);
  if(new_powerup_state != powerup_state){
    // button changed
    powerup_state = new_powerup_state;
    if(!powerup_state){ // was button just released?
      out = true;       // button was clicked
    }
  }
  return out;
}

void handleEvents(){
  readEncoder();
  update_ezkey_linking();
  
  if(check_powerup() && ezkey_linked){
    ezkey.print(" ");
  }
  
  int enca_pos = enca_u.value / 4;
  int encb_pos = encb_u.value / 4;
  uint8_t btna = enca_u.bytes[2];

  depressed_a = (bool)(btna >> 4);
  btna &= 0b1111;
  uint8_t btnb = encb_u.bytes[2];
  depressed_b = (bool)(btnb >> 4);
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
    if(btna > 1){ // double click a to swap interfaces
      swap_kb(); // swap uis
      btna = 0;
    }
    else{
      for(int i=0; i<n_active_ui; i++){
	if(active_uis_pp[i]->onClickL()){
	  break;
	}
      }
    }
  }
  if(encb_pos != last_encb_pos){
    bool handled = false;
    for(int i=0; i<n_active_ui; i++){
      if(active_uis_pp[i]->onScrollR(encb_pos)){
	handled = true;
	break;
      }
    }
    if(!handled){
      // send a volume command
      if(encb_pos < last_encb_pos && last_encb_pos != -999){
	ezkey_volume_up();
	SerialDBG.print(encb_pos);
	SerialDBG.print(" up ");
	SerialDBG.println(last_encb_pos);
      }
      else if(encb_pos > last_encb_pos && last_encb_pos != -999){
	ezkey_volume_down();
	SerialDBG.print(encb_pos);
	SerialDBG.print(" down ");
	SerialDBG.println(last_encb_pos);
      }
      handled = true;
    }
    last_encb_pos = encb_pos;
  }
  if(btnb > 0){
    if(btnb > 1){ // double click b to swap interfaces
      swap_mouse(); // swap uis
      btnb = 0;
    }
    else{
      for(int i=0; i<n_active_ui; i++){
	if(active_uis_pp[i]->onClickR()){
	  break;
	}
      }
    }
  }
}

void update(){
  for(int i=0; i<n_active_ui; i++){
    // SerialDBG.print("    ");SerialDBG.println(i);
    active_uis_pp[i]->update(depressed_a, depressed_b);
    delay(1);
  }
}

void splash(){
  // grey scale
  /*
  uint8_t i = 0; 
  uint8_t r, g, b;
  tft.setAddrWindow(0, 0, 159, 127);
  for(uint8_t row = 0; row < 128; row++){
    for(uint8_t col = 0; col < 160; col++){
      int index = (col * 128 + row);
      r = image[index];
      g = r;
      b = r;
      tft.pushColor(tft.Color565(r, g, b));
    }
  }
  */
  // color
    tft.fillScreen(ST7735_WHITE);
    for(int i = 0; i < n_rgb565; i++){
      tft.drawPixel(rgb565_rows[i], rgb565_cols[i], rgb565[i]);
    }
    int blink_counter = 0;
    char * by_wyolum = "by WyoLum";
    tft.fillCircle(160-10, 128-10, 7, ST7735_BLUE);
    tft.setCursor(80, 100);
    tft.setTextColor(ST7735_BLUE);
    tft.setTextSize(1);
    for(int ii = 0; ii < 9; ii ++){
      tft.print(by_wyolum[ii]);
      delay(100);
    }
    // just in case it never got printed above
    while(!ezkey_linked){
      update_ezkey_linking();
      tft.fillCircle(160-10, 128-10, 7, ST7735_BLUE);
      delay(666);
      tft.fillCircle(160-10, 128-10, 5, ST7735_WHITE);
      delay(334);
      blink_counter++;
    }
    delay(1000);
}

void loop(void) {
  int active_view = 5;
  
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
  delay(10);
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

