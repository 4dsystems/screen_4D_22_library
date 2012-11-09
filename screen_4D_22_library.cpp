//
// Library for 4D Systems 4DLCDM-22 and 4Display-Shield-22 2.2" screens
// ----------------------------------
// 
// Oct 30, 2012 release 2.02
//
// 4D Systems
// http://www.4dsystems.com.au/
//


// Library header
#include "screen_4D_22_library.h"


// Class
screen22::screen22(_4Dscreen22 screen) {

	if (screen==_4DSHIELD22) {
		LCD_RESET = _4DSHIELD22_LCD_RESET;
		LCD_RS = _4DSHIELD22_LCD_RS;
		LCD_CS = _4DSHIELD22_LCD_CS;
		LCD_Backlight = _4DSHIELD22_LCD_Backlight;
		TOUCH_YU = _4DSHIELD22_TOUCH_YU;
		TOUCH_XR = _4DSHIELD22_TOUCH_XR;
		TOUCH_YD = _4DSHIELD22_TOUCH_YD;
		TOUCH_XL = _4DSHIELD22_TOUCH_XL;
	} else if (screen==_4DLCDM22) {
		LCD_RESET = _4DLCDM22_LCD_RESET;
		LCD_RS = _4DLCDM22_LCD_RS;
		LCD_CS = _4DLCDM22_LCD_CS;
		LCD_Backlight = _4DLCDM22_LCD_Backlight;
		TOUCH_YU = _4DLCDM22_TOUCH_YU;
		TOUCH_XR = _4DLCDM22_TOUCH_XR;
		TOUCH_YD = _4DLCDM22_TOUCH_YD;
		TOUCH_XL = _4DLCDM22_TOUCH_XL;
	} else {
		return; // unknown screen
	}


	pinMode(LCD_RESET, OUTPUT);
	pinMode(LCD_Backlight, OUTPUT);
	pinMode(LCD_RS, OUTPUT);
	pinMode(LCD_CS, OUTPUT);

	digitalWrite(LCD_Backlight, HIGH);

	SPI.begin();
	SPI.setClockDivider(SPI_CLOCK_DIV2); // 4 MHz (half speed)
	SPI.setBitOrder(MSBFIRST);
	SPI.setDataMode(SPI_MODE0);
};


void screen22::_orientCoordinates(uint16_t &x1, uint16_t &y1) {
	switch (_orientation) {
	case 0:  // ok
		break;
	case 1: // ok
		y1 = _maxY - y1 -1;
		_swap(x1, y1);
		break;
	case 2: // ok
		x1 = _maxX - x1 -1;
		y1 = _maxY - y1 -1;
		break;
	case 3: // ok
		x1 = _maxX - x1 -1;
		_swap(x1, y1);
		break;
	}
}


void screen22::_setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
	_orientCoordinates(x0, y0);
	_orientCoordinates(x1, y1);

	if (x1<x0) _swap(x0, x1);
	if (y1<y0) _swap(y0, y1);

	_writeDisplay(0x36,x1);
	_writeDisplay(0x37,x0);

	_writeDisplay(0x38,y1);
	_writeDisplay(0x39,y0);

	_writeDisplay(0x20,x0);
	_writeDisplay(0x21,y0);

	_writeCommand(0x00, 0x22);
}


