#include "LimitedEnc.h"
/*
 * Limit encoder output from 0 to n_item -1.  If n_item-1 is selected, and a decrement occurs return 
 * n_item-2 regardless of encoder position.
 */

int my_min(int x, int y){
  if(x < y) return x;
  return y;
}
int my_max(int x, int y){
  if(x > y) return x;
  return y;
}
LimitedEnc::LimitedEnc(int current_pos, int _n_item, bool _cw){
  n_item = _n_item;
  last_enc_pos = current_pos;
  ccw = !_cw;
  selected = 0;
  
}
int LimitedEnc::getDelta(int enc_pos){
  int delta = enc_pos - last_enc_pos;
  last_enc_pos = enc_pos;
  return delta;
}
int LimitedEnc::get(int enc_pos){
  int delta = getDelta(enc_pos);
  if(ccw){
    delta = -delta;
  }
  if(delta > 0){
    selected = my_min(selected + delta, n_item - 1);
  }
  if(delta < 0){
    selected = my_max(selected + delta, 0);
  }
  return selected;
}
