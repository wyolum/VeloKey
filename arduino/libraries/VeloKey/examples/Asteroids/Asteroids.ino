#include "events.h"
#include "VeloKey.h"

ConvexPolygonSprite ship = ConvexPolygonSprite();
byte bullets_active = 0;
const byte MAX_ASTEROIDS = 28;
const byte INIT_ASTEROID_SIZE = 16;
const byte MAX_BULLETS = 16;
const int BULLET_DURATION = 2000;
const float BULLET_SPEED = 5.;
const float SHIP_ACCEL = .5;
const float DT = 50;

float ship_vx, ship_vy, ship_x, ship_y;
const float pi = 3.14159;
const float DEG = pi / 180;



class Asteroid: public RectSprite{
 public:
  byte id;
  void setup(uint16_t _x, uint16_t _y, uint16_t _w, uint16_t _h, uint16_t _color, byte _id){
    id = _id;
    RectSprite::setup(_x, _y, _w, _h, _color);
  }
  void update(){
    RectSprite::update();
  }
  void move(uint16_t dx, uint16_t dy){
    RectSprite::move(dx, dy);
  }
};

class Bullet: public RectSprite{
 public:
  unsigned long start;
  Bullet(){
    screen_wrap = true;
  }
  void update(){
    if(!active && !(color == VELOKEY_BLACK)){
      color = VELOKEY_BLACK;
      draw();
    }
    if(active){
      active = millis() < start + BULLET_DURATION;
      if(active){
	RectSprite::update();
	if((x < 0) || (VELOKEY_WIDTH < x) ||
	   (y < 0) || (VELOKEY_HEIGHT < y)){
	  active = false;
	}
      }
      else{
	color = VELOKEY_BLACK;
	draw();
      }
    }
  }
  void fire(float _x, float _y, float _vx, float _vy){
    if(!active){
      start = millis();
      active = true;
      setup(_x, _y, 2, 2, VELOKEY_WHITE);
      vx = _vx;
      vy = _vy;
      draw();
    }
  }
};

Bullet bullets[MAX_BULLETS];
Bullet *bullets_p[MAX_BULLETS];

Asteroid asteroids[MAX_ASTEROIDS];
Asteroid *asteroids_p[MAX_ASTEROIDS];

class MyListener : public VeloKeyListener{
 public:
  void onScrollLeftCW(){
  }
  void onScrollLeftCCW(){
  }
  void onScrollRightCW(){
    ship.rotate(15);
  }
  void onScrollRightCCW(){
    ship.rotate(-15);
  }
  void onScrollLeftPress(){
    if(bullets_active < MAX_BULLETS){
      float dx, dy;
      dx =  sin(ship.theta_deg * DEG);
      dy = -cos(ship.theta_deg * DEG);
      bullets_p[bullets_active++]->fire(ship.x - 1 + 10 * dx, ship.y - 1 + 10 * dy,
					ship.vx + BULLET_SPEED * dx,
					ship.vy + BULLET_SPEED * dy);
    }
  }
  void onScrollRightPress(){
  }
  void onScrollRightRelease(){
  }
};

MyListener my_listener = MyListener();

int16_t ship_xs[3] = {80 +  0, 80 + 5, 80 - 5};
int16_t ship_ys[3] = {64 -  6, 64 + 6, 64 + 6};

int16_t asteroid_xs[6] = {0, 20, 25, 5, -15, -5};
int16_t asteroid_ys[6] = {0, -5, 12, 20, 10, -8};

