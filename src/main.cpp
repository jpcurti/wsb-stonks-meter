#include <Arduino.h>
#include <StockDisplay.h>
#include <ServoInterface.h>
#include <ApConfigurator.h>

//Stock Display
StockDisplay *display ;
ServoInterface *servo;
void setup()
{ 
  display = new StockDisplay();
  servo =  new ServoInterface();
  ApConfigurator::setupApConfigurator();
  
}
void loop()
{
  ApConfigurator::checkRequestConfigurationPortal();
  
  ApConfigurator::check_status();
	display->printStockPriceOnDisplay("BB",5.75, 0.5, 10.2);
  delay(1000);

  /*
  for (int aux=0; aux<100; aux++)
  {
  servo->updateServoOnPercentage(aux);
  delay(50);
  }
  */
}