#include <Arduino.h>
#include <StockDisplay.h>
#include <ServoInterface.h>
#include <ApConfigurator.h>
#include <finnhubAPIInterface.h>
#include <Ticker.h>


StockDisplay *display;
ServoInterface *servo;
ApConfigurator apConfig;
finnhubAPIInterface *stockAPI;

void updateStockValue();
void checkWifiConnection();
void checkInterruptButtonPress();
void updateDisplay();
int count=0;


Ticker timer1(updateStockValue, 60000, 0, MILLIS);
Ticker timer2(checkWifiConnection, 5000, 0, MILLIS);
Ticker timer3(checkInterruptButtonPress, 100, 0, MILLIS);
Ticker timer4(updateDisplay, 2000, 0, MILLIS);
void setup()
{
  display = new StockDisplay();
  servo = new ServoInterface();
  apConfig.begin();
  stockAPI = new finnhubAPIInterface( );
  updateStockValue();
  timer1.start();
  timer2.start();
  timer3.start();
  timer4.start();
}
void loop()
{ 
 
  timer1.update();
  timer2.update();
  timer3.update();
  timer4.update();
}

void checkInterruptButtonPress()
{
   //Verifies if configuration Portal was requested. If it was, update immediatly the value on screen
  if(apConfig.checkRequestConfigurationPortal())
  {
    updateStockValue();
  } 
}
void checkWifiConnection()
{
  apConfig.check_WiFi();
}
void updateStockValue()
{
  stockAPI->requestStockCurrentPrice(String(apConfig.ticker()), String(apConfig.api_key()));
  //servo->updateServoOnPercentage(aux);
}
void updateDisplay()
{ 
  String value;
  switch (count%3)
  {
  case 0:
    value=String()+"$"+stockAPI->getCurrentPrice();
    break;
  case 1:
    if(stockAPI->getDifferenceInPrice()>0) value=String()+"+"+stockAPI->getDifferenceInPrice();
    else value=String()+stockAPI->getDifferenceInPrice();
    break;
  case 2:
    //display percentage
    if(stockAPI->getDifferenceInPrice()>0) value= String()+"+"+stockAPI->getDifferenceInPrice()*100/stockAPI->getPreviousClosePrice()+"%";
    else value= String()+stockAPI->getDifferenceInPrice()*100/stockAPI->getPreviousClosePrice()+"%";
    break;
  default:
    break;
  }
  display->printStockPriceOnDisplay(String(apConfig.ticker()), value);
  count++;
  //display->printStockPriceOnDisplay(String(apConfig.ticker()), stockAPI->getCurrentPrice(), stockAPI->getDifferenceInPrice(), stockAPI->getDifferenceInPrice()*100/stockAPI->getPreviousClosePrice());
}



  