void restart(){
  float xs[4] = {0,
		 VELOKEY_WIDTH - INIT_ASTEROID_SIZE,
		 VELOKEY_WIDTH - INIT_ASTEROID_SIZE,
		 0};
  float ys[4] = {0,
		 0,
		 VELOKEY_HEIGHT - INIT_ASTEROID_SIZE,
		 VELOKEY_HEIGHT - INIT_ASTEROID_SIZE};
  float vxs[4] = {1, -1, -.7, 1.1};
  float vys[4] = {1, .7, -.8, -.6};
  for(int i = 0; i < 4; i++){
    asteroids[i].setup(xs[i], ys[i], INIT_ASTEROID_SIZE, INIT_ASTEROID_SIZE, VELOKEY_WHITE, i);
    asteroids[i].active = true;
    asteroids[i].vx = vxs[i];
    asteroids[i].vy = vys[i];
  }
  for(int i = 4; i < 4 + 8; i++){
    asteroids[i].setup(0, 0, INIT_ASTEROID_SIZE / sqrt(2), INIT_ASTEROID_SIZE / sqrt(2), VELOKEY_WHITE, i);
    asteroids[i].active = false;
  }
  for(int i = 4 + 8; i < 4 + 8 + 16; i++){
    asteroids[i].setup(0, 0, INIT_ASTEROID_SIZE / 2, INIT_ASTEROID_SIZE / 2, VELOKEY_WHITE, i);
    asteroids[i].active = false;
  }
}
void setup(){
  Serial.begin(115200);
  velokey.begin();
  ship.setup(3, ship_xs, ship_ys, VELOKEY_WHITE);
  ship_x = ship.x;
  ship_y = ship.y;
  // velokey.splash(2000);
  velokey.backlightOn();
  velokey.subscribe(&my_listener);
  ship.rotate(0);
  for(byte i=0; i < MAX_BULLETS; i++){
    bullets[i].setup(80, 80, 2, 2, VELOKEY_WHITE);
    bullets_p[i] = &bullets[i];
  }
  restart();
}

int sign(int val){
  return (bool)(val > 0) * 2 - 1;
}

void loop(){
  velokey.eventDelay(DT);
  if(velokey.scroll_right_down){
    ship.vx += SHIP_ACCEL * sin(ship.theta_deg * DEG);
    ship.vy -= SHIP_ACCEL * cos(ship.theta_deg * DEG);
  }
  byte n_asteroid = 0;
  for(int i=0; i < MAX_ASTEROIDS; i++){
    asteroids[i].update();
    if(asteroids[i].active){
      n_asteroid++;
    
      for(int j = 0; j < bullets_active; j++){
	if(asteroids[i].collide(bullets_p[j])){
	  // 0 -->  4, 5  /*   4 + 2 * i, 5 + 2 * i */
	  // 1 -->  6, 7   
	  // 2 -->  8, 9
	  // 3 --> 10, 11
	  // 4 --> 12, 13
	  // 5 --> 14, 15
	  // 6 --> 16, 17
	  // 7 --> 18, 19
	  // 8 --> 20, 21
	  // 9 --> 22, 23
	  //10 --> 24, 25
	  //11 --> 26, 27
	  asteroids[i].color = VELOKEY_BLACK;
	  asteroids[i].draw();
	  asteroids[i].active = false;
	  bullets[j].active = false;
	  if(i < 12){ // explode
	    asteroids[2 * i + 4].active = true;
	    asteroids[2 * i + 5].active = true;
	    asteroids[2 * i + 4].setup(asteroids[i].x,
				       asteroids[i].y,
				       asteroids[i].w / sqrt(2),
				       asteroids[i].h / sqrt(2),
				       VELOKEY_WHITE, 0);
	    asteroids[2 * i + 5].setup(asteroids[i].x,
				       asteroids[i].y,
				       asteroids[i].w / sqrt(2),
				       asteroids[i].h / sqrt(2),
				       VELOKEY_WHITE, 0);

	    asteroids[2 * i + 4].vx =  asteroids[i].vy;
	    asteroids[2 * i + 4].vy = -asteroids[i].vx;
	    asteroids[2 * i + 5].vx = -asteroids[i].vy;
	    asteroids[2 * i + 5].vy =  asteroids[i].vx;
	  }
	}
      }
      if(ship.collide(&asteroids[i])){
	Serial.print(i);
	Serial.println(" crash!");
      }
    }
  }
  if(n_asteroid == 0){
    restart();
  }
  ship.update();
  bullets_active = 0;
  for(int i=0; i < MAX_BULLETS; i++){
    bullets[i].update();
    bullets_p[i] = &bullets[bullets_active];
    bullets_active += bullets[i].active;
  }
}
