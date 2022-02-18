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

#ifndef _SETTINGS_C_
#define _SETTINGS_C_


//#include <Arduino.h>

// - BUTTONS -----------------------

#define NUM_BTN       9

// Pin definitions

#define BUTTON_PIN_1 4
#define BUTTON_PIN_2 8
#define BUTTON_PIN_3 7
#define BUTTON_PIN_4 6
#define BUTTON_PIN_5 5
#define BUTTON_PIN_6 10
#define BUTTON_PIN_7 16
#define BUTTON_PIN_8 14
#define BUTTON_PIN_9 9


#define BUTTON_1  0
#define BUTTON_2  1
#define BUTTON_3  2
#define BUTTON_4  3
#define BUTTON_5  4
#define BUTTON_6  5
#define BUTTON_7  6
#define BUTTON_8  7
#define BUTTON_9  8


// - KEYBOARD ----------------------

// Media keys
#define KEY_MEDIA_CLEAR 0
#define KEY_VOLUME_UP 1
#define KEY_VOLUME_DOWN 2
#define KEY_VOLUME_MUTE 4
#define KEY_MEDIA_PLAY 8
#define KEY_MEDIA_CALC 16
//#define KEY_MEDIA_PAUSE 16
#define KEY_MEDIA_STOP 32
#define KEY_MEDIA_NEXT 64
#define KEY_MEDIA_PREVIOUS 128
#define KEY_MEDIA_FAST_FORWARD 256
#define KEY_MEDIA_REWIND 512


// Modifiers
#define KEY_WINDOWS 0x83
#define KEY_LCTRL 0x80
#define KEY_LSHIFT 0x81
#define KEY_ESCAPE 0xB1

// Arrow Keys
#define KEY_UP	  0xDA
#define KEY_DOWN	0xD9
#define KEY_LEFT	0xD8
#define KEY_RGHT  0xD7

// Other Keys
#define KEY_SPACE 0x20




// - ENCODER -----------------------
#define ENCODER1  1
#define ENCODER2  2

#define ENCODER1_PIN_L 15
#define ENCODER1_PIN_R 18

#define ENCODER2_PIN_L 20
#define ENCODER2_PIN_R 19



// - PROFILES ----------------------
#define ENCODERPROFILE  1
#define MAXPROFILE 4

// ---------------------------------

// - SIMON -------------------------

#define BUTTON_START  1
#define BUTTON_RED    3
#define BUTTON_BLUE   4
#define BUTTON_GREEN  7
#define BUTTON_YELLOW 8


// ---------------------------------


#endif /* SETTINGS_C */
