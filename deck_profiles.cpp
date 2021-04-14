#include "deck_profiles.h"


void Profiles::begin(){
  
  //Set up the encoder we use for the profiles
  encoder.begin(ENCODERPROFILE);

}

void Profiles::update(){
  
  //Update the encoder
  encoder.update();

  isUpdated = encoder.updated();

  //When encoder updates, we need to set the new set of keys for the profile
  if (isUpdated){
    current = encoder.getCurrent();
  
  
  
  
  }

}

bool Profiles::updated(){
  return isUpdated;
}

uint8_t Profiles::getCurrent(){
  return current;
}