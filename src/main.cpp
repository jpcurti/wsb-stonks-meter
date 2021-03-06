#include <Arduino.h>
#include <StockDisplay.h>
#include <ServoInterface.h>
#include <ApConfigurator.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <vector>
#include <string>

//Stock Display
StockDisplay *display;
ServoInterface *servo;
DynamicJsonDocument doc(1024);
float previous_close_price;
float current_price;
ApConfigurator apConfig;
void setup()
{
  display = new StockDisplay();
  servo = new ServoInterface();
  apConfig.begin();
}
void loop()
{ 
  apConfig.checkRequestConfigurationPortal();
  apConfig.check_status();
  delay(1000);
  String  httpRequest = String("https://finnhub.io/api/v1/quote?symbol=")+ apConfig.ticker() +"&token="+ apConfig.api_key();
  if (apConfig.check_WiFi() == 3)//Check WiFi connection status
  { 
    BearSSL::WiFiClientSecure client;
    HTTPClient http; //Declare an object of class HTTPClient
    client.setInsecure();
    http.begin(client,httpRequest); //Specify request destination
    int httpCode = http.GET();                                 //Send the request

    if (httpCode > 0)
    { //Check the returning code

      String payload = http.getString(); //Get the request response payload
      Serial.println(payload);           //Print the response payload
      deserializeJson(doc, payload);
      JsonObject obj = doc.as<JsonObject>();

      // You can use a String to get an element of a JsonObject
      // No duplication is done.
       previous_close_price = obj[String("pc")];
       current_price = obj[String("c")];
    }

    http.end(); //Close connection
  }
  float difference = current_price-previous_close_price;
  display->printStockPriceOnDisplay("BB", current_price, difference, difference*100/previous_close_price);
  delay(60000);

  /*
  for (int aux=0; aux<100; aux++)
  {
  servo->updateServoOnPercentage(aux);
  delay(50);
  }
  */
}
 


  