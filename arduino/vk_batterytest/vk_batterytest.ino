#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include "UI.h"

// Serial2 pin and pad definitions (in Arduino files Variant.h & Variant.cpp)
#define PIN_SERIAL2_RX       (34ul) // Pin number for PIO_SERCOM on D12
#define PIN_SERIAL2_TX       (36ul) // Pin number for PIO_SERCOM on D10
#define PAD_SERIAL2_TX       (UART_TX_PAD_2)      // SERCOM pad 2
#define PAD_SERIAL2_RX       (SERCOM_RX_PAD_3)    // SERCOM pad 3

#define VBATPIN A7

// Instantiate the Serial2 class
Uart Serial2(&sercom1, 
	     PIN_SERIAL2_RX, PIN_SERIAL2_TX, 
	     PAD_SERIAL2_RX, PAD_SERIAL2_TX);
//

#define ncodr Serial1
//#define SerialDBG SerialUSB // for M0
#define SerialDBG SERIAL_PORT_USBVIRTUAL
#define ezkey Serial2


void setup(){
  SerialDBG.begin(115200);
  SerialDBG.print("buy open hardware and share the future");
}

void loop(){
  float measuredvbat = analogRead(VBATPIN);
  measuredvbat *= 2;    // we divided by 2, so multiply back
  measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
  measuredvbat /= 1024; // convert to voltage
  SerialDBG.print("VBat: " ); Serial.println(measuredvbat);
  delay(100);
}
