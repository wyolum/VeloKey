#include "events.h"
#include "VeloKey.h"

VeloKey vk = VeloKey();

class MyListener : public VeloKeyListener{
  void onScrollLeftCW(){
    Serial.println("MyListener::onScrollLeftCW()");
  }
};

MyListener my_listener = MyListener();

void setup(){
  Serial.begin(115200);
  ncodr.begin(57600);
  vk.subscribe(&my_listener);
}
void loop(){
  vk.captureEvents();
  vk.handleEvents();
}
