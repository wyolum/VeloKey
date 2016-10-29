#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include "logo.h"
#include "events.h"

// define display pins
const uint8_t TFT_SCLK = 13;   // set these to be whatever pins you like!
const uint8_t TFT_MOSI = 11;   // set these to be whatever pins you like!
const uint8_t TFT_DC   =  6;   // "Data/Control" pin
const uint8_t TFT_CS   =  5;
const uint8_t TFT_RST  =  9;  // you can also connect this to the Arduino reset
const int DISPLAY_BACKLIGHT = A3;
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

uint8_t player_w = 3;
uint8_t player_h = 20;
uint16_t player1_color = ST7735_BLUE;
uint16_t player2_color = ST7735_GREEN;
uint8_t player1_x = 3;
const uint8_t WIDTH = ST7735_TFTHEIGHT_18;
const uint8_t HEIGHT = ST7735_TFTWIDTH;
uint8_t player2_x = WIDTH - 3 - player_w;
uint8_t player1_y = (WIDTH - player_h) / 2;
uint8_t player2_y = (WIDTH - player_h) / 2;
int16_t ball_x = player1_x;
int16_t ball_y = 64;
uint8_t ball_w = 3;
int8_t ball_vx = 2;
int8_t ball_vy = 2;
uint16_t ball_color = ST7735_WHITE;

uint8_t player1_score = 0;
uint8_t player2_score = 0;

// encoder serail port
#define ncodr Serial1

bool read_ncodr_events();

void setup(void) {
  ncodr.begin(57600);
  Serial.begin(115200);
  Serial.print("Buy Open Hardware and take stock in the future!");

  // Use this initializer if you're using a 1.8" TFT
  pinMode(DISPLAY_BACKLIGHT, OUTPUT);
  digitalWrite(DISPLAY_BACKLIGHT, HIGH);
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

  // Use this initializer (uncomment) if you're using a 1.44" TFT
  //tft.initR(INITR_144GREENTAB);   // initialize a ST7735S chip, black tab

  Serial.println("init");

  tft.setTextWrap(false); // Allow text to run off right edge
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(3);
  splash();
  draw_scores();
  draw_player(1, player1_y, player1_color);
  draw_player(2, player2_y, player2_color);
  delay(1000);
}

void draw_player(byte player, byte top, uint16_t color){
  uint8_t x;
  if(player == 1){
    x = player1_x;
  }
  else{
    x = player2_x;
  }
  
  tft.fillRect(x,                                            // x
	       top,                                          // y
	       player_w,                                     // w
	       player_h,                                     // h
	       color);                                       // color
}

void draw_scores(){
  tft.fillRect(0, 0, WIDTH, 15, ST7735_BLACK);
  
  tft.setCursor(16, 0);
  tft.setTextColor(player1_color);
  tft.setTextSize(2);
  tft.println(player1_score);

  tft.setCursor(WIDTH - 10 - 24, 0);
  tft.setTextColor(player2_color);
  tft.setTextSize(2);
  tft.println(player2_score);
  tft.drawFastHLine(0, 17, WIDTH, ST7735_WHITE);

}
void update_ball(){
  // erase ball at old position
  tft.fillRect(ball_x, ball_y, ball_w, ball_w, ST7735_BLACK);

  // check bounces
  if(ball_vy > 0 && ball_y + ball_w >= HEIGHT){
    ball_vy *= -1;
  }
  if(ball_vy < 0 && ball_y < 20){
    ball_vy *= -1;
  }
  if(ball_vx > 0 && ball_x >= (int)player2_x - ball_w){
    if(player2_y <= ball_y && ball_y < player2_y + player_h){
      ball_vx *= -1;
    }
  }
  if(ball_vx < 0 && ball_x <= (int)player1_x + player_w){
    if(player1_y <= ball_y && ball_y < player1_y + player_h){
      ball_vx *= -1;
    }
  }

  ball_x += ball_vx;
  ball_y += ball_vy;
  if(ball_x <= 0){
    player2_score++;
    draw_scores();
    delay(1000);
    ball_x = player2_x - player_w;
    //ball_y = player2_y;
    ball_vx = -abs(ball_vx);
    draw_player(1, player1_y, player1_color);
    draw_player(2, player2_y, player2_color);
  }
  if(ball_x >= WIDTH){
    player1_score++;
    draw_scores();
    delay(1000);
    ball_x = player1_x;
    // ball_y = player1_y;
    ball_vx = abs(ball_vx);
    draw_player(1, player1_y, player1_color);
    draw_player(2, player2_y, player2_color);
  }
  tft.fillRect(ball_x, ball_y, ball_w, ball_w, ball_color);
}

void loop(){
  if(ncodr.available()){
    draw_player(1, player1_y, ST7735_BLACK);
    draw_player(2, player2_y, ST7735_BLACK);
    read_ncodr_events();
    draw_player(1, player1_y, player1_color);
    draw_player(2, player2_y, player2_color);
  }
  update_ball();
  delay(14);
}


bool read_ncodr_events(){
  //read encoder value into global enca_u.value
  uint8_t event = 0;
  bool out = false;
  byte step = 4;
  
  for(int ii=0; ii<ncodr.available(); ii++){
    out = true;
    event = ncodr.read(); // got a new event add to queue
    // handle event
    if((event & INPUT_MASK) == SCROLL_LEFT){
      if((event & ACTION_MASK) == CW){
	if(player1_y < ST7735_TFTHEIGHT_144 - step - player_h){
	  player1_y += step;
	}
      }
      else if((event & ACTION_MASK) == CCW){
	if(player1_y > step + 20){
	  player1_y -= step;
	}
      }
    }
    if((event & INPUT_MASK) == SCROLL_RIGHT){
      if((event & ACTION_MASK) == CCW){
	if(player2_y < ST7735_TFTHEIGHT_144 - step - player_h){
	  player2_y += step;
	}
      }
      else if((event & ACTION_MASK) == CW){
	if(player2_y > step + 20){
	  player2_y -= step;
	}
      }
    }
  }
  return out;
}

void splash(){
  tft.fillScreen(ST7735_WHITE);
  for(int i = 0; i < n_rgb565; i++){
    tft.drawPixel(rgb565_rows[i], rgb565_cols[i], rgb565[i]);
  }
  int blink_counter = 0;
  char * by_wyolum = "by WyoLum";
  tft.setCursor(80, 100);
  tft.setTextColor(ST7735_BLUE);
  tft.setTextSize(1);
  for(int ii = 0; ii < 9; ii ++){
    tft.print(by_wyolum[ii]);
    delay(100);
  }
  delay(1000);
  //delay(500);
  tft.fillScreen(ST7735_BLACK);
}

