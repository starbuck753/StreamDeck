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

#include <Arduino.h>

//Include Buttons and Profiles
#include "deck_buttons.h"
#include "deck_profiles.h"
#include "deck_encoders.h"


// Include Wire Library for I2C
#include <Wire.h>

// Include Adafruit Graphics & OLED libraries
#include <Adafruit_SSD1306.h>

//Include Keyboard library
#include <Keyboard.h>


// Reset pin not used but needed for library
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);


Buttons buttons;
Profiles profiles;
Encoders volume;


//For Media buttons!
uint8_t data[2];

// For direct use of USB HID (yes, 3 is left out)
const uint8_t kHID_ReportID_ConsumerControl =  4;

static const uint8_t HID_ReportDescriptor_ConsumerControl[] PROGMEM =
{
    0x05, 0x0c,                           // Usage Page ("Consumer Devices")
    0x09, 0x01,                           // Usage (Consumer Control)
    0xa1, 0x01,                           // Collection (Application)
    0x85, kHID_ReportID_ConsumerControl,  // "Report ID"
    0x15, 0x00,                           // Logical Minimum (0)
    0x25, 0x01,                           // Logical Maximum (1)
    0x09, 0xe9,                           // Usage (Volume Up)
    0x09, 0xea,                           // Usage (Volume Down)
    0x75, 0x01,                           // Report Size (1)
    0x95, 0x02,                           // Report Count (2)
    0x81, 0x06,                           // Input (Data, Variable, Relative)

    0x09, 0xe2,                           // Usage (Mute)
    0x95, 0x01,                           // Report Count (1)
    0x81, 0x06,                           // Input (Data, Variable, Relative)

    0x09, 0xcd,                           // Usage (Play/Pause)
    //0x09, 0xb0,                           // Usage (Play/Pause)
    0x95, 0x01,                           // Report Count (1)
    0x81, 0x06,                           // Input (Data, Variable, Relative)

    0x09, 0x192,                           // Usage (CALC)
    //0x09, 0xb1,                           // Usage (Pause)
    0x95, 0x01,                           // Report Count (1)
    0x81, 0x06,                           // Input (Data, Variable, Relative)

    0x09, 0xb7,                           // Usage (Stop)
    0x95, 0x01,                           // Report Count (1)
    0x81, 0x06,                           // Input (Data, Variable, Relative)

    0x09, 0xb5,                           // Usage (Next)
    0x95, 0x01,                           // Report Count (1)
    0x81, 0x06,                           // Input (Data, Variable, Relative)

    0x09, 0xb6,                           // Usage (Previous)
    0x95, 0x01,                           // Report Count (1)
    0x81, 0x06,                           // Input (Data, Variable, Relative)

    0x09, 0xb3,                           // Usage (Fast Forward)
    0x95, 0x01,                           // Report Count (1)
    0x81, 0x06,                           // Input (Data, Variable, Relative)

    0x09, 0xb4,                           // Usage (Rewind)
    0x95, 0x01,                           // Report Count (1)
    0x81, 0x06,                           // Input (Data, Variable, Relative)

    0x95, 0x06,                           // Report Count (6) Number of bits remaining in byte
    0x81, 0x07,                           // Input (Constant, Variable, Relative)
    0xc0                                  // End Collection
}; // Table for USB HID "Consumer Control" (for audio volume control, etc.)



bool ppFirstTime = true, muteHeld = false;

//To clear up the Profile and Volume display
uint16_t contVolume = 0, timeVolume = 5000;
uint16_t contProfile = 0, timeProfile = 10000;



// -- To easily print text! -----------------------------------

void printText(char* text, int16_t x, int16_t y, uint8_t size, bool clear = false) {
  
  if (clear){
    display.clearDisplay();
  }
  display.setCursor(x,y);
  display.setTextSize(size);
  display.print(text);
  display.display();

};

/*void printTopLine(String textLeft = "", String textRight = "", bool clear = false) {
  
  if (clear){
    display.clearDisplay();
  }

  display.setTextSize(1);

  display.setCursor(0, 0);
  display.print(textLeft);

  display.setCursor(1 + (21 - textRight.length()) * 6, 0);
  display.print(textRight);

  display.display();

};*/

// ------------------------------------------------------------

// -- Handle Media Keys ---------------------------------------

void mediaKeyPress(uint8_t key){
  data[0] = key;
  data[1] = 0;
  HID().SendReport(kHID_ReportID_ConsumerControl, data, 2);
}

void mediaKeyRelease(){
  data[0] = KEY_MEDIA_CLEAR;
  data[1] = 0;
  HID().SendReport(kHID_ReportID_ConsumerControl, data, 2);
}


// ------------------------------------------------------------

