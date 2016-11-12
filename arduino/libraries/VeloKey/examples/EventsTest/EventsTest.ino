#include "events.h"
#include "VeloKey.h"

//VeloKey vk = VeloKey();

RectSprite ball = RectSprite(80, 80, 4, 4, VELOKEY_WHITE);
RectSprite player1 = RectSprite(0, 80 - 15, 3, 30, VELOKEY_BLUE);
RectSprite player2 = RectSprite(160-3, 80 - 15, 3, 30, VELOKEY_GREEN);

class MyListener : public VeloKeyListener{
  void onScrollLeftCW(){
    player1.move(0, 5);
  }
  void onScrollLeftCCW(){
    player1.move(0, -5);
  }
  void onScrollRightCW(){
    player2.move(0, -5);
  }
  void onScrollRightCCW(){
    player2.move(0, 5);
  }
};

MyListener my_listener = MyListener();

void setup(){
  Serial.begin(115200);
  Serial.println("Hello1");
  velokey.begin();
  Serial.println("Hello2");
  velokey.splash(2000);
  velokey.backlightOn();
  player1.draw();
  player2.draw();
  velokey.subscribe(&my_listener);
}

const uint16_t d = 10;
int16_t dx = 1;
int16_t dy = 1;

uint16_t count;
void loop(){
  unsigned long last_time = 0;
  uint16_t x0, y0, x1, y1, r, color;
  unsigned int now = millis();
  
  while(millis() - now < d){
    velokey.captureEvents();
    velokey.handleEvents();
  }
  if(dx > 0 and ball.x > VELOKEY_WIDTH - ball.w - player2.w){
    dx *= -1;
  }
  if(dx < 0 and ball.x < player1.w){
    dx *= -1;
  }
  if(dy > 0 and ball.y > VELOKEY_HEIGHT - ball.h){
    dy *= -1;
  }
  if(dy < 0 and ball.y < 0){
    dy *= -1;
  }
  // now = millis();
  ball.move(dx, dy);
  player1.draw();
  player2.draw();
  if(count++ == 100){
    redraw();
  }
  // Serial.println(millis() - now);
}

void redraw(){
  for(int row=0; row<160; row++){
    for(int col=0; col<160; col++){
      //velokey.drawPixel(getPixel(col, row));
    }
  }
}