void screen22::begin() {
	// Initialization Code
	digitalWrite(LCD_RESET, 1); // Pull the reset pin high to release the ILI9225C from the reset status
	delay(1); 
	digitalWrite(LCD_RESET, 0); // Pull the reset pin low to reset ILI9225
	delay(10);
	digitalWrite(LCD_RESET, 1); // Pull the reset pin high to release the ILI9225C from the reset status
	delay(50);

	_writeDisplay(0x10, 0x0000); // Set SAP,DSTB,STB
	_writeDisplay(0x11, 0x0000); // Set APON,PON,AON,VCI1EN,VC
	_writeDisplay(0x12, 0x0000); // Set BT,DC1,DC2,DC3
	_writeDisplay(0x13, 0x0000); // Set GVDD
	_writeDisplay(0x14, 0x0000); // Set VCOMH/VCOML voltage
	delay(40); 

	// Power-on sequence
	_writeDisplay(0x11, 0x0018); // Set APON,PON,AON,VCI1EN,VC
	_writeDisplay(0x12, 0x6121); // Set BT,DC1,DC2,DC3
	_writeDisplay(0x13, 0x006F); // Set GVDD   /*007F 0088 */
	_writeDisplay(0x14, 0x495F); // Set VCOMH/VCOML voltage
	_writeDisplay(0x10, 0x0800); // Set SAP,DSTB,STB
	delay(10);
	_writeDisplay(0x11, 0x103B); // Set APON,PON,AON,VCI1EN,VC
	delay(50);

	_writeDisplay(0x01, 0x011C); // set the display line number and display direction
	_writeDisplay(0x02, 0x0100); // set 1 line inversion
	_writeDisplay(0x03, 0x1030); // set GRAM write direction and BGR=1.
	_writeDisplay(0x07, 0x0000); // Display off
	_writeDisplay(0x08, 0x0808); // set the back porch and front porch
	_writeDisplay(0x0B, 0x1100); // set the clocks number per line
	_writeDisplay(0x0C, 0x0000); // CPU interface
	_writeDisplay(0x0F, 0x0D01); // Set Osc  /*0e01*/
	_writeDisplay(0x15, 0x0020); // Set VCI recycling
	_writeDisplay(0x20, 0x0000); // RAM Address
	_writeDisplay(0x21, 0x0000); // RAM Address

	// GRAM area
	_writeDisplay(0x30, 0x0000); 
	_writeDisplay(0x31, 0x00DB); 
	_writeDisplay(0x32, 0x0000); 
	_writeDisplay(0x33, 0x0000); 
	_writeDisplay(0x34, 0x00DB); 
	_writeDisplay(0x35, 0x0000); 
	_writeDisplay(0x36, 0x00AF); 
	_writeDisplay(0x37, 0x0000); 
	_writeDisplay(0x38, 0x00DB); 
	_writeDisplay(0x39, 0x0000); 


	// Gamma 2.2 
	_writeDisplay(0x50, 0x0000); 
	_writeDisplay(0x51, 0x0808); 
	_writeDisplay(0x52, 0x080A); 
	_writeDisplay(0x53, 0x000A); 
	_writeDisplay(0x54, 0x0A08); 
	_writeDisplay(0x55, 0x0808); 
	_writeDisplay(0x56, 0x0000); 
	_writeDisplay(0x57, 0x0A00); 
	_writeDisplay(0x58, 0x0710); 
	_writeDisplay(0x59, 0x0710); 

	_writeDisplay(0x07, 0x0012); 
	delay(50); 
	_writeDisplay(0x07, 0x1017);

	setBacklight(true);
	setOrientation(0);

	clear();
}


void screen22::clear() {
	uint8_t old = _orientation;
	setOrientation(0);
	solidRectangle(0, 0, _maxX-1, _maxY-1, blackColour);
	setOrientation(old);
	delay(10);
}


void screen22::invert(boolean flag) {
	_writeCommand(0x00, flag ? ILI9225C_INVON : ILI9225C_INVOFF);
}


void screen22::setBacklight(boolean flag) {
	digitalWrite(LCD_Backlight, flag);
}


void screen22::setDisplay(boolean flag) {
	if (flag) {
		_writeDisplay(0x00ff, 0x0000);
		_writeDisplay(0x0010, 0x0000);
		delay(50);
		_writeDisplay(0x0007, 0x1017);
		delay(200);
	} else {
		_writeDisplay(0x00ff, 0x0000);
		_writeDisplay(0x0007, 0x0000);
		delay(50);
		_writeDisplay(0x0010, 0x0003);
		delay(200);
	}
}


void screen22::setOrientation(uint8_t orientation) {
	_orientation = orientation % 4;

	switch (_orientation) {
	case 0:
		_maxX = ILI9225C_WIDTH;
		_maxY = ILI9225C_HEIGHT;
		break;
	case 1:
		_maxX = ILI9225C_HEIGHT;
		_maxY = ILI9225C_WIDTH;
		break;
	case 2:
		_maxX = ILI9225C_WIDTH;
		_maxY = ILI9225C_HEIGHT;
		break;
	case 3:
		_maxX = ILI9225C_HEIGHT;
		_maxY = ILI9225C_WIDTH;
		break;
	}
}


uint8_t screen22::getOrientation() {
	return _orientation;
}


void screen22::rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t colour) {
	line(x1, y1, x1, y2, colour);
	line(x1, y1, x2, y1, colour);
	line(x1, y2, x2, y2, colour);
	line(x2, y1, x2, y2, colour);
}


void screen22::solidRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t colour) {

	_setWindow(x1, y1, x2, y2);

	for(uint16_t t=(y2-y1+1)*(x2-x1+1); t>0; t--)
		_writeData(colour >> 8, colour);
}


