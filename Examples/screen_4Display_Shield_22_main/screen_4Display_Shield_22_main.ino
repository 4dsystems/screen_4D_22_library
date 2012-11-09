///
/// @file	screen_4Display_Shield_22_main.ino
/// @brief	Main sketch
/// @details	Demonstration for 4Display-Shield-22 2.2" screen
/// 
/// @author	4D Systems
/// @author	http://4dsystems.com.au
/// @date	Oct 30, 2012
/// @version	2.02
///
/// @copyright	(c) 4D Systems, 2012
///


// Core library - MCU-based
#if defined(ARDUINO) && (ARDUINO >= 100)
#include "Arduino.h" // for Arduino 1.0
#else
#include "WProgram.h" // for Arduino 23
#endif

// Include application, user and local libraries
#include "SPI.h"
#include "screen_4D_22_library.h"

// Variables and constants
screen22 myScreen(_4DSHIELD22);
uint16_t x, y;
boolean flag = false;

// Setup
void setup() {
  myScreen.begin();
}

// Loop
void loop() {
  myScreen.rectangle(0, 0, myScreen.maxX()-1, myScreen.maxY()-1, whiteColour);
  myScreen.text(10, 10, "hello!");
  delay(1000);
  
  myScreen.clear();
  myScreen.text(10, 20, "clear");
  delay(1000);

  myScreen.text(10, 30, "text small");
  myScreen.text(90, 30, "BIG", redColour, yellowColour, 3, 2);
  delay(1000);

  myScreen.text(10, 40, "setBacklight off");
  delay(500);
  myScreen.setBacklight(LOW);
  delay(500);
  myScreen.setBacklight(HIGH);
  myScreen.text(10, 50, "setBacklight on");
  delay(1000);

  myScreen.rectangle(10, 10, 110, 110, blueColour);
  myScreen.text(10, 60, "rectangle");
  delay(1000);

  myScreen.solidRectangle(20, 20, 120, 120, redColour);
  myScreen.text(10, 70, "solidRectangle");
  delay(1000);

  myScreen.circle(80, 80, 50, yellowColour);
  myScreen.text(10, 80, "circle");
  delay(1000);

  myScreen.solidCircle(90, 90, 30, greenColour);
  myScreen.text(10, 90, "solidCircle");
  delay(1000);

  myScreen.line(0, 0, myScreen.maxX()-1, myScreen.maxY()-1, cyanColour);
  myScreen.text(10, 100, "line");
  delay(1000);

  for (uint8_t i=0; i<127; i++)
    myScreen.point(random(myScreen.maxX()), random(myScreen.maxY()), random(0xffff));
  myScreen.text(10, 110, "point");
  delay(1000);

  for (uint8_t i=0; i<4; i++) {
    myScreen.clear();
    myScreen.setOrientation(i);
    myScreen.rectangle(0, 0, myScreen.maxX()-1, myScreen.maxY()-1, whiteColour);
    myScreen.text(10, 10, "setOrientation (" + String("0123").substring(i, i+1) + ")");
    myScreen.rectangle(10, 20, 50, 60, greenColour);
    myScreen.circle(70, 80, 10, blueColour);
    myScreen.line(30, 40, 70, 80, yellowColour);
    delay(1000);
  }
  
  for (uint8_t i=0; i<4; i++) {
    myScreen.clear();
    myScreen.setOrientation(i);
    myScreen.rectangle(0, 0, myScreen.maxX()-1, myScreen.maxY()-1, whiteColour);
    myScreen.text(30, 10, "setOrientation (" + String("0123").substring(i, i+1) + ")", whiteColour);
    myScreen.text(30, 20, "getTouch", redColour);
    myScreen.text(30, 30, "touch red box to stop", whiteColour);
    myScreen.solidRectangle(3, 3, 20, 20, redColour);
    flag = false;
    
    do {
      if (myScreen.getTouch(x, y)) {
        myScreen.rectangle(x, y, x+1, y+1, redColour);
        flag = true;
      }
    } while ( (y>20) || (x>20) || (flag==false) );
    myScreen.solidRectangle(3, 3, 20, 20, yellowColour);
    myScreen.text(30, 40, "touch stopped", yellowColour);
    delay(1000);
  }
  
  myScreen.setOrientation(0);
  myScreen.clear();
  myScreen.text(10, 40, "bye!", redColour, yellowColour, 3, 3);
  delay(1000);
  
  myScreen.text(10, 60, "off");
  delay(1000);
  
  myScreen.setBacklight(false);
  myScreen.setDisplay(false);
  
  while(true);
}

