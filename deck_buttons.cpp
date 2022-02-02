#include "deck_buttons.h"

void Buttons::begin() {
    
    for (uint8_t thisButton = 0; thisButton < NUM_BTN; thisButton++) {
        pinMode(pins[thisButton], INPUT_PULLUP);
        states[thisButton] = 0;
    }

	timePerFrame = 40;
}

void Buttons::update() {

    for (uint8_t i = 0; i < NUM_BTN; i++) {
        pinMode(pins[i], INPUT_PULLUP);

        if (digitalRead(pins[i]) == LOW) { //if button pressed
            if (millis() % timePerFrame == 1) { //if time to render a new frame is reached and the frame end has ran once
                states[i]++; //increase button hold time
            }
        } else {
            if (states[i] == 0)//button idle
                continue;
            if (states[i] == 0xFF)//if previously released
                states[i] = 0; //set to idle
            else
                states[i] = 0xFF; //button just released
        }
    }
        
}


/*
 * Returns true when 'button' is pressed.
 * The button has to be released for it to be triggered again.
 */
boolean Buttons::pressed(uint8_t button) {
    if (states[button] == 1)
        return true;
    else
        return false;
}

/*
 * return true if 'button' is released
 */
boolean Buttons::released(uint8_t button) {
    if (states[button] == 0xFF)
        return true;
    else
        return false;
}

/**
 * returns true ONCE when 'button' is held for 'time' frames
 * @param button The button's ID
 * @param time How much frames button must be held, between 1 and 254.
 * @return true when 'button' is held for 'time' frames
 */
boolean Buttons::held(uint8_t button, uint16_t time){
    if(states[button] == (time+1))
        return true;
    else
        return false;
}

/**
 * returns true every 'period' frames when 'button' is held
 * @param button The button's ID
 * @param period How much frames button must be held, between 1 and 254.
 * @return true if the button is held for the given time
 */
boolean Buttons::repeat(uint8_t button, uint16_t period) {
    if (period == 0) {
        if ((states[button] != 0xFF) && (states[button]))
            return true;
    } else {
        if ((states[button] != 0xFF) && ((states[button] % period) == 1))
            return true;
    }
    return false;
}

/**
 * 
 * @param button The button's ID
 * @return The number of frames during which the button has been held.
 */
uint8_t Buttons::timeHeld(uint8_t button){
    if(states[button] != 0xFF)
        return states[button];
    else
        return 0;
    
}
