#ifndef STOCKDISPLAY_H
#define STOCKDISPLAY_H

	#include <Wire.h>
	#include <Adafruit_GFX.h>
	#include<Adafruit_SSD1306.h>
	#define SCREEN_WIDTH 128 // OLED display width, in pixels
	#define SCREEN_HEIGHT 64 // OLED display height, in pixels
	#define DELAY_LOGO true
	
	class StockDisplay
	{
	private:
		// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
		Adafruit_SSD1306 m_display;
		String stock;
	public:
		StockDisplay();
		~StockDisplay();
		void printTextOnDisplay(String message);
		void drawWSB();
		void printStockPriceOnDisplay(String stockName, float value, float difference , float differenceInPercentage);
	
	};


#endif