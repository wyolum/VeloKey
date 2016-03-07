const int powerup = A5;

#define SerialDBG SERIAL_PORT_USBVIRTUAL

void setup(){
  pinMode(powerup, INPUT);
  SerialDBG.begin(115200);
}

bool powerup_state = false;
void loop(){
  bool new_powerup_state = !digitalRead(powerup);
  if(new_powerup_state != powerup_state){
    powerup_state = new_powerup_state;
    if(!powerup_state){
      Serial.println("click");
    }
  }
}
