#include "deck_encoders.h"


void Encoders::begin(uint8_t encodernumber, uint8_t initialState, uint8_t max){

  if (encodernumber == ENCODER1) {
    pinLeft = ENCODER1_PIN_L;
    pinRight = ENCODER1_PIN_R;
  }
  else {
    pinLeft = ENCODER2_PIN_L;
    pinRight = ENCODER2_PIN_R;
  }

  pinMode(pinLeft, INPUT_PULLUP);
  pinMode(pinRight, INPUT_PULLUP);


  encoder = initialState;
  maxencoder = max-1;
  lastLeftValue = 0, lastRightValue = 0;

}


void Encoders::update(){

  int8_t leftValue, rightValue;

  leftValue = digitalRead(pinLeft);
  rightValue = digitalRead(pinRight);

  hasIncreased = false, hasDecreased = false;
  
  //Encoder was activated and got to the middle point
  if (leftValue && rightValue) {
    //Check the different combinations (we look at the previous vale to know to which side it turned)
    if (lastLeftValue && !lastRightValue) {   //It turned left
      encoder = (encoder != 0) ? encoder - 1 : maxencoder;
      hasDecreased = true;
    }
    else if (!lastLeftValue && lastRightValue) {   //It turned right
      encoder = (encoder != maxencoder) ? encoder + 1 : 0;
      hasIncreased = true;
    }

  }

  lastLeftValue = leftValue;
  lastRightValue = rightValue;
  
}

bool Encoders::changed(){
  return (hasDecreased || hasIncreased);
}

bool Encoders::increased(){
  return hasIncreased;
}
bool Encoders::decreased(){
  return hasDecreased;
}

uint8_t Encoders::getCurrent(){
  return encoder;
}