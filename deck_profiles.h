#ifndef _DECKPROFILES_H_
#define _DECKPROFILES_H_

#include <Arduino.h>

#include "deck_encoders.h"
#include "settings.c"


const uint8_t ProfileList[] = {
  PROFILE1
};


class Profiles {
public:

  Encoders encoder;

  void begin();
  void update();
  

  bool updated();
  //bool profileIncreased();
  //bool profileDecreased();
  uint8_t getCurrent();

  uint16_t keys[NUM_BTN];

private:
  bool isUpdated;
  uint8_t current;

};

#endif