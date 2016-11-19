#include "events.h"
#include "VeloKey.h"

class MyListener : public VeloKeyListener{
  void onScrollLeftCW(){
  }
  void onScrollLeftCCW(){
  }
  void onScrollRightCW(){
  }
  void onScrollRightCCW(){
  }
  void onScrollLeftPress(){
  }
  void onScrollRightPress(){
  }  
};

MyListener my_listener = MyListener();

int16_t ship_xs[3] = {80 + 0, 80 + 5, 80 - 5};
int16_t ship_ys[3] = {64 - 5, 64 + 5, 64 + 5};
ConvexPolygonSprite ship = ConvexPolygonSprite();

void setup(){
  Serial.begin(115200);
  velokey.begin();
  ship.setup(3, ship_xs, ship_ys, VELOKEY_WHITE);
  // velokey.splash(2000);
  velokey.backlightOn();
  velokey.subscribe(&my_listener);
  for(int ii=0; ii=90; ii++){
    ship.rotate(1);
    ship.draw();
    delay(100);
  }
}

void loop(){
}
