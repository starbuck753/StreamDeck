#ifndef _DECKPROFILES_H_
#define _DECKPROFILES_H_

#include <Arduino.h>

#include "deck_encoders.h"
#include "settings.c"


const String ProfileNameList[] = {
  PROFILE_DAILY,
  PROFILE_MEET,
  PROFILE_GAME,
  PROFILE_SIMON/*,
  PROFILE5_NAME,
  PROFILE6_NAME,
  PROFILE7_NAME,
  PROFILE8_NAME*/
};


// -- Define profile keys -----------------

struct Key {
  String name;
  uint16_t key1;
  uint16_t key2;
  uint16_t key3;
};

const Key KeyMute {"MUTE", 0x00, 0x00};
const Key KeyPTrk {"PTRK", 0x00, 0x00};
const Key KeyPlay {"PLAY", 0x00, 0x00};
const Key KeyNTrk {"NTRK", 0x00, 0x00};
const Key KeyCalc {"CALC", 0x00, 0x00};
const Key KeyLock {"LOCK", 0x83, 0x4C};
const Key KeyKeyb {"KEYB", 0x80, 0x81};
const Key KeyPrSc {"PRSC", 0x00, 0x00};
const Key KeyTask {"TASK", 0x00, 0x00};


const Key DailyKeys[] = {
  KeyMute,
  KeyPTrk,
  KeyPlay,
  KeyNTrk,
  KeyCalc,
  KeyLock,
  KeyKeyb,
  KeyPrSc,
  KeyTask
};




// ----------------------------------------


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

  //Keys keys[NUM_BTN];
  Key currentKeys[NUM_BTN];


private:

  void setCurrent(uint8_t current);

  bool hasChanged;
  uint8_t id;
  String name;

};

#endif