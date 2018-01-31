#include "events.h"
#include "VeloKey.h"
#include "kandy_commands.h"

uint8_t mode = 0;
const uint8_t CLOCK_MODE = 0;
const uint8_t STANDBY_MODE = 1;
const uint8_t RACE_MODE = 2;
const uint8_t WAVE_MODE = 3;
const uint8_t N_MODE = 4;
const uint32_t TIMEOUT_us = 10000;
uint32_t last_mode_switch = 0;

void next_mode();
void send_cmd(char cmd);
class ModeListener : public VeloKeyListener{
 public:
  bool locked = false;
  uint16_t color;
  char *name = "Generic Mode";
  uint8_t scroll_left_cw = 0;
  uint8_t scroll_left_ccw = 0;
  uint8_t scroll_center_cw = 0;
  uint8_t scroll_center_ccw = 0;
  uint8_t scroll_right_cw = 0;
  uint8_t scroll_right_ccw = 0;
  ModeListener(){
    color = VELOKEY_BLACK;
    name = "LOCKED";
    scroll_left_cw = 0;
    scroll_left_ccw = 0;
    scroll_center_cw = 0;
    scroll_center_ccw = 0;
    scroll_right_cw = 0;
    scroll_right_ccw = 0;
  }
  void begin(){
    locked = true;
    velokey.drawText(5, 84, color, 2, name);
    velokey.drawText(50, 14, color, 2, ":");
    velokey.drawText(70, 14, color, 2, ":");
    if(locked){
      velokey.drawText(144, 14, color, 2, "L");
    }
    else{
      velokey.drawText(144, 14, color, 2, "U");
    }
  }
  void end(){
    velokey.drawText(5, 84, VELOKEY_BLACK, 2, name);
    velokey.drawText(40, 14, VELOKEY_BLACK, 2, "+");
    velokey.drawText(40, 14, VELOKEY_BLACK, 2, "-");
    velokey.drawText(60, 14, VELOKEY_BLACK, 2, "+");
    velokey.drawText(60, 14, VELOKEY_BLACK, 2, "-");
    velokey.drawText(80, 14, VELOKEY_BLACK, 2, "+");
    velokey.drawText(80, 14, VELOKEY_BLACK, 2, "-");
    velokey.drawText(144, 14, VELOKEY_BLACK, 2, "L");
    velokey.drawText(144, 14, VELOKEY_BLACK, 2, "U");
  }
  void onScrollLeftCW(){
    if(not locked && scroll_left_cw != 0){
      velokey.drawText(40, 14, VELOKEY_BLACK, 2, "-");
      velokey.drawText(40, 14, color, 2, "+");
      send_cmd(scroll_left_cw);
    }
  }
  void onScrollLeftCCW(){
    if(not locked && scroll_left_ccw != 0){
      velokey.drawText(40, 14, VELOKEY_BLACK, 2, "+");
      velokey.drawText(40, 14, color, 2, "-");
      send_cmd(scroll_left_ccw);
    }
  }
  void onScrollCenterCW(){
    if(not locked && scroll_center_cw != 0){
      velokey.drawText(60, 14, VELOKEY_BLACK, 2, "-");
      velokey.drawText(60, 14, color, 2, "+");
      send_cmd(scroll_center_cw);
    }
  }
  void onScrollCenterCCW(){
    if(not locked && scroll_center_ccw != 0){
      velokey.drawText(60, 14, VELOKEY_BLACK, 2, "+");
      velokey.drawText(60, 14, color, 2, "-");
      send_cmd(scroll_center_ccw);
    }
  }
  void onScrollRightCW(){
    if(not locked && scroll_right_cw != 0){
      velokey.drawText(80, 14, VELOKEY_BLACK, 2, "-");
      velokey.drawText(80, 14, color, 2, "+");
      send_cmd(scroll_right_cw);
    }
  }
  void onScrollRightCCW(){
    if(not locked && scroll_right_ccw != 0){
      velokey.drawText(80, 14, VELOKEY_BLACK, 2, "+");
      velokey.drawText(80, 14, color, 2, "-");
      send_cmd(scroll_right_ccw);
    }
  }
  void onScrollLeftPress(){
    if(not locked){
      if(mode != STANDBY_MODE){
	send_cmd(KANDY_DEC_BRIGHTNESS);
      }
    }
  }
  void onScrollLeftRelease(){
  }
  void onScrollRightPress(){
    if(not locked){
      if(mode == STANDBY_MODE){
	send_cmd(KANDY_START);
	next_mode();
      }
      else{
	send_cmd(KANDY_INC_BRIGHTNESS);
      }
    }
  }
  void onScrollRightRelease(){
    if(not locked){
    }
  }
  void onScrollCenterPress(){
  }
  void onScrollCenterRelease(){
    if(millis() - last_mode_switch > 250){
      last_mode_switch = millis();
      next_mode();
      if(mode == 0){ // go back to clock mode
	for(int i=0; i<N_MODE; i++){
	  send_cmd(KANDY_DEC_MODE);
	}
      }
      if(mode == 1){ // move to countdown mode
	send_cmd(KANDY_INC_MODE);
      }
      if(mode == 2){ // move to race mode
	send_cmd(KANDY_INC_MODE);
      }
      if(mode == 3){ // move to wave setup mode
	send_cmd(KANDY_INC_MODE);
      }
    }
  }
  void onButtonNorthPress(){
    velokey.drawText(144, 14, VELOKEY_BLACK, 2, "L");
    velokey.drawText(144, 14, color, 2, "U");
    locked = false;
  }
  void onButtonSouthPress(){
    velokey.drawText(144, 14, VELOKEY_BLACK, 2, "U");
    velokey.drawText(144, 14, color, 2, "L");
    locked = true;
  }
};

