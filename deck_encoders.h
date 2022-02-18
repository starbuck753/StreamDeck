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