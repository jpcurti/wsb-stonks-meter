#ifndef STOCKPRINTER_H
#define STOCKPRINTER_H

	#include <Wire.h>
	#include <Adafruit_GFX.h>
	#include<Adafruit_SSD1306.h>
	#define SCREEN_WIDTH 128 // OLED display width, in pixels
	#define SCREEN_HEIGHT 64 // OLED display height, in pixels

	
	class StockPrinter{

		public:
		StockPrinter();

		void updateDisplay(String message);
		void drawWSB();

		private:
		// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
		Adafruit_SSD1306 *display;
		String stock;
	
	};
	
#endif