///
/// @mainpage 	Library for 4D Systems 4DLCDM-22 and 4Display-Shield-22 2.2" screens
/// @details	screen_4D_22_library is a library for the 4DLCDM-22 and 4Display-Shield-22 2.2" screens from 4D Systems
/// 
/// @b Usage
///
/// On the main sketch, define the variable
/// *	for the 4Display-Shield-22
/// @code{cpp}
///		screen22 myScreen(_4DSHIELD22);
/// @endcode
/// *	for the 4DLCDM-22
/// @code{cpp}
///		screen22 myScreen(_4DLCDM22); 
/// @endcode
///
///
/// @author	4D Systems
/// @author	http://4dsystems.com.au
/// @date	Oct 30, 2012
/// @version	2.02
///
/// @copyright	(c) 4D Systems, 2012
///


///
/// @file 	screen_4D_22_library.h 
/// @brief	Main sketch
/// @details	Library for 4DLCDM-22 and 4Display-Shield-22 2.2" screens
///
/// @author	4D Systems
/// @author	http://4dsystems.com.au
/// @date	Oct 30, 2012
/// @version	2.02
///
/// @copyright	(c) 4D Systems, 2012
///

///
/// @brief	Library release number
///
#define screen22_RELEASE 201

#ifndef screen_4DisplayShield22_library_h
#define screen_4DisplayShield22_library_h

// Core library - MCU-based
#if (ARDUINO >= 100)
#include "Arduino.h" // for Arduino 1.0
#else
#include "WProgram.h" // for Arduino 23
#endif

// Other libraries
#include "SPI.h"

///
/// @brief	Supported screens
///
enum _4Dscreen22 {
	_4DSHIELD22,   ///<	4D Systems 4Display-Shield-22
	_4DLCDM22      ///<	4D Systems 4DLCDM-22
};

///
/// @name	Arduino Pins for  4Display-Shield-22
///
/// @{
#define _4DSHIELD22_LCD_RESET A0     // Arduino Pin A0
#define _4DSHIELD22_LCD_RS 8         // Arduino Pin 8 - data or command
#define _4DSHIELD22_LCD_CS 7         // Arduino Pin 7 - select
#define _4DSHIELD22_LCD_Backlight 9  // Arduino Pin 9

#define _4DSHIELD22_TOUCH_YU A3  // Arduino Pin A3 - analog
#define _4DSHIELD22_TOUCH_XR A4  // Arduino Pin A4 - analog
#define _4DSHIELD22_TOUCH_YD A1  // Arduino Pin A1 - analog or digital
#define _4DSHIELD22_TOUCH_XL A2  // Arduino Pin A2 - analog or digital

/// @}

///
/// @name	Arduino Pins for 4DLCDM-22
///
/// @{
#define _4DLCDM22_LCD_RESET 8     // Arduino Pin 8
#define _4DLCDM22_LCD_RS 5         // Arduino Pin 5 - data or command
#define _4DLCDM22_LCD_CS 6         // Arduino Pin 6 - select
#define _4DLCDM22_LCD_Backlight 9  // Arduino Pin 9

#define _4DLCDM22_TOUCH_YU A0  // Arduino Pin A0 - analog
#define _4DLCDM22_TOUCH_XR A1  // Arduino Pin A1 - analog
#define _4DLCDM22_TOUCH_YD 4  // Arduino Pin 4 - digital
#define _4DLCDM22_TOUCH_XL 3  // Arduino Pin 3 - digital

/// @}

#define ILI9225C_WIDTH  176
#define ILI9225C_HEIGHT 220
#define ILI9225C_PRESSURE  10
#define ILI9225C_XRPLATE   314

#define MADCTL_MY  0x80
#define MADCTL_MX  0x40
#define MADCTL_MV  0x20
#define MADCTL_ML  0x10
#define MADCTL_RGB 0x08
#define MADCTL_MH  0x04
#define ILI9225C_MADCTL  0x36
#define ILI9225C_INVOFF  0x20
#define ILI9225C_INVON   0x21


