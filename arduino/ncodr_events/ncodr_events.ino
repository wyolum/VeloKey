#include <Encoder.h>
#include <ClickButton.h>
#include "events.h" 
// TODO(DONE!): THIS CODE IS updaged from OLD HARDWARE code.  UPDATEd PIN13 TO PIN9 and TEST W/ NEW HW
/*
   2 --> ENCA_a
   3 --> ENCA_b
   4 --> ENCA_btn
   5 --> ENCB_a
   6 --> ENCB_b
   7 --> ENBB_btn
   9 --> South Button
  10 -->  West Button
  11 --> North Button
  12 -->  East Button
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
#define E_BUTTON 12 // was N (modified for OTS hardware v3)
#define W_BUTTON 10 // was S
#define S_BUTTON 9  // was E
#define N_BUTTON 11 // was W

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

const byte DEV_SCROLL_R = SCROLL_LEFT;
const byte DEV_SCROLL_L = SCROLL_RIGHT;
const byte DEV_SCROLL_C = SCROLL_CENTER;
const byte DEV_N = BUTTON_NORTH;
const byte DEV_S = BUTTON_SOUTH;
const byte DEV_E = BUTTON_EAST;
const byte DEV_W = BUTTON_WEST;

byte button_devs[n_button] = {DEV_N, DEV_S, DEV_E, DEV_W, DEV_SCROLL_L, DEV_SCROLL_R, DEV_SCROLL_C};
const byte enca_dev = DEV_SCROLL_L;
const byte encb_dev = DEV_SCROLL_R;
const byte encc_dev = DEV_SCROLL_C;

/* // already defined in events.h
const byte CW = 0b0001;
const byte PRESSED = 0b00000011;
const byte RELEASED = 0b00000100;
const byte CCW = 0b0010;
*/
void setup()
{
  Serial.begin(57600);
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
	Serial.write(button_devs[ii] | PRESS);
      }
      else{
	Serial.write(button_devs[ii] | RELEASE);
      }
      buttons[ii].changed = false;
    }
  }
  handle_ncodr(&enca, enca_dev);
  handle_ncodr(&encb, encb_dev);
  handle_ncodr(&encc, encc_dev);
}

