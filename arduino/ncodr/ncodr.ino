#include <Encoder.h>
/*
  encoder interface
  commands:
  "R" -- Read six bytes from two encoders
  "a" -- Reset encoder a to zero count, and button counts to zero
  "b" -- Reset encoder b to zero count, and button counts to zero
  
  message format:
  byte1  byte2  byte3  byte4  byte5  byte6 
  <---posa--->  btna   <---pos2--->  btn2

  posa -- signed 2 byte int -- encoder a position
  btna -- byte              -- number of button a clicks since last read
  posb -- signed 2 byte int -- encoder b position
  btnb -- byte              -- number of button b clicks since last read
 */
#define ENCA_a 5
#define ENCA_b 6
#define ENCB_a A3
#define ENCB_b A4
#define ENCA_btn 2
#define ENCB_btn 3

Encoder enca(ENCA_a, ENCA_b);
Encoder encb(ENCB_a, ENCB_b);

union Data{
  int value;
  unsigned char bytes[3];
};

Data enca_u;
Data encb_u;

byte enca_button_count = 0;
byte encb_button_count = 0;
unsigned long a_last_pressed = 0;
unsigned long b_last_pressed = 0;

void setup()
{
  pinMode(ENCA_btn, INPUT_PULLUP);
  pinMode(ENCB_btn, INPUT_PULLUP);

  // flash leds
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  for(int ii=0; ii < 3; ii++){
    digitalWrite(4, HIGH);
    digitalWrite(7, LOW);
    delay(100);
    digitalWrite(7, HIGH);
    digitalWrite(4, LOW);
    delay(100);
  }
  digitalWrite(7, LOW);
  digitalWrite(4, LOW);
  Serial.begin(28800);//Serial.println("Support open hardware and share the future");
}

bool ba_was_open = true;
bool bb_was_open = true;

void loop() 
{
// buttons stays active till sent
  bool ba_closed = (digitalRead(ENCA_btn) == LOW);
  bool bb_closed = (digitalRead(ENCB_btn) == LOW);
  if(ba_closed && ba_was_open){
    if(millis() - a_last_pressed > 100){
      enca_button_count++;
      a_last_pressed = millis();
    }
  }
  ba_was_open = !ba_closed;

  if(bb_closed && bb_was_open){
    if(millis() - b_last_pressed > 100){
      encb_button_count++;
      b_last_pressed = millis();
    }
  }
  bb_was_open = !bb_closed;
  if(Serial.available()){
    char command = Serial.read();
    while(Serial.available()){
      Serial.read(); // soak up any extra chars
    }
    if(command == 'R'){
      enca_u.value = enca.read();
      enca_u.bytes[2] = enca_button_count;
      encb_u.value = encb.read();
      encb_u.bytes[2] = encb_button_count;
      Serial.write(enca_u.bytes[0]);
      Serial.write(enca_u.bytes[1]);
      Serial.write(enca_u.bytes[2]);
      Serial.write(encb_u.bytes[0]);
      Serial.write(encb_u.bytes[1]);
      Serial.write(encb_u.bytes[2]);
      enca_button_count = 0; // clear buttons
      encb_button_count = 0;
    }
    else if (command == 'a'){
      enca.write(0);
    }
    else if (command == 'b'){
      encb.write(0);
    }
  }
  digitalWrite(4, enca.read() & 0b1);
  //digitalWrite(7, enca.read() & 0b10);
  digitalWrite(7, enca_button_count);
}

