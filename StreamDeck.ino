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
bool turnleft = false, turnright = false;


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

  pinMode(ENCODER1_PIN_L, INPUT_PULLUP);
  pinMode(ENCODER1_PIN_R, INPUT_PULLUP);
 
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

  left = digitalRead(ENCODER1_PIN_L);
  right = digitalRead(ENCODER1_PIN_R);
  prevleft = left;
  prevright = right;

}

// the loop function runs over and over again forever
void loop() {

  //Check on buttons
  buttons.update();
  

  digitalWrite(6, buttons.repeat(BUTTON_1));
  digitalWrite(7, buttons.repeat(BUTTON_2));
  digitalWrite(8, buttons.repeat(BUTTON_3));

  pstate = cstate;

  if (buttons.states[BUTTON_1] == 1)
    cstate = true;
  else
    cstate = false;
  


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
  

  if (cont != prevcont){
    display.clearDisplay();
    display.setCursor(10,20);
    display.print(cont);
    display.display();

    if (cont > prevcont){
      digitalWrite(11,HIGH);
      digitalWrite(12,LOW);
    }
    else{
      digitalWrite(12,HIGH);
      digitalWrite(11,LOW);
    }
  }

  prevcont = cont, prevright = right, prevleft = left;

}


