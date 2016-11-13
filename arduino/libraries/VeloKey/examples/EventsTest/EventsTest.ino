#include "events.h"
#include "VeloKey.h"

//VeloKey vk = VeloKey();

const byte PLAYER_H = 30;

RectSprite ball = RectSprite(80, 80, 4, 4, VELOKEY_WHITE);
RectSprite player1 = RectSprite(    0, 80 - 15, 3, PLAYER_H, VELOKEY_BLUE);
RectSprite player2 = RectSprite(160-3, 80 - 15, 3, PLAYER_H, VELOKEY_GREEN);

bool pending_p1_serve = true;
bool pending_p2_serve = false;

class MyListener : public VeloKeyListener{
  void onScrollLeftCW(){
    if(player1.y + player1.h < 128){
      player1.move(0, 5);
    }
  }
  void onScrollLeftCCW(){
    if(player1.y > 0){
      player1.move(0, -min(5, player1.y));
    }
  }
  void onScrollRightCW(){
    if(player2.y > 0){
      player2.move(0, -min(5, player2.y));
    }
  }
  void onScrollRightCCW(){
    if(player2.y + player2.h < 128){
      player2.move(0, 5);
    }
  }
  void onScrollLeftPress(){
    if(pending_p1_serve){
      pending_p1_serve = false;
    }
  }
  void onScrollRightPress(){
    if(pending_p2_serve){
      pending_p2_serve = false;
    }
  }  
};

MyListener my_listener = MyListener();

void setup(){
  Serial.begin(115200);
  velokey.begin();
  eventDelay(10);
  Serial.println(velokey.scroll_center_down);
  velokey.splash(2000);
  velokey.backlightOn();
  player1.draw();
  player2.draw();
  velokey.subscribe(&my_listener);
  display_score();
}

const uint16_t dt = 10;
int16_t dx = 2;
int16_t dy = 2;

byte p1_score = 0;
byte p2_score = 0;

uint16_t count = 0;

void serve_p1(){
}
void serve_p2(){
}

void display_score(){
  // pop up score
  int w = 140;
  int h = 50;
  int font_w = 24;
  velokey.fillRect((160 - w) / 2, (128 - h) / 2, w, h, VELOKEY_BLACK);
  velokey.drawText(font_w, (128 - h) / 2, VELOKEY_BLUE, 3, p1_score);
  if(p2_score > 10){
    velokey.drawText(160-3 * font_w,  (128 - h) / 2, VELOKEY_GREEN, 3, p2_score);
  }
  else{
    velokey.drawText(160-2*font_w,  (128 - h) / 2, VELOKEY_GREEN, 3, p2_score);
  }
  eventDelay(1000);
  if(p1_score > 9){
    velokey.fillRect((160 - w) / 2, (128 - h) / 2 + h / 2, w, h, VELOKEY_BLACK);
    velokey.drawText((160 - w) / 2, (128 - h) / 2 + h / 2, VELOKEY_BLUE, 3, (char*)"P1 WINS!");
    if(player1.h > 5){
      player1.h -= 5;
      player1.move(0, 5);
    }
    p1_score = 0;
    p2_score = 0;
    eventDelay(2000);
    display_score();
  }
  else if(p2_score > 9){
    velokey.fillRect((160 - w) / 2, (128 - h) / 2 + h / 2, w, h, VELOKEY_BLACK);
    velokey.drawText((160 - w) / 2, (128 - h) / 2 + h / 2, VELOKEY_GREEN, 3, "P2 WINS!");
    if(player2.h > 5){
      player2.h -= 5;
      player2.move(0, 5);
    }
    p1_score = 0;
    p2_score = 0;
    eventDelay(2000);
    display_score();
  }
  else{
    eventDelay(1000);
  }
  velokey.fillRect((160 - w) / 2, (128 - h) / 2, w, h, VELOKEY_BLACK);
}

void reset(){
  p1_score = 0;
  p2_score = 0;
  player1.h = PLAYER_H;
  player2.h = PLAYER_H;
  player1.y = 80 - player1.h / 2;
  player2.y = 80 - player2.h / 2;
  velokey.fillRect(26, 10, 140, 40, VELOKEY_BLACK);
  velokey.drawText(26, 10, VELOKEY_RED, 3, "RESET!");
  player1.draw();
  player2.draw();
  display_score();
  velokey.fillRect(26, 10, 140, 40, VELOKEY_BLACK);
  pending_p1_serve = true;
}

void eventDelay(uint16_t ms){
  unsigned int now = millis();
  while(millis() - now < ms){
    velokey.captureEvents();
    velokey.handleEvents();
  }
  if(velokey.scroll_center_down){
    reset();
  }
}

void loop(){
  unsigned long last_time = 0;
  uint16_t x0, y0, x1, y1, r, color;

  eventDelay(dt);
  if(velokey.scroll_center_down){
  }
  if(pending_p1_serve || pending_p2_serve){
    if(pending_p1_serve){
      player1.draw();
      ball.move(player1.x - ball.x + player1.w + 1, player1.y - ball.y);
    }
    if(pending_p2_serve){
      player2.draw();
      ball.move(player2.x - ball.x - ball.w - 1, player2.y - ball.y);
    }
    return;
  }
  if(dx > 0 && ball.x+ball.w > VELOKEY_WIDTH ){
    dx *= -1;
    p1_score += 1;
    Serial.println("point for p1");
    display_score();
    pending_p2_serve = true;
  }
  if(dx < 0 && ball.x < 0){
    dx *= -1;
    p2_score += 1;
    Serial.println("point for p2");
    display_score();
    pending_p1_serve = true;
  }
  if(dy > 0 &&  ball.y > VELOKEY_HEIGHT - ball.h){
    dy *= -1;
  }
  if(dy < 0 && ball.y < 0){
    dy *= -1;
  }
  // now = millis();
  ball.move(dx, dy);
  if (ball.collide(&player1) && dx < 0){
    Serial.println("ouch player 1");
    dx *= -1;
  }
  if (ball.collide(&player2) && dx > 0){
    Serial.println("ouch player 2");
    dx *= -1;
  }
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
