#include "deck_encoders.h"


void Encoders::begin(uint8_t encodernumber){

  if (encodernumber == ENCODER1) {
    pinLeft = ENCODER1_PIN_L;
    pinRight = ENCODER1_PIN_R;
  }
  else if(encodernumber == ENCODER2){
    //pinLeft = ENCODER2_PIN_L;
    //pinRight = ENCODER2_PIN_R;
  }

  pinMode(pinLeft, INPUT_PULLUP);
  pinMode(pinRight, INPUT_PULLUP);


  encoder = 1, lastEncoder = 1, encoderState = 0;
  lastLeftValue = 0, lastRightValue = 0;

}


void Encoders::update(){

  int8_t leftValue, rightValue;

  leftValue = digitalRead(pinLeft);
  rightValue = digitalRead(pinRight);


  //Encoder was activated and got to the middle point
  if (leftValue && rightValue) {
    //Check the different combinations (we look at the previous vale to know to which side it turned)
    if (lastLeftValue && !lastRightValue) {   //It turned left
      encoder = (encoder != 1) ? encoder - 1 : MAXENCODER;
    }
    else if (!lastLeftValue && lastRightValue) {   //It turned right
      encoder = (encoder != MAXENCODER) ? encoder + 1 : 1;
    }

    encoderState = true;

  }
  //Encoder got back to iddle state
  else if (!(leftValue || rightValue) && encoderState) {
    encoderState = false;
  }

  
  hasIncreased = (encoder > lastEncoder) ? true : false;
  hasDecreased = (encoder < lastEncoder) ? true : false;

  lastLeftValue = leftValue;
  lastRightValue = rightValue;
  lastEncoder = encoder;
  
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