#include <Arduino.h>
#include <StockDisplay.h>
#include <ServoInterface.h>
#include <ApConfigurator.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

//Stock Display
StockDisplay *display;
ServoInterface *servo;
DynamicJsonDocument doc(1024);
float previous_close_price;
float current_price;

void setup()
{
  display = new StockDisplay();
  servo = new ServoInterface();
  ApConfigurator::setupApConfigurator();
}
void loop()
{ 
  ApConfigurator::checkRequestConfigurationPortal();
  ApConfigurator::check_status();
  // delay(1000);
  // if (ApConfigurator::check_WiFi() == 3)//Check WiFi connection status
  // { 
  //   BearSSL::WiFiClientSecure client;
  //   HTTPClient http; //Declare an object of class HTTPClient
  //   client.setInsecure();
  //   http.begin(client,"https://finnhub.io/api/v1/quote?symbol=BB&token=sandbox_c11p0kv48v6p2grljrj0"); //Specify request destination
  //   int httpCode = http.GET();                                 //Send the request

  //   if (httpCode > 0)
  //   { //Check the returning code

  //     String payload = http.getString(); //Get the request response payload
  //     Serial.println(payload);           //Print the response payload
  //     deserializeJson(doc, payload);
  //     JsonObject obj = doc.as<JsonObject>();

  //     // You can use a String to get an element of a JsonObject
  //     // No duplication is done.
  //      previous_close_price = obj[String("pc")];
  //      current_price = obj[String("c")];
  //   }

  //   http.end(); //Close connection
  // }
  // float difference = current_price-previous_close_price;
  // display->printStockPriceOnDisplay("BB", current_price, difference, difference*100/previous_close_price);
  // delay(100000);

  /*
  for (int aux=0; aux<100; aux++)
  {
  servo->updateServoOnPercentage(aux);
  delay(50);
  }
  */
}
 


  