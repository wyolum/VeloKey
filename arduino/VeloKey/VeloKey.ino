/***************************************************
  This is a library for the Adafruit 1.8" SPI display.

This library works with the Adafruit 1.8" TFT Breakout w/SD card
  ----> http://www.adafruit.com/products/358
The 1.8" TFT shield
  ----> https://www.adafruit.com/product/802
The 1.44" TFT breakout
  ----> https://www.adafruit.com/product/2088
as well as Adafruit raw 1.8" TFT display
  ----> http://www.adafruit.com/products/618

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <SoftwareSerial.h>
#include <EZKey.h>

SoftwareSerial ncodr = SoftwareSerial(A0, A1);
SoftwareSerial ezkey = SoftwareSerial(A2, A3);

// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS     10
#define TFT_RST    9  // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to 0!
#define TFT_DC     8

// Option 1 (recommended): must use the hardware SPI pins
// (for UNO thats sclk = 13 and sid = 11) and pin 10 must be
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
union Data{
  int16_t value;
  char bytes[3];
};

Data enca_u;
Data encb_u;

char *Camera_Views[8] = {
  "1st Person",
  "2nd Person",
  "3nd Person",
  "Side",
  "Right Rear",
  "Specator",
  "Helicopter",
  "Birdseye"
};

// Option 2: use any pins but a little slower!
// #define TFT_SCLK 13   // set these to be whatever pins you like!
// #define TFT_MOSI 11   // set these to be whatever pins you like!
// Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

uint8_t last_mouse_delta_x;
uint8_t last_mouse_delta_y;

void keyCommand(SoftwareSerial Serial1, 
		uint8_t modifiers, uint8_t keycode1, uint8_t keycode2, 
		uint8_t keycode3, uint8_t keycode4, uint8_t keycode5, 
		uint8_t keycode6) {
  Serial1.write(0xFD);       // our command
  Serial1.write(modifiers);  // modifier!
  Serial1.write((byte)0x00); // 0x00  
  Serial1.write(keycode1);   // key code #1
  Serial1.write(keycode2); // key code #2
  Serial1.write(keycode3); // key code #3
  Serial1.write(keycode4); // key code #4
  Serial1.write(keycode5); // key code #5
  Serial1.write(keycode6); // key code #6
}


void mouseCommand(SoftwareSerial Serial1, 
		  uint8_t buttons, uint8_t delta_x, uint8_t delta_y) {
  Serial1.write(0xFD);
  Serial1.write((byte)0x00);
  Serial1.write((byte)0x03);
  Serial1.write(buttons);
  Serial1.write(delta_x);
  Serial1.write(delta_y);
  Serial1.write((byte)0x00);
  Serial1.write((byte)0x00);
  Serial1.write((byte)0x00);
  last_mouse_delta_x = delta_x;
  last_mouse_delta_y = delta_y;
}

void setup(void) {
  Serial.begin(9600);
  Serial.print("Hello! Adafruit ST7735 rotation test");

  ncodr.begin(28800);
  // Use this initializer if you're using a 1.8" TFT
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

  // Use this initializer (uncomment) if you're using a 1.44" TFT
  //tft.initR(INITR_144GREENTAB);   // initialize a ST7735S chip, black tab

  Serial.println("init");

  tft.setTextWrap(false); // Allow text to run off right edge
  tft.fillScreen(ST7735_BLACK);

  Serial.println("This is a test of the rotation capabilities of the TFT library!");
  Serial.println("Press <SEND> (or type a character) to advance");
}

void loop(void) {
  rotateText();
}

void rotateText() {
  int fontsize=9;
  int active_view = 5;
  
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(3);
  tft.setTextSize(1);
 tft.setTextColor(ST7735_RED);
 tft.setCursor(80, 0);
 tft.println("Elbow Flick");
 tft.setCursor(80, fontsize*1);
 tft.println("Wave");
 tft.setCursor(80, fontsize*2);
 tft.println("Ride On!");
 tft.setCursor(80, fontsize*3);
 tft.println("Hammer Time!");
 tft.setCursor(80, fontsize*4);
 tft.setTextColor(ST7735_WHITE);
 tft.println("Nice!");
 tft.setTextColor(ST7735_RED);
 tft.setCursor(80, fontsize*5);
 tft.println("Bring it!");
 tft.setCursor(80, fontsize*6);
 tft.println("I'm Toast!");
 tft.setCursor(80, fontsize*7);
 tft.println("Bell");
 tft.setCursor(80, fontsize*8);
 tft.println("Screen Shot");
 readEncoder();
 int position = enca_u.value / 4;
 int last_position = -999;
 while(1){
   readEncoder();
   if(enca_u.bytes[2]){
     //send a key_command
     keyCommand(ezkey, MODIFIER_NONE, KEY_F1, 0, 0, 0, 0, 0); // test keycode
   }
   position = enca_u.value / 4;
   if(position < 0)position = 8 - (-position % 8);
   if(position > 7)position = position % 8;
   if(position != last_position){
     // undo old selection
     tft.fillRect(0, last_position * fontsize, 80, 9, ST7735_BLACK);
     tft.setCursor(0, last_position * fontsize);
     tft.setTextColor(ST7735_YELLOW);
     tft.println(Camera_Views[last_position]);

     tft.fillRect(0, position * fontsize, 80, 9, ST7735_BLUE);
     tft.setCursor(0, position * fontsize);
     tft.setTextColor(ST7735_WHITE);
     tft.println(Camera_Views[position]);
     Serial.print(last_position);
     Serial.print(" ");
     Serial.print(position);
     Serial.print(" ");
     Serial.println(enca_u.value);
   }
   last_position = position;
   delay(10);
 }

 while (!Serial.available());
 Serial.read();  Serial.read();  Serial.read();
}

bool readEncoder(){
  //read encoder value into global enca_u.value
  bool out = false;
  ncodr.print("R");
  if(ncodr.available()){
    out = true;
    enca_u.bytes[0] = ncodr.read(); // receive a byte as character
    enca_u.bytes[1] = ncodr.read(); // receive a byte as character
    enca_u.bytes[2] = ncodr.read(); // receive a byte as character
    encb_u.bytes[0] = ncodr.read(); // receive a byte as character
    encb_u.bytes[1] = ncodr.read(); // receive a byte as character
    encb_u.bytes[2] = ncodr.read(); // receive a byte as character
    while(ncodr.available()){
      ncodr.read();
    }
  }
  return out;
}

