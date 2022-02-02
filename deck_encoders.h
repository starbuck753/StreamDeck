#ifndef _DECKENCODERS_H_
#define _DECKENCODERS_H_

#include <Arduino.h>
#include "settings.c"


class Encoders {
public:

  void begin(uint8_t encodernumber, uint8_t initialState = 0, uint8_t max = 255);
  void update();
  
  bool changed();
  bool increased();
  bool decreased();
  uint8_t getCurrent();


private:
  uint8_t lastLeftValue, lastRightValue, pinLeft, pinRight;
  uint8_t encoder, maxencoder;
  bool hasIncreased, hasDecreased;

};

#endif