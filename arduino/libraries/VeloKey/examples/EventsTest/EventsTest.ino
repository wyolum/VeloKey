#include "VeloKey.h"
#include "events.h"

VeloKeyListener listener();
VeloKey vk = VeloKey();
void setup(){
  vk.subscribe(listener);
}
void loop(){
}