///
/// @name	Colours constants
// Colours                        Red  Green Blue
//                               4321054321043210
/// @{

const uint16_t blackColour   = 0b0000000000000000; ///<	black
const uint16_t whiteColour   = 0b1111111111111111; ///<	white
const uint16_t redColour     = 0b1111100000000000; ///<	red
const uint16_t greenColour   = 0b0000011111100000; ///<	green
const uint16_t blueColour    = 0b0000000000011111; ///<	blue
const uint16_t yellowColour  = 0b1111111111100000; ///<	yellow
const uint16_t cyanColour    = 0b0000011111111111; ///<	cyan
const uint16_t orangeColour  = 0b1111101111100000; ///<	orange
const uint16_t magentaColour = 0b1111100000001111; ///<	magenta
const uint16_t violetColour  = 0b1111100000011111; ///<	violet
const uint16_t grayColour    = 0b0111101111101111; ///<	gray

/// @}

// Objects
//
///
/// @class	screen22
/// @brief	Main and core class
///
class screen22 {
public:  
	///
	/// @brief	Constructor
	/// @param	screen either _4DSHIELD22 or _4DLCDM22
	/// 
	screen22(_4Dscreen22 screen);

	/// 
	/// @brief	Initialisation
	/// 
	void begin();

	///
	/// @brief	Clear the screen
	/// 
	void clear(); 

	///
	/// @brief	Invert screen
	/// @param	flag true to invert, false for normal screen
	///
	void invert(boolean flag);

	/// 
	/// @brief	Switch backlight on or off
	/// @param	flag true=on, false=off
	///
	void setBacklight(boolean flag); 

	/// 
	/// @brief	Switch display on or off
	/// @param	flag true=on, false=off
	///
	void setDisplay(boolean flag);  

	/// 
	/// @brief	Set orientation
	/// @param	orientation orientation, 0=portrait, 1=right rotated landscape, 2=reverse portrait, 3=left rotated landscape
	///
	void setOrientation(uint8_t orientation);  

	/// 
	/// @brief	Get orientation
	/// @return	orientation orientation, 0=portrait, 1=right rotated landscape, 2=reverse portrait, 3=left rotated landscape
	///
	uint8_t getOrientation(); 

	/// 
	/// @brief	Font size, x-axis
	/// @return	horizontal size of current font, in pixels
	/// 
	uint8_t fontX();

	/// 
	/// @brief	Font size, y-axis
	/// @return	vertical size of current font, in pixels
	/// 
	uint8_t fontY(); 

	/// 
	/// @brief	Screen size, x-axis
	/// @return	horizontal size of the screen, in pixels
	/// @note	240 means 240 pixels and thus 0..239 coordinates (decimal)
	/// 
	uint16_t maxX();

	/// 
	/// @brief	Screen size, y-axis
	/// @return	vertical size of the screen, in pixels
	/// @note	240 means 240 pixels and thus 0..239 coordinates (decimal)
	///
	uint16_t maxY();

	///
	/// @brief	Draw circle
	/// @param	x0 center, point coordinate, x-axis
	/// @param	y0 center, point coordinate, y-axis
	/// @param	radius radius
	/// @param	colour 16-bit colour
	/// 
	void circle(uint16_t x0, uint16_t y0, uint16_t radius, uint16_t colour);  

	///
	/// @brief	Draw solid circle
	/// @param	x0 center, point coordinate, x-axis
	/// @param	y0 center, point coordinate, y-axis
	/// @param	radius radius
	/// @param	colour 16-bit colour
	///
	void solidCircle(uint8_t x0, uint8_t y0, uint8_t radius, uint16_t colour); 

	///
	/// @brief	Set background colour
	/// @param	colour background colour, default=black
	/// 
	void setBackGroundColour(uint16_t colour=blackColour);  

