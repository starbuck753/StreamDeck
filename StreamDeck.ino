#include <Arduino.h>

//Include Buttons and Profiles
#include "deck_buttons.h"
#include "deck_profiles.h"
#include "deck_encoders.h"


// Include Wire Library for I2C
#include <Wire.h>

// Include Adafruit Graphics & OLED libraries
//#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Include Keyboard library
#include <Keyboard.h>



// Reset pin not used but needed for library
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);


Buttons buttons;
Profiles profiles;

Encoders volumen;


bool cstate = false;
bool pstate = false;


uint32_t lastVolume;




// the setup function runs once when you press reset or power the board
void setup() {

  // Start Wire library for I2C
  Wire.begin();
  // initialize OLED with I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);


  //Setup the buttons, encoder and profile
  buttons.begin();
  profiles.begin();
  volumen.begin(ENCODER2,50); //We don't use the encoder number, only increased/decreased


  //Keyboard.begin();

 
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);


  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);


  // Clear the display
  display.clearDisplay();
  //Set the color - always use white despite actual display color
  display.setTextColor(WHITE);
  //Set the font size
  display.setTextSize(1);


  //Set the cursor coordinates
  display.setCursor(10,10);
  display.setTextSize(2);
  display.print("WELCOME!!");
  display.display();



  delay(1500);

  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);


  display.clearDisplay();
  display.setTextSize(1);
  display.display();

}

// the loop function runs over and over again forever
void loop() {

  //Update objects!
  buttons.update();
  profiles.update();
  volumen.update();


  //Handle Profile
  if (profiles.changed()){
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("PROF: " + profiles.getName());
    display.display();

    if (profiles.encoder.increased()){
      digitalWrite(11,HIGH);
      digitalWrite(12,LOW);
    }
    else{
      digitalWrite(12,HIGH);
      digitalWrite(11,LOW);
    }
  }


  //Handle keys -- this is just some test!!
  digitalWrite(6, buttons.repeat(BUTTON_1));
  digitalWrite(7, buttons.repeat(BUTTON_2));
  digitalWrite(8, buttons.repeat(BUTTON_3));

  pstate = cstate;

  if (buttons.states[BUTTON_1] == 1)
    cstate = true;
  else
    cstate = false;
  



  //Handle Volume
  HandleVolume();


  //Handle SIMON!!!
  if (profiles.getName() == PROFILE_SIMON){
    HandleSimon();
  }


}


void HandleVolume(){

  if(volumen.changed()){
    display.setCursor(0,100);
    if(volumen.increased()){
      display.print("VOL +");
    }
    else{
      display.print("VOL -");
    }
    display.display();
    lastVolume = millis();
  }
  
  if(millis()-lastVolume >= 200){
    display.setCursor(0,100);
    display.print("     ");
    display.display();
  }

}


void HandleSimon(){



}