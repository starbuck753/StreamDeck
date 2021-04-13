#ifndef _DECKENCODERS_H_
#define _DECKENCODERS_H_

#include <Arduino.h>
#include "settings.c"



class Encoders {
public:

  void begin();
  void update();
  


private:
  uint8_t LastLeftValue;
  uint8_t LastRightValue;

};

#endif