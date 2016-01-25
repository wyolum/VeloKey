#include <Encoder.h>

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

bool enca_button_state = false;
bool encb_button_state = false;

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

void loop() 
{
// buttons stays active till sent
  if(!enca_button_state){
    enca_button_state = (digitalRead(ENCA_btn) == LOW);
  }
  if(!encb_button_state){
    encb_button_state = (digitalRead(ENCB_btn) == LOW);
  }
  if(Serial.available()){
    while(Serial.available()){
      Serial.read(); // soak up any extra chars
    }
    enca_u.value = enca.read();
    enca_u.bytes[2] = enca_button_state;
    encb_u.value = encb.read();
    encb_u.bytes[2] = encb_button_state;
    Serial.write(enca_u.bytes[0]);
    Serial.write(enca_u.bytes[1]);
    Serial.write(enca_u.bytes[2]);
    Serial.write(encb_u.bytes[0]);
    Serial.write(encb_u.bytes[1]);
    Serial.write(encb_u.bytes[2]);

    enca_button_state = false; // clear buttons
    encb_button_state = false;
  }
  digitalWrite(4, enca.read() & 0b1);
  //digitalWrite(7, enca.read() & 0b10);
  digitalWrite(7, enca_button_state);
}

