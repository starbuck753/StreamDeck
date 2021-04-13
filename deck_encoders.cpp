#include "deck_encoders.h"


void Encoders::begin(){

  pinMode(ENCODER1_PIN_L, INPUT);
  pinMode(ENCODER1_PIN_R, INPUT);

}


void Encoders::update(){

  int8_t LeftValue, RightValue;


  LeftValue = digitalRead(ENCODER1_PIN_L);
  RightValue = digitalRead(ENCODER1_PIN_R);


  // Moved Left (decrease counter)


  //Moved Right (increased counter)




  LastLeftValue = LeftValue;
  LastRightValue = RightValue;

}