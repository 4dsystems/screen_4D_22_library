// Core library - MCU-based
#if defined(ARDUINO) && (ARDUINO >= 100)
#include "Arduino.h" // for Arduino 1.0
#else
#include "WProgram.h" // for Arduino 23
#endif

// Include application, user and local libraries
#include "SPI.h"
#include "TFT_22_ILI9225.h"

#define TFT_RST 8
#define TFT_RS  9
#define TFT_CS  10  // SS
#define TFT_SDI 11  // MOSI
#define TFT_CLK 13  // SCK
#define TFT_LED 3

// Use hardware SPI (faster - on Uno: 13-SCK, 12-MISO, 11-MOSI)
TFT_22_ILI9225 tft = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_LED);
// Use software SPI (slower)
//TFT_22_ILI9225 tft = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_SDI, TFT_CLK, TFT_LED);

// Variables and constants
uint16_t x, y;
boolean flag = false;

// Setup
void setup() {
  tft.begin();
}

// Loop
void loop() {
  tft.rectangle(0, 0, tft.maxX() - 1, tft.maxY() - 1, COLOR_WHITE);
  tft.text(10, 10, "hello!");
  delay(1000);
  
  tft.clear();
  tft.text(10, 20, "clear");
  delay(1000);

  tft.text(10, 30, "text small");
  tft.text(90, 30, "BIG", COLOR_RED, COLOR_YELLOW, 3, 2);
  delay(1000);

  tft.text(10, 40, "setBacklight off");
  delay(500);
  tft.setBacklight(LOW);
  delay(500);
  tft.setBacklight(HIGH);
  tft.text(10, 50, "setBacklight on");
  delay(1000);

  tft.rectangle(10, 10, 110, 110, COLOR_BLUE);
  tft.text(10, 60, "rectangle");
  delay(1000);

  tft.solidRectangle(20, 20, 120, 120, COLOR_RED);
  tft.text(10, 70, "solidRectangle");
  delay(1000);

  tft.circle(80, 80, 50, COLOR_YELLOW);
  tft.text(10, 80, "circle");
  delay(1000);

  tft.solidCircle(90, 90, 30, COLOR_GREEN);
  tft.text(10, 90, "solidCircle");
  delay(1000);

  tft.line(0, 0, tft.maxX() - 1, tft.maxY() - 1, COLOR_CYAN);
  tft.text(10, 100, "line");
  delay(1000);

  for (uint8_t i = 0; i < 127; i++)
    tft.point(random(tft.maxX()), random(tft.maxY()), random(0xffff));
  tft.text(10, 110, "point");
  delay(1000);

  for (uint8_t i = 0; i < 4; i++) {
    tft.clear();
    tft.setOrientation(i);
    tft.rectangle(0, 0, tft.maxX() - 1, tft.maxY() - 1, COLOR_WHITE);
    tft.text(10, 10, "setOrientation (" + String("0123").substring(i, i + 1) + ")");
    tft.rectangle(10, 20, 50, 60, COLOR_GREEN);
    tft.circle(70, 80, 10, COLOR_BLUE);
    tft.line(30, 40, 70, 80, COLOR_YELLOW);
    delay(1000);
  }
  
  for (uint8_t i = 0; i < 4; i++) {
    tft.clear();
    tft.setOrientation(i);
    tft.rectangle(0, 0, tft.maxX() - 1, tft.maxY() - 1, COLOR_WHITE);
    tft.text(30, 10, "setOrientation (" + String("0123").substring(i, i + 1) + ")", COLOR_WHITE);
    tft.text(30, 20, "getTouch", COLOR_RED);
    tft.text(30, 30, "touch red box to stop", COLOR_WHITE);
    tft.solidRectangle(3, 3, 20, 20, COLOR_RED);
    flag = false;
    
    do {
      tft.rectangle(x, y, x + 1, y + 1, COLOR_RED);
      flag = true;
    } while ( (y > 20) || (x > 20) || (flag==false) );
    tft.solidRectangle(3, 3, 20, 20, COLOR_YELLOW);
    tft.text(30, 40, "touch stopped", COLOR_YELLOW);
    delay(1000);
  }
  
  tft.setOrientation(0);
  tft.clear();
  tft.text(10, 40, "bye!", COLOR_RED, COLOR_YELLOW, 3, 3);
  delay(1000);
  
  tft.text(10, 60, "off");
  delay(1000);
  
  tft.setBacklight(false);
  tft.setDisplay(false);
  
  while(true);
}