// -- Handle different functions ------------------------------
void PrintProfile(){

  display.clearDisplay();
  display.setTextSize(1);

  display.setCursor(0,0);
  display.print("PROF:");
  display.setCursor(35,0);
  display.print(profiles.getName());

  uint8_t ppX, ppY;
  char* ppKeyName;

  for (uint8_t n=1; n<NUM_BTN; n++){
    ppX = (n <= 4) ? (32*(n-1))+3 : (32*(n-5))+3;
    ppY = (n <= 4) ? 10 : 22;
    ppKeyName = profiles.currentKeys[n].name;

    /*if (ppKeyName == "PTRK"){
      display.drawFastVLine(ppX+4,ppY,8,WHITE);
      display.drawTriangle(ppX+4,ppY+4,ppX+12,ppY,ppX+12,ppY+8,WHITE);
    }
    else if (ppKeyName == "PLAY"){
      display.drawTriangle(ppX+2,ppY,ppX+2,ppY+10,ppX+6,ppY+4,WHITE);
      display.drawFastVLine(ppX+6,ppY,8,WHITE);
      display.drawFastVLine(ppX+8,ppY,8,WHITE);
    }
    else if (ppKeyName == "NTRK"){
      display.drawTriangle(ppX+4,ppY,ppX+4,ppY+8,ppX+12,ppY+4,WHITE);
      display.drawFastVLine(ppX+10,ppY,8,WHITE);
    }
    else {*/
      display.setCursor(ppX,ppY);
      display.print(ppKeyName);
    //}
  }

  display.display();
}


void HandleVolume(){
  
  if(volume.changed()){
    char* text;

    if (volume.increased()){
      text = "VOL +";
      mediaKeyPress(KEY_VOLUME_UP);
      delay(100);
      mediaKeyRelease();
    }
    else {
      text = "VOL -";
      mediaKeyPress(KEY_VOLUME_DOWN);
      delay(100);
      mediaKeyRelease();
    }
    printText(text, 97, 0, 1);

    contVolume = 1;
  }
 
  if (contVolume > 0){
    contVolume ++;
  }
  if(contVolume > timeVolume){
    display.setTextColor(BLACK);
    printText("VOL +", 97, 0, 1);
    display.setTextColor(WHITE);
    contVolume = 0;
  }

}


void HandleSimon(){


}


// ------------------------------------------------------------



// the setup function runs once when you press reset or power the board
void setup() {

  //Serial.begin(9600);

  // Start Wire library for I2C 
  Wire.begin();
  
  // initialize OLED with I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);


  //Setup the buttons, encoder and profile
  buttons.begin();
  profiles.begin();
  volume.begin(ENCODER2,50,100); //We don't use the encoder number, only increased/decreased

  // Keyboar and Medias Setup
  Keyboard.begin();
  static HIDSubDescriptor node(HID_ReportDescriptor_ConsumerControl, sizeof(HID_ReportDescriptor_ConsumerControl));
  HID().AppendDescriptor(&node);


  // Clear the display
  display.clearDisplay();
  //Set the color - always use white despite actual display color
  display.setTextColor(WHITE);

  //Set the cursor coordinates
  printText("WELCOME!!", 10, 10, 2);
  
  delay(2000);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextWrap(false);
  display.display();

}


// the loop function runs over and over again forever
void loop() {

  //Update objects!
  buttons.update();
  profiles.update();
  volume.update();


  //Handle Profile
  if (profiles.changed() || ppFirstTime || buttons.held(BUTTON_1, 25)){
    PrintProfile();
    ppFirstTime = false;
    contProfile = 1;
    muteHeld = buttons.held(BUTTON_1, 25) ? true : false;
  }

  //Handle keys
  for (uint8_t n=0; n<NUM_BTN; n++){
    if(buttons.released(n)){
      if (muteHeld) {
        muteHeld = false;
      }
      else{
        display.clearDisplay();
        printText(profiles.currentKeys[n].name, 40, 10, 2);
        contProfile = 1;
      
        //Executes key combination
        if (profiles.currentKeys[n].isMedia) { 
          //If it's a media key uses the SendReport function
          mediaKeyPress(profiles.currentKeys[n].key1);
          delay(100);
          mediaKeyRelease();
        }
        else {
          //For the rest we use the Keyboard library
          Keyboard.press(profiles.currentKeys[n].key1);
          if (profiles.currentKeys[n].key2 != 0){
            Keyboard.press(profiles.currentKeys[n].key2);
          }
          if (profiles.currentKeys[n].key3 != 0){
            Keyboard.press(profiles.currentKeys[n].key3);
          }
          delay(100);
          Keyboard.releaseAll();
        }
      }      
    }
  }


  //Clears screen after a few seconds
  if (contProfile > 0){
    contProfile ++;
  }
  if(contProfile > timeProfile){
    display.clearDisplay();
    display.display();
    contProfile = 0;
  }


  //Handle Volume
  HandleVolume();


  //Handle SIMON!!!
  /*if (profiles.getName() == PROFILE_SIMON){
    HandleSimon();
  }*/


}


