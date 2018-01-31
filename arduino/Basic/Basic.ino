#include "events.h"
#include "VeloKey.h"

class MyListener : public VeloKeyListener{
 public:
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
  void onScrollRightRelease(){
  }
};

MyListener my_listener = MyListener();

void setup(){
  Serial.begin(115200);
  velokey.begin();
  velokey.splash(2000); // turns off backlight to save battery
  velokey.backlightOn(); // critical to see display!
  velokey.drawText(2, 58, VELOKEY_RED, 2, "Hello VeloKey");
}


void loop(){
  velokey.eventDelay(0); // allow velokey to read encoder events
}
