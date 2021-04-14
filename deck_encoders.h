#ifndef _DECKENCODERS_H_
#define _DECKENCODERS_H_

#include <Arduino.h>
#include "settings.c"


class Encoders {
public:

  void begin(uint8_t encodernumber);
  void update();
  
  bool updated();
  bool increased();
  bool decreased();
  int8_t getCurrent();


private:
  uint8_t lastLeftValue, lastRightValue, pinLeft, pinRight;
  int8_t encoder, lastEncoder, encoderState;
};

#endif