void screen22::circle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t colour) {
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

	point(x0, y0+r, colour);
	point(x0, y0-r, colour);
	point(x0+r, y0, colour);
	point(x0-r, y0, colour);

	while (x<y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		point(x0 + x, y0 + y, colour);
		point(x0 - x, y0 + y, colour);
		point(x0 + x, y0 - y, colour);
		point(x0 - x, y0 - y, colour);
		point(x0 + y, y0 + x, colour);
		point(x0 - y, y0 + x, colour);
		point(x0 + y, y0 - x, colour);
		point(x0 - y, y0 - x, colour);
	}
}


void screen22::solidCircle(uint8_t x0, uint8_t y0, uint8_t radius, uint16_t colour) {
	int16_t f = 1 - radius;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * radius;
	int16_t x = 0;
	int16_t y = radius;

	while (x<y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		line(x0 + x, y0 + y, x0 - x, y0 + y, colour); // bottom
		line(x0 + x, y0 - y, x0 - x, y0 - y, colour); // top
		line(x0 + y, y0 - x, x0 + y, y0 + x, colour); // right
		line(x0 - y, y0 - x, x0 - y, y0 + x, colour); // left
	}

	solidRectangle(x0-x, y0-y, x0+x, y0+y, colour);
}


void screen22::line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t colour) {
	// Classic Bresenham algorithm
	int16_t steep = abs(y2 - y1) > abs(x2 - x1);
	int16_t dx, dy;

	if (steep) {
		_swap(x1, y1);
		_swap(x2, y2);
	}

	if (x1 > x2) {
		_swap(x1, x2);
		_swap(y1, y2);
	}

	dx = x2 - x1;
	dy = abs(y2 - y1);

	int16_t err = dx / 2;
	int16_t ystep;

	if (y1 < y2) ystep = 1;
	else ystep = -1;


	for (; x1<=x2; x1++) {
		if (steep) point(y1, x1, colour);
		else       point(x1, y1, colour);

		err -= dy;
		if (err < 0) {
			y1 += ystep;
			err += dx;
		}
	}
}


void screen22::point(uint16_t x1, uint16_t y1, uint16_t colour) {

	if((x1 < 0) || (x1 >= _maxX) || (y1 < 0) || (y1 >= _maxY)) return;

	_setWindow(x1, y1, x1+1, y1+1);
	_orientCoordinates(x1, y1);
	_writeData(colour >> 8, colour);
}


void screen22::text(uint16_t x0, uint16_t y0, String s, uint16_t textColour, uint16_t backColour, uint8_t ix, uint8_t iy) {
	uint8_t c;
	uint8_t line;
	uint16_t x, y;
	uint8_t i, j, k;

	y0 -= 8*(iy-1);

	if ((ix>1) || (iy>1)) {
		for (k=0; k<s.length(); k++) {
			x = x0 + 6 * k * ix;
			y = y0;

			for ( i=0; i<6; i++ ) {
				if (i == 5) line = 0x0;
				else        line = font5x8[s.charAt(k)-' '][i];

				for ( j = 0; j<8; j++) {
					if (bitRead(line, j)) solidRectangle(x+i*ix, y+j*iy, x+i*ix+ix-1, y+j*iy+iy-1, textColour);
					else solidRectangle(x+i*ix, y+j*iy, x+i*ix+ix-1, y+j*iy+iy-1, backColour);
				}
			}
		}
	} else {
		for (k=0; k<s.length(); k++) {
			x = x0 + 6 * k;
			y = y0;

			for ( i=0; i<6; i++ ) {
				if (i == 5) line = 0x0;
				else        line = font5x8[s.charAt(k)-' '][i];

				for ( j = 0; j<8; j++) {
					if (bitRead(line, j)) point(x+i, y+j, textColour);
					else point(x+i, y+j, backColour);
				}
			}
		}
	}
}


