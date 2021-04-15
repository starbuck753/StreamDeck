#ifndef _DECKENCODERS_H_
#define _DECKENCODERS_H_

#include <Arduino.h>
#include "settings.c"


class Encoders {
public:

  void begin(uint8_t encodernumber, uint8_t max);
  void update();
  
  bool changed();
  bool increased();
  bool decreased();
  uint8_t getCurrent();


private:
  uint8_t lastLeftValue, lastRightValue, pinLeft, pinRight;
  uint8_t encoder, lastEncoder, encoderState, maxencoder;
  bool hasIncreased, hasDecreased;

};

#endif