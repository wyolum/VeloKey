#include "EZKey.h"
void keyCommand(uint8_t modifiers, uint8_t keycode1, uint8_t keycode2, 
		uint8_t keycode3, uint8_t keycode4, uint8_t keycode5, 
		uint8_t keycode6);

void setup(){
  Serial1.begin(9600);
  SerialUSB.begin(115200);
  SerialUSB.println("Hello");
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
}
bool keys[4];
uint8_t key_map[4] = {0, KEY_B, KEY_C, KEY_D};
bool last_keys[4];

void getKeys(){
  int keys_down = 0;
  uint8_t key_codes[4];
  uint8_t modifier;
  bool stale = false;

  for(int i=0; i<4; i++){
    keys[i] = digitalRead(2 + i) == LOW;
    key_codes[i] = key_map[i] * keys[i];
    if(keys[i] != last_keys[i]){
      stale = true;
      last_keys[i] = keys[i];
    }
  }
  if(keys[0]){
    modifier = MODIFIER_SHIFT_LEFT;
  }
  else{
    modifier = MODIFIER_NONE;
  }
  if(stale){
    keyCommand(modifier, 
	       key_codes[0], key_codes[1], 
	       key_codes[2], key_codes[3], 
	       0, 0);
    SerialUSB.println("Key Change");
  }
}

void loop(){
  getKeys(); 
}


void keyCommand(uint8_t modifiers, uint8_t keycode1, uint8_t keycode2, 
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
