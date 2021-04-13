#ifndef _DECKPROFILES_H_
#define _DECKPROFILES_H_

#include <Arduino.h>
#include "settings.c"



class Profiles {
public:

  void begin();
  void update();
  
  void setProfile(uint8_t profile);

  uint8_t getProfile();

  uint16_t keys[NUM_BTN];

private:
  uint8_t current;

};

#endif