#ifndef _LIMITED_ENC_H
#define _LIMITED_ENC_H

class LimitedEnc{
 public:
  int n_item;
  int selected;
  int last_enc_pos;
  bool ccw;
  LimitedEnc(int current_pos, int _n_item, bool _ccw);
  int getDelta(int _current_pos);
  int get(int _current_pos);
};
#endif