	/// 
	/// @brief	Draw line, rectangle coordinates
	/// @param	x1 top left coordinate, x-axis
	/// @param	y1 top left coordinate, y-axis
	/// @param	x2 bottom right coordinate, x-axis
	/// @param	y2 bottom right coordinate, y-axis
	/// @param	colour 16-bit colour
	///
	void line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t colour); 

	///
	/// @brief	Draw rectangle, rectangle coordinates
	/// @param	x1 top left coordinate, x-axis
	/// @param	y1 top left coordinate, y-axis
	/// @param	x2 bottom right coordinate, x-axis
	/// @param	y2 bottom right coordinate, y-axis
	/// @param	colour 16-bit colour
	///
	void rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t colour); 

	/// 
	/// @brief	Draw solid rectangle, rectangle coordinates
	/// @param	x1 top left coordinate, x-axis
	/// @param	y1 top left coordinate, y-axis
	/// @param	x2 bottom right coordinate, x-axis
	/// @param	y2 bottom right coordinate, y-axis
	/// @param	colour 16-bit colour
	///
	void solidRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t colour);

	/// 
	/// @brief	Draw pixel
	/// @param	x1 point coordinate, x-axis
	/// @param	y1 point coordinate, y-axis
	/// @param	colour 16-bit colour
	///
	void point(uint16_t x1, uint16_t y1, uint16_t colour);  

	///
	/// @brief	Draw ASCII Text (pixel coordinates)
	/// @param	x0 point coordinate, x-axis
	/// @param	y0 point coordinate, y-axis
	/// @param	s text string
	/// @param	textColour 16-bit colour, default=white
	/// @param	backColour 16-bit colour, default=black
	/// @param	ix x-axis font size multiplier, default=1
	/// @param	iy y-axis font size multiplier, default=1
	///
	void text(uint16_t x0, uint16_t y0, String s, uint16_t textColour=whiteColour, uint16_t backColour=blackColour, uint8_t ix=1, uint8_t iy=1);

	///
	/// @brief	Get touch activity and coordinates
	/// @param	x x-axis coordinate
	/// @param	y y-axis coordinate
	/// @return	true if pressed, false otherwise
	/// @note	x and y coordinates are consitent with the orientation
	/// @code{.cpp}
	/// myScreen.setOrientation(2);
	/// if (myScreen.getTouch(x, y)) {
	///   myScreen.rectangle(x, y, x+1, y+1, redColour);
	/// }
	/// @endcode
	///
	boolean getTouch(uint16_t &x, uint16_t &y);  

	/// 
	/// @brief	Calculate 16-bit colour from 8-bit Red-Green-Blue components
	/// @param	red red component, 0x00..0xff
	/// @param	green green component, 0x00..0xff
	/// @param	blue blue component, 0x00..0xff
	/// @return	16-bit colour
	///
	uint16_t setColour(uint8_t red, uint8_t green, uint8_t blue);

	///
	/// @brief	Calculate 8-bit Red-Green-Blue components from 16-bit colour
	/// @param	rgb 16-bit colour
	/// @param	red red component, 0x00..0xff
	/// @param	green green component, 0x00..0xff
	/// @param	blue blue component, 0x00..0xff
	///
	void splitColour(uint16_t rgb, uint8_t &red, uint8_t &green, uint8_t &blue);


private:
	uint8_t _orientation;
	uint16_t _maxX, _maxY;
	void _swap(uint16_t &a, uint16_t &b);
	void _setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
	void _orientCoordinates(uint16_t &x1, uint16_t &y1);
	void _writeDisplay(uint16_t reg, uint16_t data);
	void _writeData(uint8_t HI, uint8_t LO);
	void _writeCommand(uint8_t HI, uint8_t LO);

	uint8_t LCD_RESET;
	uint8_t LCD_RS;
	uint8_t LCD_CS;
	uint8_t LCD_Backlight;
	uint8_t TOUCH_YU;
	uint8_t TOUCH_XR;
	uint8_t TOUCH_YD;
	uint8_t TOUCH_XL;

};

