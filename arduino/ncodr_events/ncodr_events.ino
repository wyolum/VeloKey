#include <Encoder.h>
#include <ClickButton.h>
// TODO(DONE!): THIS CODE IS BASED ON OLD HARDWARE.  UPDATE PIN13 TO PIN9 and TEST W/ NEW HW
/*
  2 --> ENCA_a
  3 --> ENCA_b
  4 --> ENCA_btn
  5 --> ENCB_a
  6 --> ENCB_b
  7 --> ENBB_btn
  10 -->  West Button
  11 --> North Button
  12 -->  East Button
  13 --> South Button
  A0 --> Center Encoder A
  A1 --> Center Encoder B
  A2 --> Center Button

  encoder interface
  --- Monitor serial interface.  Each byte is an event as defined in events.h
  most significant nybble is device:
  0b0001 -- SCROLL_LEFT
  0b0010 -- SCROLL_RIGHT
  0b0011 -- SCROLL_CENTER
  0b0100 -- BUTTON_NORTH
  0b0101 -- BUTTON_SOUTH
  0b0110 -- BUTTON_EAST
  0b0111 -- BUTTON_WEST
  
  least significant nybble is event type:
  0b00000001 -- CW
  0b00000010 -- CCW
  0b00000011 -- PRESS
  0b00000100 -- RELEASE

  for instance the event 0b00100001 ==> dev 0010, event 0001 ==> SCROLL_RIGHT CW
*/

#define ENCA_a   5
#define ENCA_b   6
#define ENCA_btn 7
#define ENCB_a   2
#define ENCB_b   3
#define ENCB_btn 4
#define ENCC_a   A2
#define ENCC_b   A1
#define ENCC_btn A0
#define N_BUTTON 12
#define S_BUTTON 10
#define E_BUTTON 9
#define W_BUTTON 11

Encoder enca(ENCA_a, ENCA_b);
Encoder encb(ENCB_a, ENCB_b);
Encoder encc(ENCC_a, ENCC_b);

const int n_button = 7;
ClickButton buttons[n_button] = {
  ClickButton(N_BUTTON, LOW, CLICKBTN_PULLUP),
  ClickButton(S_BUTTON, LOW, CLICKBTN_PULLUP),
  ClickButton(E_BUTTON, LOW, CLICKBTN_PULLUP),
  ClickButton(W_BUTTON, LOW, CLICKBTN_PULLUP),
  ClickButton(ENCA_btn, LOW, CLICKBTN_PULLUP),
  ClickButton(ENCB_btn, LOW, CLICKBTN_PULLUP),
  ClickButton(ENCC_btn, LOW, CLICKBTN_PULLUP)
};

const byte DEV_SCROLL_R = 0b00010000;
const byte DEV_SCROLL_L = 0b00100000;
const byte DEV_SCROLL_C = 0b00110000;
const byte DEV_N = 0b01000000;
const byte DEV_S = 0b01010000;
const byte DEV_E = 0b01100000;
const byte DEV_W = 0b01110000;

byte button_devs[n_button] = {DEV_N, DEV_S, DEV_E, DEV_W, DEV_SCROLL_L, DEV_SCROLL_R, DEV_SCROLL_C};
const byte enca_dev = DEV_SCROLL_L;
const byte encb_dev = DEV_SCROLL_R;
const byte encc_dev = DEV_SCROLL_C;

const byte CW = 0b0001;
const byte PRESSED = 0b00000011;
const byte RELEASED = 0b00000100;
const byte CCW = 0b0010;

void setup()
{
  Serial.begin(57600);
  Serial.println("Hello World");
}

void handle_ncodr(Encoder *ncodr_p, byte dev){
  int v = ncodr_p->read();
  if(v > 1){
    for(int ii = 0; ii < v; ii+=2){
      Serial.write(dev | CCW);
    }
    ncodr_p->write(v % 2);
  }
  if(v < -1){
    for(int ii = 0; ii < -v; ii+=2){
      Serial.write(dev | CW);
    }
    ncodr_p->write(v%2);
  }  
}

void loop() 
{
  for(int ii=0; ii<n_button; ii++){
    buttons[ii].Update();
    if(buttons[ii].changed){
      if(buttons[ii].depressed){
	Serial.write(button_devs[ii] | PRESSED);
      }
      else{
	Serial.write(button_devs[ii] | RELEASED);
      }
      buttons[ii].changed = false;
    }
  }
  handle_ncodr(&enca, enca_dev);
  handle_ncodr(&encb, encb_dev);
  handle_ncodr(&encc, encc_dev);
}