boolean screen22::getTouch(uint16_t &x, uint16_t &y) {
	uint16_t x0, y0, z0;
	uint16_t sample0, sample1;
	uint8_t i;
	boolean valid = true;

	uint8_t xp_port = digitalPinToPort(TOUCH_XL);
	uint8_t yp_port = digitalPinToPort(TOUCH_YU);
	uint8_t xm_port = digitalPinToPort(TOUCH_XR);
	uint8_t ym_port = digitalPinToPort(TOUCH_YD);

	uint8_t xp_pin = digitalPinToBitMask(TOUCH_XL);
	uint8_t yp_pin = digitalPinToBitMask(TOUCH_YU);
	uint8_t xm_pin = digitalPinToBitMask(TOUCH_XR);
	uint8_t ym_pin = digitalPinToBitMask(TOUCH_YD);

	pinMode(TOUCH_YU, INPUT);
	pinMode(TOUCH_YD, INPUT);

	digitalWrite(TOUCH_YU, LOW);
	digitalWrite(TOUCH_YD, LOW);

	pinMode(TOUCH_XL, OUTPUT);
	pinMode(TOUCH_XR, OUTPUT);
	digitalWrite(TOUCH_XL, HIGH);
	digitalWrite(TOUCH_XR, LOW);

	sample0 = analogRead(TOUCH_YU);
	sample1 = analogRead(TOUCH_YU);
	if (sample0 != sample1) valid = false;
	x0 = 1023-sample1;

	pinMode(TOUCH_XL, INPUT);
	pinMode(TOUCH_XR, INPUT);
	digitalWrite(TOUCH_XL, LOW);

	pinMode(TOUCH_YU, OUTPUT);
	digitalWrite(TOUCH_YU, HIGH);
	pinMode(TOUCH_YD, OUTPUT);

	sample0 = analogRead(TOUCH_XR);
	sample1 = analogRead(TOUCH_XR);
	if (sample0 != sample1) valid = false;
	y0 = 1023-sample1;

	// Set XL to ground
	pinMode(TOUCH_XL, OUTPUT);
	digitalWrite(TOUCH_XL, LOW);

	// Set YD to VCC
	digitalWrite(TOUCH_YD, HIGH);

	// Set YU to ground
	digitalWrite(TOUCH_YU, LOW);
	pinMode(TOUCH_YU, INPUT);

	int z1 = analogRead(TOUCH_XR);
	int z2 = analogRead(TOUCH_YU);

	if (valid) z0 = (1023-(z2-z1));
	else z0 = 0;


	switch (_orientation) {
	case 0: // ok
		x = map(x0, 136, 912, 0, _maxX);
		y = map(y0, 104, 888, 0, _maxY);
		break;
	case 1: // ok
		y = map(x0, 104, 888, _maxY, 0);
		x = map(y0, 136, 912, 0, _maxX);
		break;
	case 2: // ok
		x = map(x0, 136, 912, _maxX, 0);
		y = map(y0, 104, 888, _maxY, 0);
		break;
	case 3: // ok
		y = map(x0, 104, 888, 0, _maxY);
		x = map(y0, 136, 912, _maxX, 0);
		break;
	}

	if (x < 0) x = 0;
	if (x >= _maxX) x = _maxX-1;
	if (y < 0) y = 0;
	if (y >= _maxY) y = _maxY-1;

	return (z0>ILI9225C_PRESSURE);
}


uint16_t screen22::maxX() {
	return _maxX;
}


uint16_t screen22::maxY() {
	return _maxY;
}


uint16_t screen22::setColour(uint8_t red8, uint8_t green8, uint8_t blue8) {
	// rgb16 = red5 green6 blue5
	return (red8 >> 3) << 11 | (green8 >> 2) << 5 | (blue8 >> 3);
}


void screen22::splitColour(uint16_t rgb, uint8_t &red, uint8_t &green, uint8_t &blue) {
	// rgb16 = red5 green6 blue5
	red   = (rgb & 0b1111100000000000) >> 11 << 3;
	green = (rgb & 0b0000011111100000) >>  5 << 2;
	blue  = (rgb & 0b0000000000011111)       << 3;
}


void screen22::_swap(uint16_t &a, uint16_t &b) {
	uint16_t w = a;
	a = b;
	b = w;
}

// Utilities
void screen22::_writeCommand(uint8_t HI, uint8_t LO) {
	digitalWrite(LCD_RS, LOW);
	digitalWrite(LCD_CS, LOW);
	SPI.transfer(HI);
	SPI.transfer(LO);
	digitalWrite(LCD_CS, HIGH);
}


void screen22::_writeData(uint8_t HI, uint8_t LO) {
	digitalWrite(LCD_RS, HIGH);
	digitalWrite(LCD_CS, LOW);
	SPI.transfer(HI);
	SPI.transfer(LO);
	digitalWrite(LCD_CS, HIGH);
}


void screen22::_writeDisplay(uint16_t reg, uint16_t data) {
	_writeCommand(reg>>8, reg&255);
	_writeData(data>>8, data&255);
}