class ClockModeListener : public ModeListener{
 public:
  ClockModeListener(){
    color = VELOKEY_WHITE;
    name = "Clock Mode";
    scroll_left_cw = KANDY_INC_HOUR;
    scroll_left_ccw = KANDY_DEC_HOUR;
    scroll_center_cw = KANDY_INC_MIN;
    scroll_center_ccw = KANDY_DEC_MIN;
    scroll_right_cw = KANDY_INC_SEC;
    scroll_right_ccw = KANDY_DEC_SEC;
  }
};

class CountdownModeListener : public ModeListener{
 public:
  CountdownModeListener(){
    color = VELOKEY_YELLOW;
    name = "Countdown Set";
    scroll_left_cw = KANDY_INC_CD_HOUR;
    scroll_left_ccw = KANDY_DEC_CD_HOUR;
    scroll_center_cw = KANDY_INC_CD_MIN;
    scroll_center_ccw = KANDY_DEC_CD_MIN;
    scroll_right_cw = KANDY_INC_CD_SEC;
    scroll_right_ccw = KANDY_DEC_CD_SEC;
  }
};
class RaceModeListener : public ModeListener{
 public:
  RaceModeListener(){
    color = VELOKEY_GREEN;
    name = "Race Adjust";
    locked = true;
    scroll_left_cw = KANDY_INC_RACE_HOUR;
    scroll_left_ccw = KANDY_DEC_RACE_HOUR;
    scroll_center_cw = KANDY_INC_RACE_MIN;
    scroll_center_ccw = KANDY_DEC_RACE_MIN;
    scroll_right_cw = KANDY_INC_RACE_SEC;
    scroll_right_ccw = KANDY_DEC_RACE_SEC;
  }
};
class WaveModeListener : public ModeListener{
 public:
  WaveModeListener(){
    color = VELOKEY_MAGENTA;
    name = "Wave Setup";
    scroll_left_cw = KANDY_INC_N_WAVE;
    scroll_left_ccw = KANDY_DEC_N_WAVE;
    scroll_center_cw = 0;
    scroll_center_ccw = 0;
    scroll_right_cw = KANDY_INC_WAVE_SEP;
    scroll_right_ccw = KANDY_DEC_WAVE_SEP;
  }
};

ClockModeListener clock_listener = ClockModeListener();
CountdownModeListener countdown_listener = CountdownModeListener();
RaceModeListener race_listener = RaceModeListener();
WaveModeListener wave_listener = WaveModeListener();

ModeListener *modes[N_MODE] = {&clock_listener,
			       &countdown_listener,
			       &race_listener,
			       &wave_listener};

void next_mode(){
  velokey.unsubscribe(modes[mode]);
  modes[mode]->end();
  mode++;
  mode %= N_MODE;
  modes[mode]->begin();
  velokey.subscribe(modes[mode]);
  Serial.println(mode);
}

void send_cmd(char cmd){
  Serial1.write(cmd);
}
void setup(){
  
  Serial.begin(115200);
  Serial1.begin(57600);
  velokey.begin();
  velokey.subscribe(&clock_listener);
  
  //velokey.splash(2000);
  velokey.backlightOn(); // critical to see display!
  velokey.drawText(40, 64, VELOKEY_RED, 2, "KandyBar");
  mode = 0;
  modes[mode]->begin();
  // put Kandy in Clock Mode?  (better just sync them by looping)
  //send_cmd(KANDY_DEC_MODE);
  //send_cmd(KANDY_DEC_MODE);
  //send_cmd(KANDY_DEC_MODE);
  //send_cmd(KANDY_DEC_MODE);
}

int count = 0;
long last_us = 0;
unsigned long next = 0;

void loop(){
  velokey.eventDelay(0);
  if(millis() - velokey.last_event_time_us > TIMEOUT_us){
    velokey.backlightOff();
  }
  else{
    velokey.backlightOn(); // critical to see display!
  }
  if(mode == RACE_MODE && !modes[mode]->locked &&
     velokey.scroll_right_down &&
     velokey.scroll_left_down){
    // send race reset
    send_cmd(KANDY_RACE_STOP);
  }
}
