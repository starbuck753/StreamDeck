/*
  Copyright (c) 2022, Starbuck753
  Original code (pre-library): Copyright (c) 2011, Peter Barrett

  Permission to use, copy, modify, and/or distribute this software for
  any purpose with or without fee is hereby granted, provided that the
  above copyright notice and this permission notice appear in all copies.

  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
  WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR
  BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES
  OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
  WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
  ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
  SOFTWARE.
 */

#ifndef _DECKPROFILES_H_
#define _DECKPROFILES_H_

#include <Arduino.h>

#include "deck_encoders.h"
#include "settings.c"

//#define PROFILE1 1
const char PROFILE_DAILY[8] = "DAILY";
const char PROFILE_MEET[8] = "MEETING";
const char PROFILE_GAME[8] = "GAMING";
const char PROFILE_SIMON[8] = "SIMON";


enum ProfileName {
  Daily,
  Meeting,
  Gaming,
  Simon
};



// -- Define profile keys -----------------

struct Key {
  char* name;
  bool isMedia;
  uint8_t key1;
  uint8_t key2;
  uint8_t key3;
};

// Red Button (same for all Profiles)
const Key KeyLock {"LOCK", false, KEY_WINDOWS, 0x6C, 0};

//Daily
const Key KeyPTrk {"PTRK", true, KEY_MEDIA_PREVIOUS};
const Key KeyPlay {"PLAY", true, KEY_MEDIA_PLAY};
const Key KeyNTrk {"NTRK", true, KEY_MEDIA_NEXT};
const Key KeyCalc {"CALC", true, KEY_MEDIA_CALC};

const Key KeyFile {"FILE", false, KEY_WINDOWS, 0x65, 0};
const Key KeyKeyb {"KEYB", false, KEY_LCTRL, KEY_LSHIFT, 0};
const Key KeyPrSc {"PRSC", false, KEY_LSHIFT, KEY_WINDOWS, 0x73};
const Key KeyTask {"TASK", false, KEY_LCTRL, KEY_LSHIFT, KEY_ESCAPE};


// Meeting
const Key KeyWCam {"WCAM", false, KEY_LCTRL, KEY_LSHIFT, 0x6F};
const Key KeyMute {"MUTE", false, KEY_LCTRL, KEY_LSHIFT, 0x6D};
const Key KeyShar {"SHAR", false, KEY_LCTRL, KEY_LSHIFT, KEY_SPACE};
const Key KeyBlur {"BLUR", false, KEY_LCTRL, KEY_LSHIFT, 0x70};


const Key KeyActi {"ACTI", false, KEY_LCTRL, 0x31, 0};
const Key KeyChat {"CHAT", false, KEY_LCTRL, 0x32, 0};
const Key KeyCale {"CALE", false, KEY_LCTRL, 0x34, 0};
const Key KeySrch {"SRCH", false, KEY_LCTRL, 0x65, 0};


// Gaming
const Key KeyShft {"SHFT", false, KEY_LSHIFT, 0, 0};
const Key KeyUp   {" UP ", false, KEY_UP, 0, 0};
const Key KeyCtrl {"CTRL", false, KEY_LCTRL, 0, 0};
//const Key KeyBlur {"SHFT", true, 0x00, 0x00, 0x00};

const Key KeyLeft {"LEFT", false, KEY_LEFT, 0, 0};
const Key KeyDown {"DOWN", false, KEY_DOWN, 0, 0};
const Key KeyRght {"RGHT", false, KEY_RGHT, 0, 0};
const Key KeySpce {"SPCE", false, KEY_SPACE, 0, 0};


const Key DailyKeys[] = {
  KeyLock,
  KeyPTrk,
  KeyPlay,
  KeyNTrk,
  KeyCalc,
  KeyFile,
  KeyKeyb,
  KeyPrSc,
  KeyTask
};

const Key MeetingKeys[] = {
  KeyLock,
  KeyWCam,
  KeyMute,
  KeyShar,
  KeyBlur,
  KeyActi,
  KeyChat,
  KeyCale,
  KeySrch
};


const Key GamingKeys[] = {
  KeyLock,
  KeyShft,
  KeyUp,
  KeyCtrl,
  KeyShft,
  KeyLeft,
  KeyDown,
  KeyRght,
  KeySpce
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
  char* getName();

  //Keys keys[NUM_BTN];
  Key currentKeys[NUM_BTN];


private:

  void setCurrent(uint8_t current);

  bool hasChanged;
  uint8_t id;
  char* name;

};

#endif