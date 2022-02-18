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