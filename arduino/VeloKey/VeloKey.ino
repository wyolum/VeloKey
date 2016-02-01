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
#include <EZKey.h>
// Serial2 pin and pad definitions (in Arduino files Variant.h & Variant.cpp)
#define PIN_SERIAL2_RX       (34ul)               // Pin description number for PIO_SERCOM on D12
#define PIN_SERIAL2_TX       (36ul)               // Pin description number for PIO_SERCOM on D10
#define PAD_SERIAL2_TX       (UART_TX_PAD_2)      // SERCOM pad 2
#define PAD_SERIAL2_RX       (SERCOM_RX_PAD_3)    // SERCOM pad 3

// Instantiate the Serial2 class
Uart Serial2(&sercom1, PIN_SERIAL2_RX, PIN_SERIAL2_TX, PAD_SERIAL2_RX, PAD_SERIAL2_TX);
//

#ifdef USE_ATMEGA328
#include <SoftwareSerial.h>
SoftwareSerial ncodr = SoftwareSerial(A0, A1);
SoftwareSerial ezkey = SoftwareSerial(A2, A3);
#else
#define ncodr Serial1
#define ezkey Serial2
#define Serial SerialUSB
#endif

// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS     8
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

void keyCommand(
		uint8_t modifiers, uint8_t keycode1, uint8_t keycode2, 
		uint8_t keycode3, uint8_t keycode4, uint8_t keycode5, 
		uint8_t keycode6) {
  ezkey.write(0xFD);       // our command
  ezkey.write(modifiers);  // modifier!
  ezkey.write((byte)0x00); // 0x00  
  ezkey.write(keycode1);   // key code #1
  ezkey.write(keycode2); // key code #2
  ezkey.write(keycode3); // key code #3
  ezkey.write(keycode4); // key code #4
  ezkey.write(keycode5); // key code #5
  ezkey.write(keycode6); // key code #6
}


void mouseCommand(uint8_t buttons, uint8_t delta_x, uint8_t delta_y) {
  ezkey.write(0xFD);
  ezkey.write((byte)0x00);
  ezkey.write((byte)0x03);
  ezkey.write(buttons);
  ezkey.write(delta_x);
  ezkey.write(delta_y);
  ezkey.write((byte)0x00);
  ezkey.write((byte)0x00);
  ezkey.write((byte)0x00);
  last_mouse_delta_x = delta_x;
  last_mouse_delta_y = delta_y;
}

void setup(void) {
  pinMode(2, HIGH);
  pinMode(3, LOW);
  Serial.begin(9600);
  ncodr.begin(28800);
  ncodr.write('a'); // zero out encoder a
  delay(1);
  ncodr.write('b'); // zero out encoder b
  delay(1);
  // ezkey.begin(9600);
  // Use this initializer if you're using a 1.8" TFT
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

  // Use this initializer (uncomment) if you're using a 1.44" TFT
  //tft.initR(INITR_144GREENTAB);   // initialize a ST7735S chip, black tab

  tft.setTextWrap(false); // Allow text to run off right edge
  tft.fillScreen(ST7735_BLACK);

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
 int position_a = enca_u.value / 4;
 int last_position_a = -999;
 int position_b = enca_u.value / 4;
 int last_position_b = -999;
 unsigned long long last_enca_press = 0;
 while(1){
   readEncoder();
   if(enca_u.bytes[2]){
     //send a key_command
     if(millis() - last_enca_press > 1000){
       last_enca_press = millis();
       // Serial.println("F1"); delay(100);
       keyCommand(MODIFIER_NONE, KEY_F1, 0, 0, 0, 0, 0); // test keycode
       keyCommand(MODIFIER_NONE, 0, 0, 0, 0, 0, 0); // test keycode
     }
   }
   position_a = enca_u.value / 4;
   position_b = encb_u.value / 4;
   Serial.print(position_a);
   Serial.print(" ");
   Serial.println(position_b);
   if(position_a < 0)position_a = 8 - (-position_a % 8);
   if(position_a > 7)position_a = position_a % 8;
   if(position_a != last_position_a){
     // undo old selection
     tft.fillRect(0, last_position_a * fontsize, 80, 9, ST7735_BLACK);
     tft.setCursor(0, last_position_a * fontsize);
     tft.setTextColor(ST7735_YELLOW);
     tft.println(Camera_Views[last_position_a]);

     tft.fillRect(0, position_a * fontsize, 80, 9, ST7735_BLUE);
     tft.setCursor(0, position_a * fontsize);
     tft.setTextColor(ST7735_WHITE);
     tft.println(Camera_Views[position_a]);
   }
   last_position_a = position_a;
   delay(10);
 }

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

