#include <Encoder.h>

#define ENCA_a 5
#define ENCA_b 6
#define ENCB_a A3
#define ENCB_b A4

Encoder enca(ENCA_a, ENCA_b);

union {
  int value;
  unsigned char bytes[2];
} position_u;

void setup()
{
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
  Serial.begin(115200);//Serial.println("Support open hardware and share the future");
}

void loop() 
{
  if(Serial.available()){
    position_u.value = enca.read();
    while(Serial.available()){
      Serial.read();
    }
    Serial.write(position_u.bytes[0]);
    Serial.write(position_u.bytes[1]);
  }
  digitalWrite(4, enca.read() & 0b1);
  digitalWrite(7, enca.read() & 0b10);
}
