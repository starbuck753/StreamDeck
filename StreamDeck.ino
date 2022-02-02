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
//#include <Keyboard.h>


// Reset pin not used but needed for library
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);


Buttons buttons;
Profiles profiles;
Encoders volume;


bool ppFirstTime = true, muteHeld = false;

//To clear up the Profile and Volume display
uint16_t contVolume = 0, timeVolume = 5000;
uint16_t contProfile = 0, timeProfile = 10000;



// -- To easily print text! -----------------------------------

void printText(String text, int16_t x, int16_t y, uint8_t size, bool clear = false) {
  
  if (clear){
    display.clearDisplay();
  }
  display.setCursor(x,y);
  display.setTextSize(size);
  display.print(text);
  display.display();

};

void printTopLine(String textLeft = "", String textRight = "", bool clear = false) {
  
  if (clear){
    display.clearDisplay();
  }

  display.setTextSize(1);

  display.setCursor(0, 0);
  display.print(textLeft);

  display.setCursor(1 + (21 - textRight.length()) * 6, 0);
  display.print(textRight);

  display.display();

};

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
  String ppKeyName;

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
    String text = (volume.increased()) ? "VOL +" : "VOL -";
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

  // Start Wire library for I2C 
  Wire.begin();
  
  // initialize OLED with I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);


  //Setup the buttons, encoder and profile
  buttons.begin();
  profiles.begin();
  volume.begin(ENCODER2,50,100); //We don't use the encoder number, only increased/decreased

  
  //Keyboard.begin();


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


