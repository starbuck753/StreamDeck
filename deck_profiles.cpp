#include "deck_profiles.h"


void Profiles::begin(){
  
  //Set up the encoder we use for the profiles
  encoder.begin(ENCODERPROFILE, 0, MAXPROFILE);

  setCurrent(encoder.getCurrent());

}

void Profiles::update(){
  
  //Update the encoder
  encoder.update();

  hasChanged = encoder.changed();

  //When encoder updates, we need to set the new set of keys for the profile
  if (hasChanged){
    setCurrent(encoder.getCurrent());
  
  }

}

bool Profiles::changed(){
  return hasChanged;
}

uint8_t Profiles::getId(){
  return id;
}
String Profiles::getName(){
  return ProfileNameList[id];
}


void Profiles::setCurrent(uint8_t current){

  id = current;

  for (uint8_t n=0; n<NUM_BTN; n++){
    currentKeys[n] = DailyKeys[n];
  }

}