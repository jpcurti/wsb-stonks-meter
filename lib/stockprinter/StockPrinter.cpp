#include <StockPrinter.h>


StockPrinter::StockPrinter(){
	display = new Adafruit_SSD1306 (SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

  if(!Serial){
		Serial.begin(9600);
	} 
  if(!display->begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display->clearDisplay();
  
}

void StockPrinter::updateDisplay(String message)
{	
	display->clearDisplay();
	display->setTextSize(1);
	display->setTextColor(WHITE);
	display->setCursor(0, 10);
	// Display static text
	display->println(message.c_str());
	display->display(); 


}