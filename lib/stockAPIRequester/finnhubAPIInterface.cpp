#include <finnhubAPIInterface.h>

#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

finnhubAPIInterface::finnhubAPIInterface( )
{   
    //httpRequestAddress = String("https://finnhub.io/api/v1/quote?symbol=")+ tickerSymbol +"&token="+ apiKey;
    //client.setInsecure();
    //http.begin(client,httpRequestAddress); //Specify request destination
    //requestStockCurrentPrice();
}
finnhubAPIInterface::~finnhubAPIInterface()
{
    //http.end(); //Close connection
}
void finnhubAPIInterface::requestStockCurrentPrice(String tickerSymbol, String apiKey)
{   
    BearSSL::WiFiClientSecure client;
    HTTPClient http; //Declare an object of class HTTPClient
    httpRequestAddress = String("https://finnhub.io/api/v1/quote?symbol=")+ tickerSymbol +"&token="+ apiKey;
    client.setInsecure();

    http.begin(client,httpRequestAddress); //Specify request destination
    DynamicJsonDocument doc(1024);
    int httpCode = http.GET(); //Send the request
    if (httpCode > 0)
    { //Check the returning code

      String payload = http.getString(); //Get the request response payload
      Serial.println(payload);           //Print the response payload
      deserializeJson(doc, payload);
      JsonObject obj = doc.as<JsonObject>();

      // You can use a String to get an element of a JsonObject
      // No duplication is done.
       previousClosePrice = obj[String("pc")];
       currentPrice = obj[String("c")];
       differenceInPrice = currentPrice-previousClosePrice;
    }
    http.end(); //Close connection
}

float finnhubAPIInterface::getPreviousClosePrice()
{
    return previousClosePrice;
}
float finnhubAPIInterface::getCurrentPrice()
{
    return currentPrice;
}
float finnhubAPIInterface::getDifferenceInPrice()
{
    return differenceInPrice;
}