#include <Arduino.h>

//#include <Keyboard.h>

//Include Buttons and Profiles
#include "deck_buttons.h"
#include "deck_profiles.h"


// Include Wire Library for I2C
#include <Wire.h>

// Include Adafruit Graphics & OLED libraries
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


// Reset pin not used but needed for library
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);


Buttons buttons;
Profiles profiles;

bool cstate = false;
bool pstate = false;

int8_t cont = 0, prevcont = 0, encoderstate = 0;
int16_t left = 0, right = 0, prevleft = 0, prevright = 0;


// the setup function runs once when you press reset or power the board
void setup() {

  // Start Wire library for I2C
  Wire.begin();
  // initialize OLED with I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);


  //Setup the buttons and profile
  buttons.begin();
  //profiles.setProfile(PROFILE1);

  //Keyboard.begin();

  pinMode(ENCODER1_PIN_L, INPUT);
  pinMode(ENCODER1_PIN_R, INPUT);
 
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);


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

  //Check on buttons
  buttons.update();
  

  digitalWrite(6, buttons.repeat(BUTTON_1));
  digitalWrite(7, buttons.repeat(BUTTON_2));
  digitalWrite(8, buttons.repeat(BUTTON_3));

  //digitalWrite(8, buttons.pressed(BUTTON_1));
  //digitalWrite(8, buttons.pressed(BUTTON_2));



  pstate = cstate;

  if (buttons.states[BUTTON_1] == 1)
    cstate = true;
  else
    cstate = false;
  

  /*if (cstate != pstate){
    digitalWrite(8, cstate);
    display.setCursor(0,10);
    display.print(cstate);
    display.display();
  }*/


  //Encoder Test!
  left = digitalRead(ENCODER1_PIN_L);
  right = digitalRead(ENCODER1_PIN_R);

  //Encoder was activated and got to the middle point
  if (left && right) {
    //Check the different combinations (we look at the previous vale to know to which side it turned)
    if (prevleft && !prevright) {   //It turned left
      cont++;
    }
    else if (!prevleft && prevright) {   //It turned right
      cont--;
    }

    encoderstate = true;

  }
  //Encoder got back to iddle state
  else if (!(left || right) && encoderstate) {
    encoderstate = false;
  }

  prevleft = left, prevright = right;

  if (cont != prevcont){
    display.clearDisplay();
    display.setCursor(10,20);
    display.print(cont);
    display.display();
  }

  prevcont = cont;
  

  //Set the cursor coordinates
  /*display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,10);
  display.print("1:");
  display.setCursor(20,10);
  display.print(buttons.states[0]);

  display.setCursor(0,20);
  display.print("2:");
  display.setCursor(20,20);
  display.print(buttons.states[1]);

  display.display();*/


}


