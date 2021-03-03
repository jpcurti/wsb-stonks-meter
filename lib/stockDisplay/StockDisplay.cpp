#include <StockDisplay.h>

const unsigned char WSB[] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x01, 0x70, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x50, 0x00, 0x4c, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfa, 0xe0, 0x00, 0x01, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x20, 0x4f, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x66, 0x03, 0xf0, 0x00, 0x27, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x04, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x08, 0x00, 0x01, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x01, 0x00, 0x00, 0x80, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0xc0, 0x00, 0x40, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x10, 0x00, 0x20, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x04, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x12, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xfe, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x23, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x0f, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x03, 0xf8, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x0f, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x01, 0xc7, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xf6, 0x3f, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff,
	0xf7, 0x9f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff,
	0xfd, 0xdc, 0x7f, 0xff, 0xff, 0xfe, 0xff, 0x80, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff,
	0xfe, 0xed, 0xbf, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff,
	0xff, 0x6d, 0xbf, 0xff, 0xff, 0xfe, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff,
	0xff, 0x35, 0x79, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xbb, 0x7f, 0xff, 0xff, 0xf7, 0xff, 0xe0, 0x00, 0x08, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xd7, 0xff, 0xff, 0xff, 0xef, 0xff, 0xf0, 0x00, 0x0c, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xe7, 0x37, 0xff, 0xff, 0xef, 0xff, 0xf0, 0x00, 0x0c, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xe6, 0xf6, 0xcf, 0xff, 0xef, 0xff, 0xf0, 0x00, 0x18, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xf6, 0xff, 0xb7, 0xff, 0xef, 0xff, 0xf8, 0x00, 0x3c, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xf7, 0x1f, 0x73, 0xff, 0xef, 0xff, 0xfc, 0x00, 0x7c, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xfb, 0xcf, 0x71, 0xff, 0xef, 0xff, 0xfe, 0x00, 0xf9, 0xe1, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xfd, 0xf6, 0xf0, 0xff, 0xef, 0xff, 0xff, 0xcf, 0xff, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xc0,
	0xff, 0xfe, 0xfe, 0xe0, 0x7f, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xf3, 0xde,
	0xff, 0xff, 0x7d, 0xe0, 0x0f, 0xf3, 0xff, 0xff, 0xff, 0xc7, 0xfb, 0xff, 0xff, 0xff, 0xef, 0xb9,
	0xff, 0xff, 0xbb, 0xc0, 0x01, 0xf9, 0xf3, 0xff, 0xff, 0x81, 0xf3, 0xff, 0xff, 0xfd, 0xf9, 0xf7,
	0xff, 0xff, 0xff, 0xc0, 0x00, 0x0c, 0x23, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xfa, 0xff, 0xef,
	0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xfb, 0xfd, 0xdf,
	0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xfd, 0xff,
	0xff, 0xff, 0xfb, 0x80, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xcf, 0xff, 0xff, 0xfe, 0xce, 0xff,
	0xff, 0xff, 0xfb, 0x00, 0x00, 0x00, 0x03, 0x3f, 0xff, 0xff, 0x9f, 0xff, 0xff, 0x37, 0xf6, 0x7f,
	0xff, 0xff, 0xf7, 0x00, 0x00, 0x00, 0x03, 0x8f, 0xff, 0xff, 0x3f, 0xff, 0xfe, 0xdf, 0xfe, 0xff,
	0xff, 0xff, 0xfb, 0x00, 0x00, 0x00, 0x03, 0xe1, 0xff, 0xfc, 0x3f, 0xff, 0xf8, 0xef, 0x1f, 0xff,
	0xff, 0xff, 0xfc, 0x80, 0x00, 0x00, 0x03, 0xf8, 0x00, 0x00, 0x00, 0x3f, 0xc0, 0xe6, 0x7d, 0xff,
	0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x01, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x75, 0xfb, 0xff,
	0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x01, 0xf8, 0x1f, 0x80, 0x00, 0x00, 0x00, 0x7b, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x01, 0xf8, 0x1f, 0x80, 0x00, 0x00, 0x00, 0x79, 0xdf, 0xff,
	0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x01, 0xfc, 0x1f, 0x80, 0x00, 0x00, 0x00, 0x3d, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x01, 0xfc, 0x3f, 0x80, 0x00, 0x00, 0x00, 0x3e, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x01, 0xfc, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0xfc, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x7f, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0xfc, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x1d, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0xfc, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x0d, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0xf8, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x78, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x70, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x70, 0x78, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff};

StockDisplay::StockDisplay() : m_display(SCREEN_WIDTH, SCREEN_HEIGHT)
{

	if (!Serial)
	{
		Serial.begin(115200);
	}
	if (!m_display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
	{ // Address 0x3D for 128x64
		Serial.println(F("SSD1306 allocation failed"));
		for (;;)
			;
	}
	delay(1000);
	m_display.clearDisplay();
	drawWSB();
	
}
StockDisplay::~StockDisplay()
{
}

void StockDisplay::printTextOnDisplay(String message)
{
	m_display.clearDisplay();
	m_display.setTextSize(1);
	m_display.setTextColor(WHITE);
	m_display.setCursor(0, 10);
	// Display static text
	m_display.println(message.c_str());
	m_display.display();
}

void StockDisplay::drawWSB()
{
	// Clear the buffer.
	m_display.clearDisplay();
	// Display bitmap
	m_display.drawBitmap(0, 0, WSB, 128, 64, WHITE);
	m_display.display();
}

void StockDisplay::printStockPriceOnDisplay(String stockName, float value, float difference, float differenceInPercentage)
{
	// Clear the buffer.
	m_display.clearDisplay();
	// Display bitmap
	m_display.setCursor(0, 10);
	m_display.setTextSize(2);
	m_display.setTextColor(WHITE);
	m_display.print(stockName.c_str());
	m_display.print(" ");
	m_display.write(36);
	m_display.print(value, 2);
	m_display.setCursor(00, 30);
	m_display.setTextSize(1);
	difference < 0 ? m_display.write(46) : m_display.write(43);
	m_display.print(difference, 2);
	m_display.print(" (");
	m_display.print(differenceInPercentage, 2);
	m_display.print("%)");
	m_display.display();
}
