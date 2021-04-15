#ifndef _DECKPROFILES_H_
#define _DECKPROFILES_H_

#include <Arduino.h>

#include "deck_encoders.h"
#include "settings.c"


const String ProfileNameList[] = {
  PROFILE1_NAME,
  PROFILE2_NAME,
  PROFILE3_NAME,
  PROFILE4_NAME,
  PROFILE5_NAME,
  PROFILE6_NAME,
  PROFILE7_NAME,
  PROFILE8_NAME
};


class Profiles {
public:

  Encoders encoder;

  void begin();
  void update();
  

  bool changed();
  //bool profileIncreased();
  //bool profileDecreased();
  uint8_t getId();
  String getName();

  uint16_t keys[NUM_BTN];

private:
  bool hasChanged;
  uint8_t id;
  String name;

};

#endif