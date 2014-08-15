#ifndef TFT_22_ILI9225_h
#define TFT_22_ILI9225_h

#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif
#include <avr/pgmspace.h>

// Other libraries
#include "SPI.h"

/* ILI9225 screen size */
#define ILI9225_LCD_WIDTH  176
#define ILI9225_LCD_HEIGHT 220

/* ILI9225 LCD Registers */
#define ILI9225_DRIVER_OUTPUT_CTRL      (0x01u)  // Driver Output Control
#define ILI9225_LCD_AC_DRIVING_CTRL     (0x02u)  // LCD AC Driving Control
#define ILI9225_ENTRY_MODE            	(0x03u)  // Entry Mode
#define ILI9225_DISP_CTRL1          	(0x07u)  // Display Control 1
#define ILI9225_BLANK_PERIOD_CTRL1      (0x08u)  // Blank Period Control
#define ILI9225_FRAME_CYCLE_CTRL        (0x0Bu)  // Frame Cycle Control
#define ILI9225_INTERFACE_CTRL          (0x0Cu)  // Interface Control
#define ILI9225_OSC_CTRL             	(0x0Fu)  // Osc Control
#define ILI9225_POWER_CTRL1            	(0x10u)  // Power Control 1
#define ILI9225_POWER_CTRL2           	(0x11u)  // Power Control 2
#define ILI9225_POWER_CTRL3            	(0x12u)  // Power Control 3
#define ILI9225_POWER_CTRL4            	(0x13u)  // Power Control 4
#define ILI9225_POWER_CTRL5            	(0x14u)  // Power Control 5
#define ILI9225_VCI_RECYCLING          	(0x15u)  // VCI Recycling
#define ILI9225_RAM_ADDR_SET1           (0x20u)  // Horizontal GRAM Address Set
#define ILI9225_RAM_ADDR_SET2           (0x21u)  // Vertical GRAM Address Set
#define ILI9225_GRAM_DATA_REG           (0x22u)  // GRAM Data Register
#define ILI9225_GATE_SCAN_CTRL          (0x30u)  // Gate Scan Control Register
#define ILI9225_VERTICAL_SCROLL_CTRL1   (0x31u)  // Vertical Scroll Control 1 Register
#define ILI9225_VERTICAL_SCROLL_CTRL2   (0x32u)  // Vertical Scroll Control 2 Register
#define ILI9225_VERTICAL_SCROLL_CTRL3   (0x33u)  // Vertical Scroll Control 3 Register
#define ILI9225_PARTIAL_DRIVING_POS1    (0x34u)  // Partial Driving Position 1 Register
#define ILI9225_PARTIAL_DRIVING_POS2    (0x35u)  // Partial Driving Position 2 Register
#define ILI9225_HORIZONTAL_WINDOW_ADDR1 (0x36u)  // Horizontal Address Start Position
#define ILI9225_HORIZONTAL_WINDOW_ADDR2	(0x37u)  // Horizontal Address End Position
#define ILI9225_VERTICAL_WINDOW_ADDR1   (0x38u)  // Vertical Address Start Position
#define ILI9225_VERTICAL_WINDOW_ADDR2   (0x39u)  // Vertical Address End Position
#define ILI9225_GAMMA_CTRL1            	(0x50u)  // Gamma Control 1
#define ILI9225_GAMMA_CTRL2             (0x51u)  // Gamma Control 2
#define ILI9225_GAMMA_CTRL3            	(0x52u)  // Gamma Control 3
#define ILI9225_GAMMA_CTRL4            	(0x53u)  // Gamma Control 4
#define ILI9225_GAMMA_CTRL5            	(0x54u)  // Gamma Control 5
#define ILI9225_GAMMA_CTRL6            	(0x55u)  // Gamma Control 6
#define ILI9225_GAMMA_CTRL7            	(0x56u)  // Gamma Control 7
#define ILI9225_GAMMA_CTRL8            	(0x57u)  // Gamma Control 8
#define ILI9225_GAMMA_CTRL9             (0x58u)  // Gamma Control 9
#define ILI9225_GAMMA_CTRL10            (0x59u)  // Gamma Control 10

#define ILI9225C_INVOFF  0x20
#define ILI9225C_INVON   0x21


/// @name	Colors constants
// Colors                        Red  Green Blue
//                               4321054321043210
// const uint16_t blackColor   = 0x0000;
// const uint16_t whiteColor   = 0xFFFF;
// const uint16_t redColor     = 0xF800;
// const uint16_t greenColor   = 0x07E0;
// const uint16_t blueColor    = 0x001F;
// const uint16_t yellowColor  = 0xFFE0;
// const uint16_t cyanColor    = 0x07FF;
// const uint16_t magentaColor = 0xF81F;
// const uint16_t orangeColor  = 0xFD20;
// const uint16_t violetColor  = 0xEC1D;
// const uint16_t grayColor    = 0x8410;

