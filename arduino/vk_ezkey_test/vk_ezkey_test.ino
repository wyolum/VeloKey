#include <EZKey.h>
// Serial2 pin and pad definitions (in Arduino files Variant.h & Variant.cpp)
#define PIN_SERIAL2_RX       (34ul)               // Pin description number for PIO_SERCOM on D12
#define PIN_SERIAL2_TX       (36ul)               // Pin description number for PIO_SERCOM on D10
#define PAD_SERIAL2_TX       (UART_TX_PAD_2)      // SERCOM pad 2
#define PAD_SERIAL2_RX       (SERCOM_RX_PAD_3)    // SERCOM pad 3

// Instantiate the Serial2 class
Uart Serial2(&sercom1, PIN_SERIAL2_RX, PIN_SERIAL2_TX, PAD_SERIAL2_RX, PAD_SERIAL2_TX);
//

#define ezkey Serial2
#define SerialDBG SERIAL_PORT_USBVIRTUAL
// #define SerialDBG SerialUSB // for ArduinoZero
#define ezkey_l2 A4

unsigned long last_high = 0;
unsigned long ezkey_l2_period = 0;
void ezkey_l2_cb(){
  unsigned long now = millis();
  ezkey_l2_period = now - last_high;
  last_high = now;
}

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


uint8_t last_mouse_delta_x;
uint8_t last_mouse_delta_y;
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
  pinMode(ezkey_l2, INPUT);
  attachInterrupt(ezkey_l2, ezkey_l2_cb, RISING);
  SerialDBG.begin(9600);
  // ezkey.begin(9600);
}

bool ezkey_paired = false;
void loop(void) {
  SerialDBG.println((unsigned long)ezkey_l2_period);
  if((ezkey_l2_period > 3500) && 
     (ezkey_l2_period < 4500)){
    if(!ezkey_paired){
      SerialDBG.println("ez key paired");
      ezkey_paired = true;
      ezkey.begin(9600);
      ezkey.print("ezkey");
    }
  }
  else{
    SerialDBG.println("ez key NOT paired!");
    ezkey.end();
    ezkey_paired = false;
  }
  delay(500);
}

