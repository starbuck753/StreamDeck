#ifndef _SETTINGS_C_
#define _SETTINGS_C_

// - BUTTONS -----------------------

#define NUM_BTN       4

// Pin definitions

#define BUTTON_PIN_1 2
#define BUTTON_PIN_2 3
#define BUTTON_PIN_3 4
#define BUTTON_PIN_4 5
/*#define BUTTON_PIN5 6
#define BUTTON_PIN6 7
#define BUTTON_PIN7 8
#define BUTTON_PIN8 9*/


#define BUTTON_1  0
#define BUTTON_2  1
#define BUTTON_3  2
#define BUTTON_4  4


// - ENCODER -----------------------
#define ENCODER1  1
#define ENCODER2  2

#define ENCODER1_PIN_L 9
#define ENCODER1_PIN_R 10




// - PROFILES ----------------------
#define ENCODERPROFILE  1
#define MAXPROFILE 8

#define PROFILE1 1

#define PROFILE_DAILY "DAILY"
#define PROFILE_MEET "MEETING"
#define PROFILE_GAME "GAMING"
#define PROFILE_SIMON "SIMON"
#define PROFILE5_NAME "PROFILE5"
#define PROFILE6_NAME "PROFILE6"
#define PROFILE7_NAME "PROFILE7"
#define PROFILE8_NAME "PROFILE8"



/*#define LeftCtrl    = 0x80
#define UpArrow	    = 0xDA
#define DownArrow	  = 0xD9
#define LeftArrow	  = 0xD8
#define RightArrow  = 0xD7*/

/*
enum class Keys : uint16_t {
  LeftCtrl    = 0x80,
  UpArrow	    = 0xDA,
  DownArrow	  = 0xD9,
  LeftArrow	  = 0xD8,
  RightArrow  = 0xD7
};
*/


// ---------------------------------

// - SIMON -------------------------

#define BUTTON_START  1
#define BUTTON_RED    3
#define BUTTON_BLUE   4
#define BUTTON_GREEN  7
#define BUTTON_YELLOW 8






// ---------------------------------


#endif /* SETTINGS_C */