/* RGB 24-bits color table definition (RGB888). */
#define RGB888_RGB565(color) ((((color) >> 19) & 0x1f) << 11) | ((((color) >> 10) & 0x3f) << 5) | (((color) >> 3) & 0x1f)

#define COLOR_BLACK          RGB888_RGB565(0x000000u)
#define COLOR_WHITE          RGB888_RGB565(0xFFFFFFu)
#define COLOR_BLUE           RGB888_RGB565(0x0000FFu)
#define COLOR_GREEN          RGB888_RGB565(0x00FF00u)
#define COLOR_RED            RGB888_RGB565(0xFF0000u)
#define COLOR_NAVY           RGB888_RGB565(0x000080u)
#define COLOR_DARKBLUE       RGB888_RGB565(0x00008Bu)
#define COLOR_DARKGREEN      RGB888_RGB565(0x006400u)
#define COLOR_DARKCYAN       RGB888_RGB565(0x008B8Bu)
#define COLOR_CYAN           RGB888_RGB565(0x00FFFFu)
#define COLOR_TURQUOISE      RGB888_RGB565(0x40E0D0u)
#define COLOR_INDIGO         RGB888_RGB565(0x4B0082u)
#define COLOR_DARKRED        RGB888_RGB565(0x800000u)
#define COLOR_OLIVE          RGB888_RGB565(0x808000u)
#define COLOR_GRAY           RGB888_RGB565(0x808080u)
#define COLOR_SKYBLUE        RGB888_RGB565(0x87CEEBu)
#define COLOR_BLUEVIOLET     RGB888_RGB565(0x8A2BE2u)
#define COLOR_LIGHTGREEN     RGB888_RGB565(0x90EE90u)
#define COLOR_DARKVIOLET     RGB888_RGB565(0x9400D3u)
#define COLOR_YELLOWGREEN    RGB888_RGB565(0x9ACD32u)
#define COLOR_BROWN          RGB888_RGB565(0xA52A2Au)
#define COLOR_DARKGRAY       RGB888_RGB565(0xA9A9A9u)
#define COLOR_SIENNA         RGB888_RGB565(0xA0522Du)
#define COLOR_LIGHTBLUE      RGB888_RGB565(0xADD8E6u)
#define COLOR_GREENYELLOW    RGB888_RGB565(0xADFF2Fu)
#define COLOR_SILVER         RGB888_RGB565(0xC0C0C0u)
#define COLOR_LIGHTGREY      RGB888_RGB565(0xD3D3D3u)
#define COLOR_LIGHTCYAN      RGB888_RGB565(0xE0FFFFu)
#define COLOR_VIOLET         RGB888_RGB565(0xEE82EEu)
#define COLOR_AZUR           RGB888_RGB565(0xF0FFFFu)
#define COLOR_BEIGE          RGB888_RGB565(0xF5F5DCu)
#define COLOR_MAGENTA        RGB888_RGB565(0xFF00FFu)
#define COLOR_TOMATO         RGB888_RGB565(0xFF6347u)
#define COLOR_GOLD           RGB888_RGB565(0xFFD700u)
#define COLOR_ORANGE         RGB888_RGB565(0xFFA500u)
#define COLOR_SNOW           RGB888_RGB565(0xFFFAFAu)
#define COLOR_YELLOW         RGB888_RGB565(0xFFFF00u)


/// Main and core class
class TFT_22_ILI9225 {

	public:

		TFT_22_ILI9225(uint8_t RST, uint8_t RS, uint8_t CS, uint8_t SDI, uint8_t CLK, uint8_t LED);
		TFT_22_ILI9225(uint8_t RST, uint8_t RS, uint8_t CS, uint8_t LED);

		/// Initialization
		void begin(void);

		/// Clear the screen
		void clear(void); 

		/// Invert screen
		/// @param	flag true to invert, false for normal screen
		void invert(boolean flag);

		/// Switch backlight on or off
		/// @param	flag true=on, false=off
		void setBacklight(boolean flag); 

		/// Switch display on or off
		/// @param	flag true=on, false=off
		void setDisplay(boolean flag);  

		/// Set orientation
		/// @param	orientation orientation, 0=portrait, 1=right rotated landscape, 2=reverse portrait, 3=left rotated landscape
		void setOrientation(uint8_t orientation);  

