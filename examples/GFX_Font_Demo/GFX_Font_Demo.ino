// Include application, user and local libraries
#include "SPI.h"
#include "TFT_22_ILI9225.h"

// Include font definition files
// NOTE: These files may not have all characters defined! Check the GFXfont def
// params 3 + 4, e.g. 0x20 = 32 = space to 0x7E = 126 = ~

#include <../fonts/FreeSans12pt7b.h>
#include <../fonts/FreeSans24pt7b.h>

#define TFT_RST 8
#define TFT_RS  9
#define TFT_CS  10  // SS
#define TFT_SDI 11  // MOSI
#define TFT_CLK 13  // SCK
#define TFT_LED 3   // 0 if wired to +5V directly

#define TFT_BRIGHTNESS 200 // Initial brightness of TFT backlight (optional)

// Use hardware SPI (faster - on Uno: 13-SCK, 12-MISO, 11-MOSI)
TFT_22_ILI9225 tft = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_LED, TFT_BRIGHTNESS);
// Use software SPI (slower)
//TFT_22_ILI9225 tft = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_SDI, TFT_CLK, TFT_LED, TFT_BRIGHTNESS);

// Variables and constants
int16_t x=0, y=0, w, h;

// Setup
void setup() {
  tft.begin();
  tft.clear();

  // Draw first string in big font
  String s1 = "6789";
  tft.setGFXFont(&FreeSans24pt7b); // Set current font
  tft.getGFXTextExtent(s1, x, y, &w, &h); // Get string extents
  y = h; // Set y position to string height
  tft.drawGFXText(x, y, s1, COLOR_RED); // Print string

  // Draw second string in smaller font
  tft.setGFXFont(&FreeSans12pt7b);  // Change font
  String s2 = "Hello"; // Create string object
  tft.getGFXTextExtent(s2, x, y, &w, &h); // Get string extents
  y += h + 10; // Set y position to string height plus shift down 10 pixels
  tft.drawGFXText(x, y, s2, COLOR_BLUE); // Print string
  
  // Draw third string in same font
  String s3 = "World!"; // Create string object
  y += h + 2; // Set y position to previous string height plus shift down 2 pixels
  tft.drawGFXText(x, y, s3, COLOR_GREEN); // Print string
}

// Loop
void loop() {
}