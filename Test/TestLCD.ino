#include <Arduino.h>


// Include Wire Library for I2C
#include <Wire.h>

// Include Adafruit Graphics & OLED libraries
#include <Adafruit_SSD1306.h>


// Reset pin not used but needed for library
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);


// -- COMMON FUNCTIONS ---------------------------------------- //

// -- To easily print text! ----------------------------------- //

void printText(String text, int16_t x, int16_t y, uint8_t size, bool clear = false) {
  
  if (clear){
    display.clearDisplay();
  }
  display.setCursor(x,y);
  display.setTextSize(size);
  display.print(text);
  display.display();

};

// ------------------------------------------------------------ //



// the setup function runs once when you press reset or power the board
void setup() {

  // Start Wire library for I2C 
  Wire.begin();
  
  // initialize OLED with I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);


  // Clear the display
  display.clearDisplay();
  //Set the color - always use white despite actual display color
  display.setTextColor(WHITE);
  
  display.setCursor(10,10);
  display.setTextSize(2);


  //Wellcome message and setup display
  printText("WELCOME!!", 10, 10, 2);

  delay(2000);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextWrap(false);
  display.display();

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

}


// the loop function runs over and over again forever
void loop() {

  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  delay(1000);

  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  delay(1000);

}