		/// Get orientation
		/// @return	orientation orientation, 0=portrait, 1=right rotated landscape, 2=reverse portrait, 3=left rotated landscape
		uint8_t getOrientation(void); 

		/// Font size, x-axis
		/// @return	horizontal size of current font, in pixels
		uint8_t fontX(void);

		/// Font size, y-axis
		/// @return	vertical size of current font, in pixels
		uint8_t fontY(void); 

		/// Screen size, x-axis
		/// @return	horizontal size of the screen, in pixels
		/// @note	240 means 240 pixels and thus 0..239 coordinates (decimal)
		uint16_t maxX(void);

		/// Screen size, y-axis
		/// @return	vertical size of the screen, in pixels
		/// @note	220 means 220 pixels and thus 0..219 coordinates (decimal)
		uint16_t maxY(void);

		/// Draw circle
		/// @param	x0 center, point coordinate, x-axis
		/// @param	y0 center, point coordinate, y-axis
		/// @param	radius radius
		/// @param	color 16-bit color
		void circle(uint16_t x0, uint16_t y0, uint16_t radius, uint16_t color);  

		/// Draw solid circle
		/// @param	x0 center, point coordinate, x-axis
		/// @param	y0 center, point coordinate, y-axis
		/// @param	radius radius
		/// @param	color 16-bit color
		void solidCircle(uint8_t x0, uint8_t y0, uint8_t radius, uint16_t color); 

		/// Set background color
		/// @param	color background color, default=black
		void setBackGroundColor(uint16_t color = COLOR_BLACK);  

		/// Draw line, rectangle coordinates
		/// @param	x1 top left coordinate, x-axis
		/// @param	y1 top left coordinate, y-axis
		/// @param	x2 bottom right coordinate, x-axis
		/// @param	y2 bottom right coordinate, y-axis
		/// @param	color 16-bit color
		void line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color); 

		/// Draw rectangle, rectangle coordinates
		/// @param	x1 top left coordinate, x-axis
		/// @param	y1 top left coordinate, y-axis
		/// @param	x2 bottom right coordinate, x-axis
		/// @param	y2 bottom right coordinate, y-axis
		/// @param	color 16-bit color
		void rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color); 

		/// Draw solid rectangle, rectangle coordinates
		/// @param	x1 top left coordinate, x-axis
		/// @param	y1 top left coordinate, y-axis
		/// @param	x2 bottom right coordinate, x-axis
		/// @param	y2 bottom right coordinate, y-axis
		/// @param	color 16-bit color
		void solidRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

		/// Draw pixel
		/// @param	x1 point coordinate, x-axis
		/// @param	y1 point coordinate, y-axis
		/// @param	color 16-bit color
		void point(uint16_t x1, uint16_t y1, uint16_t color);  

		/// Draw ASCII Text (pixel coordinates)
		/// @param	x0 point coordinate, x-axis
		/// @param	y0 point coordinate, y-axis
		/// @param	s text string
		/// @param	textColor 16-bit color, default=white
		/// @param	backColor 16-bit color, default=black
		/// @param	ix x-axis font size multiplier, default=1
		/// @param	iy y-axis font size multiplier, default=1
		void text(uint16_t x0, uint16_t y0, String s, uint16_t textColor = COLOR_WHITE, uint16_t backColor = COLOR_BLACK, uint8_t ix=1, uint8_t iy=1);

		/// Calculate 16-bit color from 8-bit Red-Green-Blue components
		/// @param	red red component, 0x00..0xff
		/// @param	green green component, 0x00..0xff
		/// @param	blue blue component, 0x00..0xff
		/// @return	16-bit color
		uint16_t setColor(uint8_t red, uint8_t green, uint8_t blue);

		/// Calculate 8-bit Red-Green-Blue components from 16-bit color
		/// @param	rgb 16-bit color
		/// @param	red red component, 0x00..0xff
		/// @param	green green component, 0x00..0xff
		/// @param	blue blue component, 0x00..0xff
		void splitColor(uint16_t rgb, uint8_t &red, uint8_t &green, uint8_t &blue);


	private:
		void	 _swop(uint16_t &a, uint16_t &b),
				 _setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1),
				 _orientCoordinates(uint16_t &x1, uint16_t &y1),
				 _writeDisplay(uint16_t reg, uint16_t data),
				 _writeData(uint8_t HI, uint8_t LO),
				 _writeCommand(uint8_t HI, uint8_t LO);

		uint16_t _maxX, _maxY;

		uint8_t  _rst, _rs, _cs, _sdi, _clk, _led,
				 _orientation;

	  	boolean  hwSPI;
};

/// Font 5x8
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
