#include <Encoder.h>
#include <ClickButton.h>

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
  commands:
  "R" -- Read six bytes from three encoders with center buttons.  ENCC has NSWE uttons too
  "a" -- Reset encoder a to zero count, and button counts to zero
  "b" -- Reset encoder b to zero count, and button counts to zero
  "c" -- Reset encoder c to zero count, and button counts to zero
  
  message format:
  byte1  byte2  byte3  byte4  byte5  byte6 byte7  byte8  byte9 byte10
  <---posa--->  btna   <---posb--->  btn2  <---posc--->  btnc NSEW

  posa -- signed 2 byte int -- encoder a position
  btna -- byte              -- number of button a clicks since last read
  0b00 -- not pressed
  0b01 -- pressed
  0b10 -- released
  0b11 -- click
  
  posb -- signed 2 byte int -- encoder b position
  btnb -- byte              -- number of button b clicks since last read
  0b00 -- not pressed
  0b01 -- pressed
  0b10 -- released
  0b11 -- click
 */
#ifdef PROTOTYPE
#define ENCA_a 5
#define ENCA_b 6
#define ENCB_a A3
#define ENCB_b A4
#define ENCA_btn 2
#define ENCB_btn 3
#define LED_1 4
#define LED_2 7
#else

#define ENCA_a   5
#define ENCA_b   6
#define ENCA_btn 7
#define ENCB_a   2
#define ENCB_b   3
#define ENCB_btn 4

#define LED_1 13
#define LED_2 13
#endif

Encoder enca(ENCA_a, ENCA_b);
Encoder encb(ENCB_a, ENCB_b);
ClickButton buttons[2] = {ClickButton(ENCA_btn, LOW, CLICKBTN_PULLUP),
			  ClickButton(ENCB_btn, LOW, CLICKBTN_PULLUP)};
union Data{
  int value;
  unsigned char bytes[3];
};

Data enca_u;
Data encb_u;

byte enca_button = 0;
byte encb_button = 0;
unsigned long a_last_pressed = 0;
unsigned long b_last_pressed = 0;

void setup()
{
  // not needed with ClickButton library?
  // pinMode(ENCA_btn, INPUT_PULLUP);
  // pinMode(ENCB_btn, INPUT_PULLUP);
  

  // flash leds
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  for(int ii=0; ii < 3; ii++){
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, LOW);
    delay(100);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_1, LOW);
    delay(100);
  }
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_1, LOW);
  Serial.begin(57600);
}
bool ba_was_open = true;
bool bb_was_open = true;

void loop() 
{
  buttons[0].Update();
  if(buttons[0].clicks){
    enca_u.bytes[2] = (byte)(abs(buttons[0].clicks));
  }
  buttons[1].Update();
  if(buttons[1].clicks){
    encb_u.bytes[2] = (byte)(abs(buttons[1].clicks));
  }
  /*
  if(buttons[0].clicks){
    Serial.print(buttons[0].clicks);
    Serial.print(" ");
    Serial.print(buttons[0].depressed << 4);
    Serial.print(" ");
    Serial.println(abs(buttons[0].clicks) + (abs(buttons[0].depressed) << 4));
    }*/

  if(Serial.available()){
    char command = Serial.read();
    while(Serial.available()){
      Serial.read(); // soak up any extra chars
    }
    if(command == 'R'){
      enca_u.value = enca.read();
      encb_u.value = encb.read();
      enca_u.bytes[2] += (buttons[0].depressed << 4);
      encb_u.bytes[2] += (buttons[1].depressed << 4);
      // (buttons[1].depressed << 4));
      Serial.write(enca_u.bytes[0]);
      Serial.write(enca_u.bytes[1]);
      Serial.write(enca_u.bytes[2]);
      Serial.write(encb_u.bytes[0]);
      Serial.write(encb_u.bytes[1]);
      Serial.write(encb_u.bytes[2]);
      enca_u.bytes[2] = 0;
      encb_u.bytes[2] = 0;
    }
    else if (command == 'a'){
      enca.write(0);
    }
    else if (command == 'b'){
      encb.write(0);
    }
  }
  digitalWrite(LED_1, enca.read() & 0b1);
  digitalWrite(LED_2, enca_button);
}