///
/// @brief	Font 5x8
///
static const uint8_t font5x8[96][5] = {

	0x00, 0x00, 0x00, 0x00, 0x00,      // Code for char
	0x00, 0x06, 0x5F, 0x06, 0x00,      // Code for char !
	0x07, 0x03, 0x00, 0x07, 0x03,      // Code for char "
	0x24, 0x7E, 0x24, 0x7E, 0x24,      // Code for char #
	0x24, 0x2B, 0x6A, 0x12, 0x00,      // Code for char $
	0x63, 0x13, 0x08, 0x64, 0x63,      // Code for char %
	0x36, 0x49, 0x56, 0x20, 0x50,      // Code for char &
	0x00, 0x07, 0x03, 0x00, 0x00,      // Code for char '
	0x00, 0x3E, 0x41, 0x00, 0x00,      // Code for char (
	0x00, 0x41, 0x3E, 0x00, 0x00,      // Code for char )
	0x08, 0x3E, 0x1C, 0x3E, 0x08,      // Code for char *
	0x08, 0x08, 0x3E, 0x08, 0x08,      // Code for char +
	0x00, 0xE0, 0x60, 0x00, 0x00,      // Code for char ,
	0x08, 0x08, 0x08, 0x08, 0x08,      // Code for char -
	0x00, 0x60, 0x60, 0x00, 0x00,      // Code for char .
	0x20, 0x10, 0x08, 0x04, 0x02,      // Code for char /
	0x3E, 0x51, 0x49, 0x45, 0x3E,      // Code for char 0
	0x00, 0x42, 0x7F, 0x40, 0x00,      // Code for char 1
	0x62, 0x51, 0x49, 0x49, 0x46,      // Code for char 2
	0x22, 0x49, 0x49, 0x49, 0x36,      // Code for char 3
	0x18, 0x14, 0x12, 0x7F, 0x10,      // Code for char 4
	0x2F, 0x49, 0x49, 0x49, 0x31,      // Code for char 5
	0x3C, 0x4A, 0x49, 0x49, 0x30,      // Code for char 6
	0x01, 0x71, 0x09, 0x05, 0x03,      // Code for char 7
	0x36, 0x49, 0x49, 0x49, 0x36,      // Code for char 8
	0x06, 0x49, 0x49, 0x29, 0x1E,      // Code for char 9
	0x00, 0x6C, 0x6C, 0x00, 0x00,      // Code for char :
	0x00, 0xEC, 0x6C, 0x00, 0x00,      // Code for char ;
	0x08, 0x14, 0x22, 0x41, 0x00,      // Code for char <
	0x24, 0x24, 0x24, 0x24, 0x24,      // Code for char =
	0x00, 0x41, 0x22, 0x14, 0x08,      // Code for char >
	0x02, 0x01, 0x59, 0x09, 0x06,      // Code for char ?
	0x3E, 0x41, 0x5D, 0x55, 0x1E,      // Code for char @
	0x7E, 0x11, 0x11, 0x11, 0x7E,      // Code for char A
	0x7F, 0x49, 0x49, 0x49, 0x36,      // Code for char B
	0x3E, 0x41, 0x41, 0x41, 0x22,      // Code for char C
	0x7F, 0x41, 0x41, 0x41, 0x3E,      // Code for char D
	0x7F, 0x49, 0x49, 0x49, 0x41,      // Code for char E
	0x7F, 0x09, 0x09, 0x09, 0x01,      // Code for char F
	0x3E, 0x41, 0x49, 0x49, 0x7A,      // Code for char G
	0x7F, 0x08, 0x08, 0x08, 0x7F,      // Code for char H
	0x00, 0x41, 0x7F, 0x41, 0x00,      // Code for char I
	0x30, 0x40, 0x40, 0x40, 0x3F,      // Code for char J
	0x7F, 0x08, 0x14, 0x22, 0x41,      // Code for char K
	0x7F, 0x40, 0x40, 0x40, 0x40,      // Code for char L
	0x7F, 0x02, 0x04, 0x02, 0x7F,      // Code for char M
	0x7F, 0x02, 0x04, 0x08, 0x7F,      // Code for char N
	0x3E, 0x41, 0x41, 0x41, 0x3E,      // Code for char O
	0x7F, 0x09, 0x09, 0x09, 0x06,      // Code for char P
	0x3E, 0x41, 0x51, 0x21, 0x5E,      // Code for char Q
	0x7F, 0x09, 0x09, 0x19, 0x66,      // Code for char R
	0x26, 0x49, 0x49, 0x49, 0x32,      // Code for char S
	0x01, 0x01, 0x7F, 0x01, 0x01,      // Code for char T
	0x3F, 0x40, 0x40, 0x40, 0x3F,      // Code for char U
	0x1F, 0x20, 0x40, 0x20, 0x1F,      // Code for char V
	0x3F, 0x40, 0x3C, 0x40, 0x3F,      // Code for char W
	0x63, 0x14, 0x08, 0x14, 0x63,      // Code for char X
	0x07, 0x08, 0x70, 0x08, 0x07,      // Code for char Y
	0x71, 0x49, 0x45, 0x43, 0x00,      // Code for char Z
	0x00, 0x7F, 0x41, 0x41, 0x00,      // Code for char [
	0x02, 0x04, 0x08, 0x10, 0x20,      // Code for <BackSlash>
	0x00, 0x41, 0x41, 0x7F, 0x00,      // Code for char ]
	0x04, 0x02, 0x01, 0x02, 0x04,      // Code for char ^
	0x80, 0x80, 0x80, 0x80, 0x80,      // Code for char _
	0x00, 0x03, 0x07, 0x00, 0x00,      // Code for char `
	0x20, 0x54, 0x54, 0x54, 0x78,      // Code for char a
	0x7F, 0x44, 0x44, 0x44, 0x38,      // Code for char b
	0x38, 0x44, 0x44, 0x44, 0x28,      // Code for char c
	0x38, 0x44, 0x44, 0x44, 0x7F,      // Code for char d
	0x38, 0x54, 0x54, 0x54, 0x08,      // Code for char e
	0x08, 0x7E, 0x09, 0x09, 0x00,      // Code for char f
	0x18, 0xA4, 0xA4, 0xA4, 0x7C,      // Code for char g
	0x7F, 0x04, 0x04, 0x78, 0x00,      // Code for char h
	0x00, 0x00, 0x7D, 0x40, 0x00,      // Code for char i
	0x40, 0x80, 0x84, 0x7D, 0x00,      // Code for char j
	0x7F, 0x10, 0x28, 0x44, 0x00,      // Code for char k
	0x00, 0x00, 0x7F, 0x40, 0x00,      // Code for char l
	0x7C, 0x04, 0x18, 0x04, 0x78,      // Code for char m
	0x7C, 0x04, 0x04, 0x78, 0x00,      // Code for char n
	0x38, 0x44, 0x44, 0x44, 0x38,      // Code for char o
	0xFC, 0x44, 0x44, 0x44, 0x38,      // Code for char p
	0x38, 0x44, 0x44, 0x44, 0xFC,      // Code for char q
	0x44, 0x78, 0x44, 0x04, 0x08,      // Code for char r
	0x08, 0x54, 0x54, 0x54, 0x20,      // Code for char s
	0x04, 0x3E, 0x44, 0x24, 0x00,      // Code for char t
	0x3C, 0x40, 0x20, 0x7C, 0x00,      // Code for char u
	0x1C, 0x20, 0x40, 0x20, 0x1C,      // Code for char v
	0x3C, 0x60, 0x30, 0x60, 0x3C,      // Code for char w
	0x6C, 0x10, 0x10, 0x6C, 0x00,      // Code for char x
	0x9C, 0xA0, 0x60, 0x3C, 0x00,      // Code for char y
	0x64, 0x54, 0x54, 0x4C, 0x00,      // Code for char z
	0x08, 0x3E, 0x41, 0x41, 0x00,      // Code for char {
	0x00, 0x00, 0x77, 0x00, 0x00,      // Code for char |
	0x00, 0x41, 0x41, 0x3E, 0x08,      // Code for char }
	0x02, 0x01, 0x02, 0x01, 0x00,      // Code for char ~
	0x06, 0x09, 0x09, 0x06, 0x00       // Code for <Degrees>
};

#endif
