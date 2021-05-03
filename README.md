# StreamDeck

**This is still a work in progress** 

### Why the Stream Deck?

You have ever seen the [Elgato Stream Deck](https://www.elgato.com/en/stream-deck), then there is no need to explain WHY. 
Unfortunately the Stream Deck is an expensive tech, and that is why we designed our own Custom Deck.

At heart, this is really a custom keyboard and it can be used for many things. It could be used as a hotkey board, to easily mute/unmute the microphone or decrease/increase the volume during meeting. It could also be configured to open and close apps, execute a combination of keys to perform actions, like copy/paste, move between apps, etc.


### Components

These are the main components used in the project:

* 1 Arduino Pro Micro
* 9 Sanwa Arcade Buttons
* 2 Rotative Encoders
* 1 Oled Display 0.96 (128x64)
* 9 Leds
* 9 220ohm Resistors


There are some additional components for future enhacement (which are not currently used):

* 1 Buzzer
* 1 Wi-Fi module
* 1 Real Time Clock module


### Schematics

![StreamDeck Bread Board diagram](/StramDeck_bb.png)



### The Code

Adding the necessary libraries:

* Wire.h
* Adafruit_SSD1306.h
* Keyboard.h

