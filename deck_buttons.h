#ifndef _DECKBUTTONS_H_
#define _DECKBUTTONS_H_


#include <Arduino.h>
#include "settings.c"


const uint8_t pins[] = {
  BUTTON_PIN_1,
  BUTTON_PIN_2,
  BUTTON_PIN_3,
  BUTTON_PIN_4,
  BUTTON_PIN_5,
  BUTTON_PIN_6,
  BUTTON_PIN_7,
  BUTTON_PIN_8,
  BUTTON_PIN_9
};


class Buttons {
public:
  void begin();
  void update();

  boolean pressed(uint8_t button);
  boolean released(uint8_t button);
  boolean held(uint8_t button, uint16_t time);
  boolean repeat(uint8_t button, uint16_t period=0);
  uint8_t timeHeld(uint8_t button);
  
  uint16_t states[NUM_BTN];

private:

  uint8_t timePerFrame;

};

#endif